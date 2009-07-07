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

#include "handle_out.h" 

void init_chars(void)
{
  int i,j,k;
  cha some_char;
  /*fprintf(stderr, "init_chars\n");*/
  for(i=0;i<(16*16);i++)
  {
    for(j=0;j<8;j++)
    {
      for(k=0;k<5;k++)
      {
        /*if((k==0)&&(i=='0'))
        {
          fprintf(stderr, "\n");
        }*/
        some_char[j][k] = chat[i][j][k]; /*TODO remove this!!!!!!!!!!!!!*/
        /*if(i=='0')
        {*/
          /*fprintf(stderr,"%i",chat[i][j][k]);*/
        /*  fprintf(stderr,"%i",some_char[j][k]);
        }*/
      }
    }
    init_char(some_char, i); 
  }
}

void init_char(cha some_char, int char_nr)
{
  int i, j;
  for(i=0;i<8;i++)
  {
    for(j=0;j<5;j++)
    {
      /*if(char_nr=='0')
      {
        if(j==0)
        {
          fprintf(stderr,"\n");
        }*/
        /*fprintf(stderr,"%i",chat[48][i][j]);*/
        /*fprintf(stderr,"%i", some_char[i][j]);
      }*/
      if(some_char[i][j] > 0)
      {
        chapt[char_nr][j*3][i]=char_fg[0];
        chapt[char_nr][j*3+1][i]=char_fg[1];
        chapt[char_nr][j*3+2][i]=char_fg[2];
      }
      else
      {
        if(i == 7)
        {
          chapt[char_nr][j*3][i]=underl[0];
          chapt[char_nr][j*3+1][i]=underl[1];
          chapt[char_nr][j*3+2][i]=underl[2];
        }
        else
        {
          chapt[char_nr][j*3][i]=char_bg[0];
          chapt[char_nr][j*3+1][i]=char_bg[1];
          chapt[char_nr][j*3+2][i]=char_bg[2];
        }
      }
    }
  }
}

void rst(void)
{
   int i, j;
  /*fprintf(stderr, "rst\n");*/

  /* Clear picture data field */
  for(i=0;i<zut_width*zut_height*3;i=i+3)
  {
    picture[i]=disp_bg[0];
    picture[i+1]=disp_bg[1];
    picture[i+2]=disp_bg[2];
  }
  for(i=0;i<lcd_width;i++)
  {
    for(j=0;j<lcd_height;j++)
    {
      dispbuf[0][i][j]=' ';
      dispbuf[1][i][j]=0;
      putch(' ',i,j);
    }
  }
  disp();
}

void refr(void)
{
  int i, j;
  /* Clear picture data field */
  for(i=0;i<zut_width*zut_height*3;i=i+3)
  {
    picture[i]=disp_bg[0];
    picture[i+1]=disp_bg[1];
    picture[i+2]=disp_bg[2];
  }
  for(i=0;i<20;i++)
  {
    for(j=0;j<4;j++)
    {
      putch(dispbuf[0][i][j], i, j);
    }
  }
  disp();
}

void putch(unsigned int cod, int x, int y)
{
  int i,j,k,l;
  /* fprintf(stderr,"cod: %i, x: %i, y: %i\n",cod, x, y); */
  for(i=0;i<5;i++)  {
    for(j=0;j<8;j++)
    {
      k = ( x * 6 + y * zut_width * 9 ) * 3;
      l = k + ( 1 + i + ( j + 1 ) * zut_width ) * 3;

      /* fprintf(stderr,"c"); */

      picture[l]   = chapt[cod][i*3][j];
      picture[l+1] = chapt[cod][i*3+1][j];
      picture[l+2] = chapt[cod][i*3+2][j];
    }
  }
  cursor(dispbuf[1][x][y], x, y);
}

