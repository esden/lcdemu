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

#include "char.xpm.h"
#include "char-off.xpm.h"
#include "bg.xpm.h"
#include "bg-off.xpm.h"

#include "interface.h"
#include "callbacks.h"
#include "main.h"
#include "core.h"
#include "defines.h"

#include "draw_char.h"

#define true 1
#define false 0

GdkPixmap *chars_on = NULL;
GdkPixmap *chars_off = NULL;

GdkPixmap *bg_on = NULL;
GdkPixmap *bg_off = NULL;

void init_chars( void ) {
	GdkBitmap *chars_mask;
	GtkStyle *style;
	//g_print("init_chars\n");
	style = gtk_widget_get_style ( lcdemu_window );
	chars_on = gdk_pixmap_create_from_xpm_d ( lcdemu_window->window, &chars_mask, &style->bg[GTK_STATE_NORMAL], (gchar **)char_xpm);
	chars_off = gdk_pixmap_create_from_xpm_d ( lcdemu_window->window, &chars_mask, &style->bg[GTK_STATE_NORMAL], (gchar **)char_off_xpm);
}

void init_bg() {
	GdkBitmap *bg_mask;
	GtkStyle *style;
	//g_print("init_bg\n");
	style = gtk_widget_get_style ( lcdemu_window );
	bg_on = gdk_pixmap_create_from_xpm_d ( lcdemu_window->window, &bg_mask, &style->bg[GTK_STATE_NORMAL], (gchar **)bg_xpm);
	bg_off = gdk_pixmap_create_from_xpm_d ( lcdemu_window->window, &bg_mask, &style->bg[GTK_STATE_NORMAL], (gchar **)bg_off_xpm);
}

void draw_bg() {
	GdkRectangle update_rect;
	GdkGC *gc;

	gc = gdk_gc_new(backing_pixmap);

	gdk_draw_drawable(backing_pixmap, gc, (backlight==true)?bg_on:bg_off, 0, 0, 0, 0, 121, 37);

	g_object_unref(gc);

	update_rect.x = 0;
	update_rect.y = 0;
	update_rect.width = 121;
	update_rect.height = 37;
        gtk_widget_queue_draw_area (drawing_area, 
		                    update_rect.x, update_rect.y,
		                    update_rect.width, update_rect.height);
}

void draw_char(unsigned char ch, int x, int y) {
	GdkRectangle update_rect;
	GdkGC *gc;

	gc = gdk_gc_new(backing_pixmap);

	gdk_draw_drawable(backing_pixmap, gc, (backlight==true)?chars_on:chars_off, 0, ch*8, x*6+1, y*9+1, 5, 8);

	g_object_unref(gc);
	
	update_rect.x = x*6+1;
	update_rect.y = y*9+1;
	update_rect.width = 5;
	update_rect.height = 8;
        gtk_widget_queue_draw_area (drawing_area, 
		                    update_rect.x, update_rect.y,
		                    update_rect.width, update_rect.height);
}

void reset_display() {
	int i, j;

	for (i=0; i<20; i++) {
		for (j=0; j<4; j++) {
			draw_char(' ', i, j);
		}
	}
}

void add_char() {
	int i, j;
	int mask;
	GdkGC *gc;
	GdkColor color;
	GdkColormap *colormap;
#ifdef DEBUG
	char debug_str[7];
	debug_str[5]='\n';
	debug_str[6]='\0';
#endif

	color.red = 0;
	color.green = 0;
	color.blue = 0;

	colormap = gdk_drawable_get_colormap(GDK_DRAWABLE (backing_pixmap) );

	gdk_colormap_alloc_color(colormap, &color, 1, 0);

	gc = gdk_gc_new(backing_pixmap);

	gdk_gc_set_foreground(gc, &color);

	gdk_draw_drawable(chars_on, gc, chars_on, 0, ' '*8, 0, new_char_nr*8, 5, 8);
	gdk_draw_drawable(chars_off, gc, chars_off, 0, ' '*8, 0, new_char_nr*8, 5, 8);

	for (i=0; i<8; i++) {
		mask = 1;
		for (j=0; j<5; j++) {
			if ((new_char_bits[i] & mask)) {
#ifdef DEBUG
				debug_str[4-j]='#';
#endif
				gdk_draw_point(chars_on, gc, 4-j, new_char_nr*8+i);
				gdk_draw_point(chars_off, gc, 4-j, new_char_nr*8+i);
			} 
#ifdef DEBUG
			  else {
				debug_str[4-j]='.';
			}
#endif
			mask = mask << 1;
		}
		g_debug(debug_str);
	}
}
