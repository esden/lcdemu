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

#define BOOL_TYPE char

typedef BOOL_TYPE bool; 
/*Character data*/
typedef char cha[8][5];

/*Uncomment to use the demo modus*/
/*#define DEMO*/

#define VERSION "0.5"

#define LCD_ERR 0
#define LCD_WRN 1
#define LCD_DBG 2
#define LCD_INF 3

#define LCD_WIDTH   20
#define LCD_HEIGHT  4

#define ZUT_WIDTH   121
#define ZUT_HEIGHT  37

#define TRUE  ((bool)1)
#define FALSE (!TRUE)

#define CHAR_FG_R_ON    0
#define CHAR_FG_G_ON    0
#define CHAR_FG_B_ON    0
#define CHAR_BG_R_ON  120
#define CHAR_BG_G_ON  184
#define CHAR_BG_B_ON    0
#define UNDERL_R_ON   136
#define UNDERL_G_ON   200
#define UNDERL_B_ON     0
#define DISP_BG_R_ON  144
#define DISP_BG_G_ON  216
#define DISP_BG_B_ON    0

#define CHAR_FG_R_OFF   0
#define CHAR_FG_G_OFF   0
#define CHAR_FG_B_OFF   0
#define CHAR_BG_R_OFF  20
#define CHAR_BG_G_OFF  84
#define CHAR_BG_B_OFF   0
#define UNDERL_R_OFF   36
#define UNDERL_G_OFF  100
#define UNDERL_B_OFF    0
#define DISP_BG_R_OFF  44
#define DISP_BG_G_OFF 116
#define DISP_BG_B_OFF   0

#define CHAR_FG_ON  {CHAR_FG_R_ON, CHAR_FG_G_ON, CHAR_FG_B_ON}
#define CHAR_BG_ON  {CHAR_BG_R_ON, CHAR_BG_G_ON, CHAR_BG_B_ON}
#define UNDERL_ON   {UNDERL_R_ON,  UNDERL_G_ON,  UNDERL_B_ON}
#define DISP_BG_ON  {DISP_BG_R_ON, DISP_BG_G_ON, DISP_BG_B_ON}

#define CHAR_FG_OFF {CHAR_FG_R_OFF, CHAR_FG_G_OFF, CHAR_FG_B_OFF}
#define CHAR_BG_OFF {CHAR_BG_R_OFF, CHAR_BG_G_OFF, CHAR_BG_B_OFF}
#define UNDERL_OFF  {UNDERL_R_OFF,  UNDERL_G_OFF,  UNDERL_B_OFF}
#define DISP_BG_OFF {DISP_BG_R_OFF, DISP_BG_G_OFF, DISP_BG_B_OFF}
