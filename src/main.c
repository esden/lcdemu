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

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include "interface.h"
#include "input.h"
#include "core.h"
#include "draw_char.h"
#include "defines.h"

#include "main.h"

GtkWidget *lcdemu_window;

int main( int   argc, 
          char *argv[] )
{

  gtk_init (&argc, &argv);

  lcdemu_window = create_lcdemu_window();
  
  init_input();
  
  gtk_widget_show(lcdemu_window);

  init_chars();
  init_bg();

  g_debug("core_init ...\n");
  core_init();

  //gdk_window_withdraw(lcdemu_window->window);
  XWMHints mywmhints;
  mywmhints.initial_state = WithdrawnState;
  mywmhints.flags=StateHint;
  
  XSetWMHints(GDK_DISPLAY(),
		  GDK_WINDOW_XWINDOW(lcdemu_window->window), &mywmhints);

  
  gtk_main ();

  return 0;
}
