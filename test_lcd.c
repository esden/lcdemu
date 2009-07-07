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

#include <stdio.h>
#include <stdlib.h>

#define VERSION "0.5"

void help(void)
{
  fprintf(stderr, "Keysrokes:\n");
  fprintf(stderr, "C: Line wrapping on.\n");
  fprintf(stderr, "D: Line wrapping off.\n");
  fprintf(stderr, "B: Turn light on.\n");
  fprintf(stderr, "F: Turn light off.\n");
  fprintf(stderr, "X: Clear display.\n");
  fprintf(stderr, "P: Set contrast.\n");
  fprintf(stderr, "J: Set the cursor in the current position on.\n");
  fprintf(stderr, "K: Unset the cursor in the current position.\n");
  fprintf(stderr, "L: Move the cursor to the left.\n");
  fprintf(stderr, "M: Move the cursor to the right.\n");
  fprintf(stderr, "G: Set the cursor position.\n");
  fprintf(stderr, "t: Print the test text.\n");  
  fprintf(stderr, "c: Print test character.\n");  
  fprintf(stderr, "s: Set new char and print.\n");  
  fprintf(stderr, "n: Use nonexistent command.\n");
  fprintf(stderr, "h: Print this help.\n");
  fprintf(stderr, "q: Quit\n");
}

int main(void)
{
  char ch;
  char *rch;
  int  backlight_time;
  int  *cur_x;
  int  *cur_y;
  int  *contrast;
  rch=malloc(2);
  ch=254;
  backlight_time=0;

  fprintf(stderr, "Welcome to LCD-emu test program.\n\n");
  help();

  rch[0]='*';

  for(;;)
  {
    if(rch[0]!='\n') fprintf(stderr, "\nEnter command ('h' for help): ");
    scanf("%c",rch);
    switch(rch[0])
    {
      case 'C':
        printf("%cC",ch);
        fflush(stdout);
      break;
      case 'D':
        printf("%cD",ch);
        fflush(stdout);
      break;
      case 'B':
        printf("%cB%c", ch, backlight_time);
        fflush(stdout);
      break;
      case 'F':
        printf("%cF",ch);
        fflush(stdout);
      break;
      case 'X':
        printf("%cX",ch);
        fflush(stdout);
      break;
      case 'P':
        fprintf(stderr, "val: ");
        scanf("%i", &contrast);
        printf("%cP%c", ch, contrast);
        fflush(stdout);
      break;
      case 'J':
        printf("%cJ",ch);
        fflush(stdout);
      break;
      case 'K':
        printf("%cK",ch);
        fflush(stdout);
      break;
      case 'L':
        printf("%cL",ch);
        fflush(stdout);
      break;
      case 'M':
        printf("%cM",ch);
        fflush(stdout);
      break;
      case 'G':
        fprintf(stderr, "x:");
        scanf("%i", &cur_x);
        fprintf(stderr, "y:");
        scanf("%i", &cur_y);
        printf("%cG%c%c", ch, cur_x, cur_y);
        fflush(stdout);
      break;
      case 't':
      printf("      LCD-emu           version "VERSION"           by         Piotr  Esden-Tempski");
      fflush(stdout);
      break;
      case 'c':
        printf("%c",'C');
        fflush(stdout);
      break;
      case 's':
        printf("%cN%c%c%c%c%c%c%c%c%c",ch,0,31,31,31,31,31,31,31,31);
        printf("%c",0);
        fflush(stdout);
      break;
      case 'n':
        printf("%cn",ch);
        fflush(stdout);
      break;
      case 'h':
        help();
      break;
      case 'q':
        return(0);
      break; 
    }
  }
  return(0);
}