void cursor(bool on, int x, int y )
{
  int i, k, l;  
  if((y>3)||(x>19))
  {
    mess(LCD_DBG, "Want to set cursor out of display.\n");
  }
  else
  {
    if(on)
    {
      for(i=0;i<5;i++)
      {
        k=(x*6+y*zut_width*9)*3;
        l=k+(1+i+(7+1)*zut_width)*3;
        picture[l]=char_fg[0];
        picture[l+1]=char_fg[1];
        picture[l+2]=char_fg[2];
      }
      dispbuf[1][x][y]=TRUE;
    }
    else
    {
      if(dispbuf[1][x][y]==TRUE)
      {
        for(i=0;i<5;i++)
        {
          k=(x*6+y*zut_width*9)*3;
          l=k+(1+i+(7+1)*zut_width)*3;
          picture[l]=underl[0];
          picture[l+1]=underl[1];
          picture[l+2]=underl[2];
        }
      }
      dispbuf[1][x][y]=FALSE;
    }
  }
}

void set_backlight(bool on)
{
  if(on)
  {
    char_fg[0] = CHAR_FG_R_ON;
    char_fg[1] = CHAR_FG_G_ON;
    char_fg[2] = CHAR_FG_B_ON;
    char_bg[0] = CHAR_BG_R_ON;
    char_bg[1] = CHAR_BG_G_ON;
    char_bg[2] = CHAR_BG_B_ON;
    underl[0]  = UNDERL_R_ON;
    underl[1]  = UNDERL_G_ON;
    underl[2]  = UNDERL_B_ON;
    disp_bg[0] = DISP_BG_R_ON;
    disp_bg[1] = DISP_BG_G_ON;
    disp_bg[2] = DISP_BG_B_ON;
  }
  else
  {
    char_fg[0] = CHAR_FG_R_OFF;
    char_fg[1] = CHAR_FG_G_OFF;
    char_fg[2] = CHAR_FG_B_OFF;
    char_bg[0] = CHAR_BG_R_OFF;
    char_bg[1] = CHAR_BG_G_OFF;
    char_bg[2] = CHAR_BG_B_OFF;
    underl[0]  = UNDERL_R_OFF;
    underl[1]  = UNDERL_G_OFF;
    underl[2]  = UNDERL_B_OFF;
    disp_bg[0] = DISP_BG_R_OFF;
    disp_bg[1] = DISP_BG_G_OFF;
    disp_bg[2] = DISP_BG_B_OFF;
  }
  /*set_contrast(void);*/
  /*rst(void);
  refr(void);*/
}

void set_contrast(int val)
{
  /*fprintf(stderr, "val: %i\n"
                  "char_fg: %i %i %i\n"
                  "char_bg: %i %i %i\n"
                  "underl:  %i %i %i\n\n", 
                  val, 
                  char_fg[0], char_fg[1], char_fg[2],
                  char_bg[0], char_bg[1], char_bg[2],
                  underl[0],  underl[1],  underl[2]);*/
  if(val<128)
  {
    char_fg[0]=(int)((double)char_bg[0]*((128-(double)val)/128));
    char_fg[1]=(int)((double)char_bg[1]*((128-(double)val)/128));
    char_fg[2]=(int)((double)char_bg[2]*((128-(double)val)/128));

    /*underl_fg[0]=(int)(double)(underl_bg[0]*((128-val)/128));
    underl_fg[1]=(int)(double)(underl_bg[1]*((128-val)/128));
    underl_fg[2]=(int)(double)(underl_bg[2]*((128-val)/128));*/
  }
  else
  {
    char_bg[0]=(int)((double)char_bg[0]*((255-(double)val)/128));
    char_bg[1]=(int)((double)char_bg[1]*((255-(double)val)/128));
    char_bg[2]=(int)((double)char_bg[2]*((255-(double)val)/128));

    underl[0]=(int)((double)underl[0]*((255-(double)val)/128));
    underl[1]=(int)((double)underl[1]*((255-(double)val)/128));
    underl[2]=(int)((double)underl[2]*((255-(double)val)/128));
  }

  /*fprintf(stderr, "val: %i\n"
                    "char_fg: %i %i %i\n"
                    "char_bg: %i %i %i\n"
                    "underl:  %i %i %i\n\n\n", 
                    val, 
                    char_fg[0], char_fg[1], char_fg[2],
                    char_bg[0], char_bg[1], char_bg[2],
                    underl[0],  underl[1],  underl[2]);*/
}
