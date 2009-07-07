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

#include <gdk/gdk.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "callbacks.h"
#include "draw_char.h"
#include "core.h"
#include "defines.h"

#include "input.h"

int lcd_fifo=-1;

unsigned char *in_ch;

void init_input() {
	lcd_fifo = open("/dev/lcd", O_RDWR);
	in_ch = malloc(1);

	gdk_input_add_full(lcd_fifo, GDK_INPUT_READ, data_in, NULL, data_destroy);
}

void handle_input() {
	int ret;
	unsigned char *ch;
	ch = (unsigned char *)malloc(1);
	g_debug("data_in handler called ...\n");

	//if (read(lcd_fifo, ch, 1024)>0){
		ret = read(lcd_fifo, in_ch, 1);
		if (ret == -1 ) {
			g_error("returned zero!\n");
		}
		if (ret == 0 ) {
			g_error("returned eof!\n");
		}
#ifdef DEBUG_ECHO
		fprintf(stderr, "%c", in_ch[0]);
#endif
		g_debug("%c", in_ch[0]);

		//draw_char( ch[0], 0, 0 );
	
	//	i=0;
	//	while(ch[i]!='\0') {
			core_handle_input(in_ch[0]);
	//		i++;
	//	}
	//}
	free(ch);
}
