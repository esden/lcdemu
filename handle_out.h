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

#include <math.h>

#include "includes.h"
#include "var_exp.h"
#include "defines.h"
#include "characters.h"

extern char *picture;
extern int  contrast_val;

extern void disp(void);
extern void mess(int mess_kind, char *txt);

int char_fg[3] = CHAR_FG_ON;
int char_bg[3] = CHAR_BG_ON;
int underl[3]  = UNDERL_ON;
int disp_bg[3] = DISP_BG_ON;

char chapt[16*16][15][8];
char dispbuf[2][LCD_WIDTH][LCD_HEIGHT];

void init_chars(void);
void init_char(cha some_char, int char_nr);
void rst(void);
void putch(unsigned int cod, int x, int y);
void cursor(bool on, int x, int y);
void set_backlight(bool on);
void set_contrast(int val);
