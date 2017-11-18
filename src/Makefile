TARGETS	= $(OBJDIR)libGToolkit.a $(OBJDIR)libGToolkit$(SOEXT).0.0 $(OBJDIR)libGToolkit$(SOEXT).0 $(OBJDIR)libGToolkit$(SOEXT)
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
LIBDIR	= $(PREFIX)/lib
CC	= cc
CPPFLAGSF= -I ../include
CPPFLAGS=
CFLAGSF	= -W `pkg-config --cflags gl`
CFLAGS	= -Wall -fPIC -g -O2 -pedantic
EXEEXT	=
AR	= ar
ARFLAGS	= -rc
RANLIB	= ranlib
CCSHARED= $(CC) -shared
SOEXT	= .so
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

libGToolkit_OBJS = $(OBJDIR)common.o $(OBJDIR)gwindow.o $(OBJDIR)gtoolkit.o
libGToolkit_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
libGToolkit_LDFLAGS = $(LDFLAGSF) $(LDFLAGS) `pkg-config --libs gl`

$(OBJDIR)libGToolkit.a: $(libGToolkit_OBJS)
	$(AR) $(ARFLAGS) $(OBJDIR)libGToolkit.a $(libGToolkit_OBJS)
	$(RANLIB) $(OBJDIR)libGToolkit.a

$(OBJDIR)libGToolkit$(SOEXT).0.0: $(libGToolkit_OBJS)
	$(CCSHARED) -o $(OBJDIR)libGToolkit$(SOEXT).0.0 -Wl,-soname,libGToolkit$(SOEXT).0 $(libGToolkit_OBJS) $(libGToolkit_LDFLAGS)

$(OBJDIR)libGToolkit$(SOEXT).0: $(OBJDIR)libGToolkit$(SOEXT).0.0
	$(LN) -s -- libGToolkit$(SOEXT).0.0 $(OBJDIR)libGToolkit$(SOEXT).0

$(OBJDIR)libGToolkit$(SOEXT): $(OBJDIR)libGToolkit$(SOEXT).0.0
	$(LN) -s -- libGToolkit$(SOEXT).0.0 $(OBJDIR)libGToolkit$(SOEXT)

$(OBJDIR)common.o: common.c
	$(CC) $(libGToolkit_CFLAGS) -o $(OBJDIR)common.o -c common.c

$(OBJDIR)gwindow.o: gwindow.c
	$(CC) $(libGToolkit_CFLAGS) -o $(OBJDIR)gwindow.o -c gwindow.c

$(OBJDIR)gtoolkit.o: gtoolkit.c
	$(CC) $(libGToolkit_CFLAGS) -o $(OBJDIR)gtoolkit.o -c gtoolkit.c

clean:
	$(RM) -- $(libGToolkit_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(PREFIX)/lib
	$(INSTALL) -m 0644 $(OBJDIR)libGToolkit.a $(DESTDIR)$(PREFIX)/lib/libGToolkit.a
	$(INSTALL) -m 0755 $(OBJDIR)libGToolkit$(SOEXT).0.0 $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT).0.0
	$(LN) -s -- libGToolkit$(SOEXT).0.0 $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT).0
	$(LN) -s -- libGToolkit$(SOEXT).0.0 $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT)

uninstall:
	$(RM) -- $(DESTDIR)$(PREFIX)/lib/libGToolkit.a
	$(RM) -- $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT).0.0
	$(RM) -- $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT).0
	$(RM) -- $(DESTDIR)$(PREFIX)/lib/libGToolkit$(SOEXT)

.PHONY: all clean distclean install uninstall
