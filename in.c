/* lcdemu - emulator of Matrix Orbital(R) lcd displays
   Copyright (C) 1999 Piotr Esden-Tempski

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "in.h"

void init_in(void)
{
  /*fifo_comf=open(pipe_path, O_RDONLY);*/
  fifo_comf=open(pipe_path, O_RDWR); /*TODO change to O_RDONLY*/
  /*mess(LCD_INF, pipe_path);*/
  if(fifo_comf == -1)
  {
    mess(LCD_ERR, "Could not open the data pipe.\n");
  }
}

void close_in(void)
{
  close(fifo_comf);
}

void main_loop(void)
{
  char *ch;
  ch=malloc(1);
  for(;;)
  {
    if(read(fifo_comf, ch, 1)==-1)
    {
      mess(LCD_ERR, "Could not read from the data pipe.\n");
    }
    else
    {
      if(!command_mode)
      {
        if( ch[0] != 254 )
        {
          disp_ch(ch[0]);
        }
        else
        {
          command_mode=TRUE;
        }
      }
      else
      {
        handle_command(ch[0]);
      }
    }
  }
}

/* handle the command mode input */
void handle_command( unsigned int ch )
{

  /*fprintf(stderr, "handlecommand %i %i \n", ch, command_nr);*/
  if(command_nr==0)
  {
    switch (ch)
    {
      case 'C': /* Line wrappinf on */
        mess(LCD_WRN, "Line wrapping on not implemented.\n");
        wrapping=TRUE;
        command_mode=FALSE;
      break;

      case 'D': /* Line wrapping off */
        mess(LCD_WRN, "Line wrapping off not implemented.\n");
        wrapping=FALSE;
        command_mode=FALSE;
      break;

      case 'Q': /* Scrolling on TODO fully implement*/
        scroll=TRUE;
        command_mode=FALSE;
      break;

      case 'R': /* Scrolling off */
        scroll=FALSE;
        command_mode=FALSE;
      break;

      case 'B': /* Backlight on */
        backlight=TRUE;
        set_backlight(backlight);
        set_contrast(contrast_val);
        init_chars(); 
        refr();
        s_backlight=TRUE;
        command_nr++;
      break;

      case 'F': /* Backlight off */
        backlight=FALSE;
        set_backlight(backlight);
        set_contrast(contrast_val);
        init_chars();
        refr();
        command_mode=FALSE;
      break;

      case 'X': /* Clear display */
        rst();
        /*fprintf(stderr,"X\n");*/
        cur_pos=0;
        command_mode=FALSE;
      break;

      case 'P': /*Set contrast*/
        /*mess(LCD_WRN, "Contrast setting not implemented.\n");*/
        contrast=TRUE;
        command_nr++;
      break;

      case 'J': /* Set the cursor at the current position on */
        cursor(TRUE, cur_pos%20, (cur_pos-cur_pos%20)/20);
        refr();
        command_mode=FALSE;
      break;

      case 'K': /* Unset the cursor in the current position */
        cursor(FALSE, cur_pos%20, (cur_pos-cur_pos%20)/20);
        refr();
        command_mode=FALSE;
      break;

      case 'L': /* Move thr curront position to the left */
        if(cur_pos>0)cur_pos--;
        else  mess(LCD_DBG,"Tryed to move the cursor out of display.(L)\n");
        command_mode=FALSE;
      break;

      case 'M': /* Move the current position to the right */
        if(cur_pos<79)cur_pos++;
        else  mess(LCD_DBG, "Tryed to move the cursor out of display.(R)\n");
        command_mode=FALSE;
      break;

      case 'N': /*Set custom character*/
        new_char=TRUE;
        command_nr++;
      break;

      case 'G': /*Set current position*/
        set_cur_pos=TRUE;
        command_nr=1;
      break;

      default:

        fprintf(stderr, "This command is not implemented.(%c)\n", ch);

        /*mess(LCD_WRN, "This command is not implemented.\n");*/

        /*char *dumy;*/
        /*sprintf(dumy, "This command is not implemented.()\n");
        mess(LCD_WRN, dumy); FIXME it brings allways Segmentation fault, why?*/

        command_mode=FALSE;
      break;
    }
  }
  else
  {
    if(s_backlight)
    {
      light_time=ch;
      /* mess(LCD_INF, "light_time set to: %i\n", light_time); TODO do usable */
      s_backlight=FALSE;
      command_nr=0;
      command_mode=FALSE;
    }

    if(set_cur_pos)
    {
      if(command_nr==1)
      {
        curs_x=ch-1;
        command_nr++;
      }
      else
      {
        curs_y=ch-1;
        if(((curs_x>=0)&&(curs_x<=19))&&((curs_y>=0)&&(curs_y<=3)))
          cur_pos=curs_y*20+curs_x;
        else
          mess(LCD_DBG, "Tryed to move the cursor out of display.\n");
        set_cur_pos=FALSE;
        command_nr=0;
        command_mode=FALSE;
      }
    }

    if(contrast)
    {
      /*char *dum;*/
      contrast_val=ch;
      set_backlight(backlight);
      set_contrast(contrast_val);
      init_chars();
      refr();
      /*sprintf(dum, "contrast_val set to: %i\n", contrast_val);
      mess(LCD_INF, dum); TODO uncomment*/
      contrast=FALSE;
      command_nr=0;
      command_mode=FALSE;
    }

    if(new_char)
    {
      if(command_nr==1)
      {
        char_nr=ch;
        command_nr++;
      }
      else
      {
        bits[command_nr-2]=ch;
        if(command_nr==9)
        {
          add_char();
          /* fprintf(stderr, "Info: New char: %i\n", char_nr); TODO do usable */
          new_char=FALSE;
          command_nr=0;
          command_mode=FALSE;
        }
        else
        {
          command_nr++;
        }
      }
    }

  }
}

void disp_ch(unsigned int ch)
{
   /* fprintf(stderr, "%i", ch); */
  if(cur_pos<80)
  {
    if(!(dispbuf[0][cur_pos%20][(cur_pos-cur_pos%20)/20]==ch)||((ch>=0)&&(ch<=7)))
    {
      dispbuf[0][cur_pos%20][(cur_pos-cur_pos%20)/20]=ch;
      putch(ch,cur_pos%20,(cur_pos-cur_pos%20)/20);
      disp();
    }
    cur_pos++;
  }
  else
  {
    if(cur_pos==80)
    {
      mess(LCD_DBG, "To much data to display.\n");
      cur_pos++;
    }
  }
}

void add_char(void)
{
  int i, j;
  cha some_char={
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0},
    {0,0,0,0,0}
  };

  if(char_nr>7)
  {
    mess(LCD_DBG, "The Character you want to change is not in the valid sector.");
  }
  else
  {
    for(i=0;i<8;i++)
    {
      for(j=4;j>=0;j--)
      {
        if(bits[i]>0)
        {
          if((bits[i]%2)==1)
          {
            some_char[i][j]=1;
            bits[i]--;
          }
          else
          {
            some_char[i][j]=0;
          }
          bits[i]=bits[i]/2;
        }
        else
        {
          some_char[i][j]=0;
        }
      }
    }
  }
  for(i=0;i<8;i++)
  {
    for(j=0;j<5;j++)
    {
      chat[char_nr][i][j] = some_char[i][j]; /*TODO remove this!!!!!!!!!!!!!*/
    }
  }
  /*chat[char_nr]=some_char;TODO do it like this not like above*/
  init_char( some_char, char_nr );
}
