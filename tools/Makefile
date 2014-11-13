TARGETS	= $(OBJDIR)test
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
CC	= cc
CPPFLAGSF= -I ../include
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -fPIC -g -O2 -pedantic
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

test_OBJS = $(OBJDIR)test.o
test_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
test_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) -L$(OBJDIR). -L../src -L $(PREFIX)/lib -Wl,-rpath,$(PREFIX)/lib -lGToolkit

$(OBJDIR)test: $(test_OBJS)
	$(CC) -o $(OBJDIR)test $(test_OBJS) $(test_LDFLAGS)

$(OBJDIR)test.o: test.c ../include/GToolkit.h
	$(CC) $(test_CFLAGS) -o $(OBJDIR)test.o -c test.c

clean:
	$(RM) -- $(test_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
