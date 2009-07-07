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
#include <stdlib.h>

#include "bg.xpm.h"

#include "interface.h"
#include "input.h"

#include "callbacks.h"

GdkPixmap *backing_pixmap = NULL;

/* Create a new backing pixmap of the appropriate size */
gint configure_event( GtkWidget *widget, GdkEventConfigure *event ) {
	GdkBitmap *mask;
	GtkStyle *style;

	if (backing_pixmap)
	  	g_object_unref (backing_pixmap);

		style = gtk_widget_get_style (widget);
	backing_pixmap = gdk_pixmap_create_from_xpm_d (widget->window,  &mask,
		  				&style->bg[GTK_STATE_NORMAL],
						(gchar **)bg_xpm);
	//core_redraw();
	return TRUE;
}

/* Redraw the screen from the backing pixmap */
gint expose_event( GtkWidget *widget, GdkEventExpose *event ) {
	gdk_draw_drawable (widget->window,
			widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
			backing_pixmap,
			event->area.x, event->area.y,
			event->area.x, event->area.y,
			event->area.width, event->area.height);

	return FALSE;
}

/* close program */
void quit () {
	exit (EXIT_SUCCESS);
}

/* handle incoming data */
void data_in ( gpointer foo, gint source, GdkInputCondition condition ) {
	handle_input();
}

/*  */
void data_destroy( gpointer foo ) {
	//g_print("data_destroy called\n");
}
