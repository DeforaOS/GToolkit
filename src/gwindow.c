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



#include <stdlib.h>
#include <string.h>
#include "common.h"


/* GWindow */
/* private */
/* types */
struct _GWindow
{
	GWidget * gwidget;

	/* GWindow */
	char * title;
	bool decorated;
	bool fullscreen;
	bool resizable;
	int width;
	int height;

	/* not portable */
	Window window;
	GLXContext context;
};


/* prototypes */
static void _gwindow_show(GWindow * gwindow);


/* public */
/* functions */
/* gwindow_new */
GWindow * gwindow_new(void)
{
	Display * display;
	XVisualInfo * visual;
	GWindow * gwindow;
	XSetWindowAttributes attr;
	Atom a;

	if((gwindow = malloc(sizeof(*gwindow))) == NULL)
		return NULL; /* FIXME report */
	if((gwindow->gwidget = gwidget_new()) == NULL)
	{
		free(gwindow);
		return NULL;
	}
	gwidget_set_self(gwindow->gwidget, gwindow);
	gwidget_set_handler(gwindow->gwidget, GWIDGET_HANDLER_SHOW,
			_gwindow_show);
	gwindow->title = NULL;
	gwindow->decorated = true;
	gwindow->fullscreen = false;
	gwindow->resizable = true;
	gwindow->width = -1;
	gwindow->height = -1;
	display = gtoolkit_get_display();
	visual = gtoolkit_get_visual();
	attr.colormap = gtoolkit_get_colormap();
	attr.border_pixel = 0;
	attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
		StructureNotifyMask;
	gwindow->window = XCreateWindow(display,
			RootWindow(display, visual->screen), 0, 0,
			(gwindow->width > 0) ? gwindow->width : 200,
			(gwindow->height > 0) ? gwindow->height : 200,
			0, visual->depth, InputOutput, visual->visual,
			CWBorderPixel | CWColormap | CWEventMask, &attr);
	gwindow->context = glXCreateContext(display, visual, 0, GL_TRUE);
	a = XInternAtom(display, "WM_DELETE_WINDOW", True);
	XSetWMProtocols(display, gwindow->window, &a, 1);
	gtoolkit_register_window(gwindow);
	return gwindow;
}


/* gwindow_delete */
void gwindow_delete(GWindow * gwindow)
{
	gtoolkit_deregister_window(gwindow);
	glXDestroyContext(gtoolkit_get_display(), gwindow->context);
	free(gwindow->title);
	free(gwindow);
}


/* accessors */
/* gwindow_get_decorated */
bool gwindow_get_decorated(GWindow * gwindow)
{
	return gwindow->decorated;
}


/* gwindow_get_modal */
bool gwindow_get_modal(GWindow * gwindow)
{
	return false;
}


/* gwindow_get_resizable */
bool gwindow_get_resizable(GWindow * gwindow)
{
	return gwindow->resizable;
}


/* gwindow_get_size */
void gwindow_get_size(GWindow * gwindow, int * width, int * height)
{
	if(width != NULL)
		*width = gwindow->width;
	if(height != NULL)
		*height = gwindow->height;
}


/* gwindow_get_title */
char const * gwindow_get_title(GWindow * gwindow)
{
	return gwindow->title;
}


/* gwindow_get_window */
Window gwindow_get_window(GWindow * gwindow)
{
	return gwindow->window;
}


/* gwindow_set_resizable */
void gwindow_set_resizable(GWindow * gwindow, bool resizable)
{
	/* FIXME really implement */
	gwindow->resizable = resizable;
}


/* gwindow_set_title */
void gwindow_set_title(GWindow * gwindow, char const * title)
{
	Display * display;

	display = gtoolkit_get_display();
	free(gwindow->title);
	title = (title != NULL) ? title : "(untitled)";
	/* XXX ignore errors */
	gwindow->title = strdup(title);
	if(!gwindow->fullscreen)
		XSetStandardProperties(display, gwindow->window, title, title,
				None, NULL, 0, NULL);
}


/* useful */
/* gwindow_event_configure */
void gwindow_event_configure(GWindow * gwindow, XConfigureEvent * event)
{
	unsigned int width;
	unsigned int height;

	if(event->width == gwindow->width
			&& event->height == gwindow->height)
		return;
	if((gwindow->width = event->width) < 0)
		width = 0;
	if((gwindow->height = event->height) < 1)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}


/* gwindow_event_expose */
void gwindow_event_expose(GWindow * gwindow, XExposeEvent * event)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	/* FIXME redraw the window */
	glXSwapBuffers(event->display, gwindow->window);
}


/* gwindow_resize */
void gwindow_resize(GWindow * gwindow, int width, int height)
{
	gwindow->width = (width == -1 || width > 0) ? width : -1;
	gwindow->height = (height == -1 || height > 0) ? height : -1;
	/* FIXME actually resize the window */
}


/* private */
/* functions */
/* gwindow_show */
static void _gwindow_show(GWindow * gwindow)
	/* FIXME accept flags (focus...) */
{
	Display * display;

	display = gtoolkit_get_display();
	XMapRaised(display, gwindow->window);
	glXMakeCurrent(display, gwindow->window, gwindow->context);
}
