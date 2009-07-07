## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	@PACKAGE_CFLAGS@

AM_CFLAGS = -Wall

bin_PROGRAMS = lcdemu

lcdemu_SOURCES = \
	main.c main.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	bg.xpm.h char.xpm.h \
	bg-off.xpm.h char-off.xpm.h \
	draw_char.c draw_char.h \
	input.c input.h \
	core.c core.h \
	defines.h

lcdemu_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

