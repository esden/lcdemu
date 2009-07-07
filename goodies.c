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

#include "goodies.h"

void demo(void)
{
  int i, j, k, l;
  /* Display characters */
  for(k=0;;k++)
  {
    for(i=0;i<20;i++)
    {
      for(j=0;j<4;j++)
      {
        putch(((j+k)*20+i)%256,i,j);
      }
    }
    disp();
    l=sleep(1);
  }
}

void welcome(void)
{
  char *str;
  int i;
  str="      LCD-emu           version "VERSION"              by         Piotr  Esden-Tempski";
  for(i=0;i<80;i++)
  {
    disp_ch(str[i]);
  }
  handle_command('G');
  handle_command(1);
  handle_command(1);
}

void help(void)
{
  fprintf(stderr, "\nlcdemu -- an emulator of Matrix Orbital(R) lcd displays\n");
  fprintf(stderr, "Usage: lcdemu [-d /dev/xxxx] [-h] [-V]\n");
  fprintf(stderr, " -d, --device                use /dev/xxxx as device instead of /dev/lcd\n");
  fprintf(stderr, " -h, --help                  show this help and exit\n");
  fprintf(stderr, " -V, --version               output version information and exit\n\n");
  exit(0);
}

void print_version(void)
{
 fprintf(stderr,"\n%s\n\n", VERSION);
 exit(0);
}
