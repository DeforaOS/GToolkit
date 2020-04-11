/* $Id$ */



#include <stdlib.h>
#include <string.h>
#include "GToolkit/GWidget.h"
#include "GToolkit/GWindow.h"
#include "common.h"


/* GWindow */
/* private */
/* types */
struct _GWindow
{
#include "gwidget.h"

	/* GWindow */
	char * title;
	Bool fullscreen;
	int width;
	int height;

	/* not portable */
	Window window;
	GLXContext context;
};


/* public */
/* functions */
/* gwindow_new */
GWindow * gwindow_new(void)
{
	Display * display;
	XVisualInfo * visual;
	GWindow * gwindow;
	XSetWindowAttributes attr;

	if((gwindow = malloc(sizeof(*gwindow))) == NULL)
		return NULL; /* FIXME report */
	gwindow->title = NULL;
	gwindow->fullscreen = False;
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


/* gwindow_set_title */
void gwindow_set_title(GWindow * gwindow, char const * title)
{
	Display * display;

	display = gtoolkit_get_display();
	free(gwindow->title);
	/* XXX ignore errors */
	gwindow->title = (title != NULL) ? strdup(title) : NULL;
	if(!gwindow->fullscreen)
		XSetStandardProperties(display, gwindow->window, gwindow->title,
				gwindow->title, None, NULL, 0, NULL);
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


/* gwindow_show */
void gwindow_show(GWindow * gwindow)
	/* FIXME accept flags (focus...) */
{
	Display * display;

	display = gtoolkit_get_display();
	XMapRaised(display, gwindow->window);
	glXMakeCurrent(display, gwindow->window, gwindow->context);
}
