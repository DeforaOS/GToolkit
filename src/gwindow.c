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
	display = gtoolkit_get_display();
	visual = gtoolkit_get_visual();
	/* FIXME colormap defined in g_init()? */
	attr.colormap = XCreateColormap(display,
			RootWindow(display, visual->screen),
			visual->visual, AllocNone);
	attr.border_pixel = 0;
	attr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
		StructureNotifyMask;
	gwindow->window = XCreateWindow(display,
			RootWindow(display, visual->screen), 0, 0,
			200, 200, 0, visual->depth, InputOutput,
			visual->visual,
			CWBorderPixel | CWColormap | CWEventMask, &attr);
	gwindow->context = glXCreateContext(display, visual, 0, GL_TRUE);
	return gwindow;
}


/* gwindow_delete */
void gwindow_delete(GWindow * gwindow)
{
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
/* gwindow_show */
void gwindow_show(GWindow * gwindow)
	/* FIXME accept flags (focus...) */
{
	Display * display;

	display = gtoolkit_get_display();
	XMapRaised(display, gwindow->window);
	glXMakeCurrent(display, gwindow->window, gwindow->context);
}
