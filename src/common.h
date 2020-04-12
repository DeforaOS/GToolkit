/* $Id$ */
/* Copyright (c) 2006-2020 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Graphics GToolkit */
/* All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */



#ifndef GTOOLKIT_COMMON_H
# define GTOOLKIT_COMMON_H

# include <X11/Xlib.h>
# include <GL/glu.h>
# include <GL/glx.h>
# include <GToolkit.h>


/* types */
typedef enum _GWidgetHandler
{
	GWIDGET_HANDLER_SHOW = 0
} GWidgetHandler;
# define GWIDGET_HANDLER_LAST GWIDGET_HANDLER_SHOW
# define GWIDGET_HANDLER_COUNT (GWIDGET_HANDLER_LAST + 1)


/* functions */
/* GToolkit */
/* accessors */
Display * gtoolkit_get_display(void);
Colormap gtoolkit_get_colormap(void);
XVisualInfo * gtoolkit_get_visual(void);

/* useful */
void gtoolkit_register_window(GWindow * gwindow);
void gtoolkit_deregister_window(GWindow * gwindow);


/* GWidget */
GWidget * gwidget_new(void);
void gwidget_delete(GWidget * gwidget);

/* useful */
void gwidget_set_handler(GWidget * gwidget, GWidgetHandler handler, ...);
void gwidget_set_self(GWidget * gwidget, void * self);


/* GWindow */
/* accessors */
Window gwindow_get_window(GWindow * gwindow);

/* useful */
void gwindow_event_configure(GWindow * gwindow, XConfigureEvent * event);
void gwindow_event_expose(GWindow * gwindow, XExposeEvent * event);
void gwindow_event_map(GWindow * gwindow, XMapEvent * event);

#endif
