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

#ifndef CORE_H
#define CORE_H

extern int backlight;
extern int new_char_bits[8];
extern int new_char_nr;

void core_init();

void core_destroy_display();

void core_reset_display();

void core_redraw();

void core_handle_input(unsigned char ch);

void core_handle_command(unsigned char ch);

void core_draw_char(unsigned char ch);

#endif
