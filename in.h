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

#include "includes.h"
#include "var_exp.h"
#include "defines.h"

extern char dispbuf[2][20][4];
extern cha  chat[16*16];

extern void mess(int mess_kind, char *txt);
extern void putch(unsigned int cod, int x, int y);
extern void disp(void);
extern void rst(void);
extern void refr(void);
extern void set_backlight(bool on);
extern void cursor(bool on, int x, int y);
extern void init_chars(void);
extern void init_char(cha some_char, int char_nr);
extern void set_contrast(int val);

int fifo_comf = -1;
char *pipe_path = "/dev/lcd";

int cur_pos = 0;
bool s_backlight = FALSE;
  bool backlight = TRUE;
int light_time = 0;
bool set_cur_pos = FALSE;
  int curs_x;
  int curs_y;
bool contrast = FALSE; /*TODO change to set_contrast*/
  int contrast_val = 0x80;
bool wrapping = TRUE;  /*TODO change to FALSE when command supported*/
bool scroll = FALSE;
bool new_char = FALSE;
  unsigned int char_nr;
  int bits[8];

bool command_mode = FALSE;
int  command_nr = 0;

void init_in(void);
void close_in(void);
void main_loop(void);
void handle_command(unsigned int ch);
void disp_ch(unsigned int ch);
void add_char(void);
