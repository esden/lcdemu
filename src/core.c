/* lcdemu - emulator of Matrix Orbital(R) lcd displays
   Copyright (C) 1999-2002 Piotr Esden-Tempski

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

#include <string.h>
#include <stdlib.h>
#include <glib.h>

#include "draw_char.h"
#include "defines.h"

#include "core.h"

#define bool int

#define true 1
#define false 0

unsigned char **display_buff;

int command_mode = false;

int cursor_pos_x = 0;
int cursor_pos_y = 0;

//bool can_print = true;

bool scrolling = false;

int command_nr = 0;

bool contrast_val = 128;

bool set_backlight = false;
	int backlight = true;
bool set_contrast = false;
bool set_current_pos = false;
bool new_char = false;
	int new_char_nr;
	int new_char_bits[8];
bool set_big_num = false;
unsigned char light_time;

void core_print_wellcome() {
	int i;
	unsigned char str0[] = "      LCD-emu       ";
	unsigned char str1[] = "version "VERSION;
	unsigned char str2[] = "         by         ";
	unsigned char str3[] = "Piotr  Esden-Tempski";
	
	for(i=0;i<20;i++) {
		core_draw_char(str0[i]);
	}
	cursor_pos_x = (20-strlen(str1))/2;
	cursor_pos_y = 1;
	for(i=0; i<strlen(str1) && i<20; i++) {
		core_draw_char(str1[i]);	
	}
	cursor_pos_x=0;
	cursor_pos_y=2;
	for(i=0;i<20;i++) {
		core_draw_char(str2[i]);
	}
	for(i=0;i<20;i++) {
		core_draw_char(str3[i]);
	}
	
	cursor_pos_x=0;
	cursor_pos_y=0;
}

void core_init() {
	int i;
	
	display_buff=(void *)malloc(sizeof(void *) * 4);
	for (i=0; i<4; i++) {
		display_buff[i]=(char *)malloc(20);
	}

	core_reset_display();
	core_print_wellcome();
}

void core_destroy_display() {
}

void core_reset_display() {
	int i, j;

	for (i=0; i<4; i++) {
		for (j=0; j<20; j++) {
			display_buff[i][j]=' ';
		}
	}
	cursor_pos_x=0;
	cursor_pos_y=0;
	//can_print = true;
	core_redraw();
}

/* only for debugging */
#ifdef DEBUG_BUF_DUMP
void core_draw_buf() {
	int i, j;
	g_print("Draw buffer dump:\n");
	for (i=0; i<4; i++) {
		for (j=0; j<20; j++) {
			g_print("%X ", display_buff[i][j]);
		}
		g_print("\n");
	}
}
#endif

void core_scroll() {
	int i;
	for (i=0; i<3; i++) {
		strncpy(display_buff[i], display_buff[i+1], 20);
	}
	for (i=0; i<20; i++) {
		display_buff[3][i] = ' ';
	}
}

void core_redraw() {
	int i, j;

	draw_bg();
	for (i=0; i<20; i++) {
		for (j=0; j<4; j++) {
			draw_char(display_buff[j][i], i, j);
		}
	}
}

void core_inc_cursor() {
	if ( cursor_pos_y < 4 ) {
		if ( cursor_pos_x < 19 ) {
			cursor_pos_x++;
		} else {
			if( cursor_pos_y < 3 ) {
				cursor_pos_x = 0;
				cursor_pos_y++;
			}
		}
	}
}

void core_dec_cursor() {
	if ( cursor_pos_x > 0 ) {
		cursor_pos_x--;
	} else {
		if(cursor_pos_y>0) {
			cursor_pos_x=19;
			cursor_pos_y--;
		}
	}
}

void core_draw_char( unsigned char ch ) {
	g_debug("core_draw_char called");
	
	if( cursor_pos_y == 4 ) {
		if ( scrolling ) {
			core_scroll();
			core_redraw();
			cursor_pos_y = 3;
		} else {
			g_warning("You try to draw outside the display, reset display or turn on scrolling.");
			return;
		}
	}
	
	if( (( display_buff[cursor_pos_y][cursor_pos_x] != ch ) || ch < 8 ) /* && can_print */) {
		draw_char( ch, cursor_pos_x, cursor_pos_y );
		display_buff[cursor_pos_y][cursor_pos_x] = ch;
	}
#ifdef DEBUG_BUF_DUMP
	core_draw_buf();
#endif
	core_inc_cursor();
}

