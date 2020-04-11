/* $Id$ */



#ifndef GTOOLKIT_COMMON_H
# define GTOOLKIT_COMMON_H

# include <X11/Xlib.h>
# include <GL/glx.h>
# include <GToolkit.h>


/* types */
typedef struct _GToolkit
{
	/* main loop */
	int loop;

	/* not portable */
	Display * display;
	int screen;
	XVisualInfo * visual;
} GToolkit;

/* variables */
extern GToolkit gt;

#endif
