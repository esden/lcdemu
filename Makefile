#  lcdemu - emulator of Matrix Orbital(R) lcd displays
#  Copyright (C) 1999 Piotr Esden-Tempski
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

SHELL=/bin/sh

PROGRAM = lcdemu.prog
VERSION = 0.5

#the device lcdproc is hooked up to
DEVICE = /dev/lcd

CC = gcc

#output *lots* of Warnings
#CFLAGS = -Wall -O -pedantic -ansi -Wshadow -Wpointer-arith -Wcast-qual -Wwrite-strings

#not *that* many Warnings but very good optimization
#CFLAGS = -Wall -O3 -pedantic -ansi -funsigned-char
CFLAGS = -Wall -O -pedantic -ansi -funsigned-char
#CFLAGS = -Wall -O -pedantic -ansi




MAINFILE = main
OBJECTS = $(MAINFILE).o init_emu.o run_emu.o close_emu.o mess.o out.o handle_out.o in.o goodies.o
INSTALL = /usr/bin/install -c

prefix = /usr/local
bindir = $(prefix)/bin

all: $(PROGRAM)

goodies.o: goodies.c goodies.h includes.h var_exp.h defines.h
	$(CC) -c $(CFLAGS) $<

in.o: in.c in.h includes.h var_exp.h defines.h
	$(CC) -c $(CFLAGS) $<

handle_out.o: handle_out.c handle_out.h includes.h var_exp.h defines.h characters.h
	$(CC) -c $(CFLAGS) $<

mess.o: mess.c mess.h includes.h var_exp.h defines.h
	$(CC) -c $(CFLAGS) $<

out.o: out.c out.h includes.h var_exp.h defines.h
	$(CC) -c $(CFLAGS) $<

init_emu.o: init_emu.c init_emu.h includes.h var_exp.h
	$(CC) -c $(CFLAGS) $<

run_emu.o: run_emu.c run_emu.h includes.h var_exp.h defines.h
	$(CC) -c $(CFLAGS) $<

close_emu.o: close_emu.c close_emu.h includes.h var_exp.h
	$(CC) -c $(CFLAGS) $<

$(MAINFILE).o: $(MAINFILE).c $(MAINFILE).h var_def.h includes.h
	$(CC) -c $(CFLAGS) $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM)

install:
	@if [ ! -e $(DEVICE) ]; then mkfifo $(DEVICE) ; chmod 666 $(DEVICE); fi
	$(INSTALL) $(PROGRAM) $(bindir)/$(PROGRAM)
	$(INSTALL) lcdemu $(bindir)/lcdemu

clean:
	rm -f *.o core *~

distclean:
	rm -f $(PROGRAM) *.o core *~

archive:
	mkdir -p lcdemu-$(VERSION)/scripts
	cp AUTHORS COPYING ChangeLog INSTALL MANIFEST Makefile README TODO \
	characters.h close_emu.c close_emu.h defines.h handle_out.c \
	handle_out.h in.c in.h includes.h init_emu.c init_emu.h main.c main.h \
	mess.c mess.h out.c out.h run_emu.c run_emu.h var_def.h var_exp.h \
	lcdemu start_test test_lcd.c goodies.c goodies.h lcdemu-$(VERSION)
	cp scripts/start scripts/stop lcdemu-$(VERSION)/scripts
	chmod 755 lcdemu-$(VERSION)
	chmod 644 lcdemu-$(VERSION)/*
	chmod 755 lcdemu-$(VERSION)/lcdemu
	chmod 755 lcdemu-$(VERSION)/start_test
	chmod 755 lcdemu-$(VERSION)/scripts
	tar cfvz lcdemu-$(VERSION).tar.gz lcdemu-$(VERSION)
	rm -rf lcdemu-$(VERSION)

bz2archive:
	mkdir -p lcdemu-$(VERSION)/scripts
	cp AUTHORS COPYING ChangeLog INSTALL MANIFEST Makefile README TODO \
	characters.h close_emu.c close_emu.h defines.h handle_out.c \
	handle_out.h in.c in.h includes.h init_emu.c init_emu.h main.c main.h \
	mess.c mess.h out.c out.h run_emu.c run_emu.h var_def.h var_exp.h \
	lcdemu start_test test_lcd.c goodies.c goodies.h lcdemu-$(VERSION)
	cp scripts/start scripts/stop lcdemu-$(VERSION)/scripts
	chmod 755 lcdemu-$(VERSION)
	chmod 644 lcdemu-$(VERSION)/*
	chmod 755 lcdemu-$(VERSION)/lcdemu
	chmod 755 lcdemu-$(VERSION)/start_test
	chmod 755 lcdemu-$(VERSION)/scripts
	tar cfvI lcdemu-$(VERSION).tar.bz2 lcdemu-$(VERSION)
	rm -rf lcdemu-$(VERSION)