void core_handle_command( unsigned char ch ) {
	if(command_nr==0)
	{
		switch (ch) {
			case 'C': /* Line wrapping on */
				g_warning("Line wrapping on not implemented.");
				/*wrapping=TRUE;*/
				command_mode=false;
				break;

			case 'D': /* Line wrapping off */
				g_warning("Line wrapping off not implemented.");
				/*wrapping=FALSE;*/
				command_mode=false;
				break;

			case 'Q': /* Scrolling on TODO fully implement*/
				scrolling=true;
				//can_print=true;
				command_mode=false;
				break;

			case 'R': /* Scrolling off */
				scrolling=false;
				command_mode=false;
				break;
			case 'B': /* Backlight on */
				backlight=true;
				core_redraw();
				set_backlight=true;
				command_nr++;
				break;

			case 'F': /* Backlight off */
				backlight=false;
				core_redraw();
				command_mode=false;
				break;

			case 'X': /* Clear display */
				core_reset_display();
				command_mode=false;
				break;

			case 'P': /*Set contrast*/
				g_warning("Contrast setting not implemented.");
				set_contrast=true;
				command_nr++;
				break;

			case 'J': /* Set the cursor at the current position on */
				g_warning("Set cursor at the current position on not implemented.");
				/*cursor(TRUE, cur_pos%LCD_WIDTH, (cur_pos-cur_pos%LCD_WIDTH)/LCD_WIDTH);
				refr();*/
				command_mode=false;
				break;

			case 'K': /* Unset the cursor in the current position */
				g_warning("Set cursor at the current position off not implemented.");
				/*cursor(FALSE, cur_pos%LCD_WIDTH, (cur_pos-cur_pos%LCD_WIDTH)/LCD_WIDTH);
				refr();*/
				command_mode=false;
				break;

			case 'L': /* Move the current position to the left */
				core_dec_cursor();
				command_mode=false;
				break;

			case 'M': /* Move the current position to the right */
				core_inc_cursor();
				command_mode=false;
				break;

			case 'N': /*Set custom character*/
				new_char=true;
				command_nr++;
				break;

			case 'G': /*Set current position*/
				set_current_pos=true;
				command_nr=1;
				break;
			
			case 'V': /*Set output on don't know if it is needed*/
				g_warning("Setting output on not implemented.");
				command_mode=false;
				break;

			case 'W': /*Set output on don't know if it is needed*/
				g_warning("Setting output off not implemented.");
				command_mode=false;
				break;
			
			case 'S': /*Set blinking cursor on TODO implement*/
				g_warning("Setting blinking cursor on not implemented.");
				command_mode=false;
				break;

			case 'T': /*Set blinking cursor off TODO implement*/
				g_warning("Setting blinking cursor off not implemented.");
				command_mode=false;
				break;

			case 'n': /*Initialize Big Digit mode*/
				g_warning("Initializing big digit not implemented.");
				command_mode=false;
				break;

			case '#': /*Write big number TODO implement correctly*/
				g_warning("Writing a big digit not implemented.");
				set_big_num=false;
				command_nr=1;
				break;

			default:
				g_warning("This command is not implemented.(%c)", ch);
				/*mess(LCD_WRN, "This command is not implemented.\n");*/

				/*char *dumy;*/
				/*sprintf(dumy, "This command is not implemented.()\n");
				  mess(LCD_WRN, dumy); FIXME it brings allways Segmentation fault, why?*/

				command_mode=false;
				break;
		}
	}
	else
	{
		if(set_backlight)
		{
			light_time=ch;
			/* mess(LCD_INF, "light_time set to: %i\n", light_time); TODO do usable */
			set_backlight=false;
			command_nr=0;
			command_mode=false;
		}

		if(set_current_pos)
		{
			if(command_nr==1)
			{
				if (ch<21 && ch>0) {
					cursor_pos_x=ch-1;
					//can_print = true;
				} else {
					g_warning("Tryed to move the cursor out of display.");
				}
				command_nr++;
			}
			else
			{
				if (ch<5 && ch>0) {
					cursor_pos_y=ch-1;
					//can_print = true;
				} else {
					g_warning("Tryed to move the cursor out of display.");
				}
				g_debug("cursor set to x=%i y=%i", cursor_pos_x, cursor_pos_y);
				set_current_pos=false;
				command_nr=0;
				command_mode=false;
			}
		}

		if(set_contrast)
		{
			/*char *dum;*/
			contrast_val=ch;
			/*set_backlight(backlight);
			set_contrast(contrast_val);
			init_chars();
			refr();*/
			g_debug("contrast_val set to: %i", contrast_val);
			/*  mess(LCD_INF, dum); TODO uncomment*/
			set_contrast=false;
			command_nr=0;
			command_mode=false;
		}

		if(new_char)
		{
			if(command_nr==1)
			{
				new_char_nr=ch;
				command_nr++;
			}
			else
			{
				new_char_bits[command_nr-2]=ch;
				if(command_nr==9)
				{
					g_debug("created new char: %X", new_char_nr);
					add_char();
					/* fprintf(stderr, "Info: New char: %i\n", char_nr); TODO do usable */
					new_char=false;
					command_nr=0;
					command_mode=false;
				}
				else
				{
					command_nr++;
				}
			}
		}

		if(set_big_num){
			if(command_nr==1){
				/*cur_pos = ch;
				command_nr=2;*/
			}else{
				//disp_ch(ch+30);
				/* fprintf(stderr, "%X, %X", ch, cur_pos); removed for demo */
				command_nr=0;
				set_big_num=false;
				command_mode=false;
			}
		}

	}

}

void core_handle_input(unsigned char ch) {
	if (!command_mode) {
		if (ch == 254) {
			g_debug("Switching to command mode.");
			command_mode = 1;
		} else {
			core_draw_char(ch);
		}
	} else {
		core_handle_command(ch);
	}
}
