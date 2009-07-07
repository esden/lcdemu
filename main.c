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

#include "main.h"

int main(int argc, char **argv)
{
  int i;
  bool recog=FALSE;
  /*fprintf(stderr, "main %i \n", argc);*/

  fprintf(stderr,
          "\nlcdemu "VERSION", Copyright 1999 by Piotr Esden-Tempski\n"
          "This program is distributed under the terms of the "
          "General Public License.\n"
          "For details on the license, please see COPYING.\n\n");

  for(i=1; i<argc; i++)
  {
    /*fprintf(stderr, "%i", i);*/
    recog=FALSE;
    if((0 == strcmp(argv[i], "-d")) || (0 == strcmp(argv[i], "--device")))
    {
      pipe_path=argv[++i];
      recog=TRUE;
      /*fprintf(stderr, "pipe %s \n", argv[i]);*/
    }
    else
    {
      if((0 == strcmp(argv[i], "-h")) || (0 == strcmp(argv[i], "--help")))
      {
        help();
        recog=TRUE;
      }
      else
      {
        if((0 == strcmp(argv[i], "-V")) || (0 == strcmp(argv[i], "--version")))
        {
          print_version();
          recog=TRUE;
        }
      }
    }
    if(!recog)
    {
      fprintf(stderr, "Invalid parameter: %s\n", argv[i]);
    }
  }

  init_emu();
  run_emu();
  close_emu();
  return 0;
}
