/* $Id$ */



#include <stdio.h>
#include <string.h>
#include "common.h"


/* GToolkit */
/* private */
/* types */
typedef struct _GToolkit 
{
	int init;

	/* main loop */
	int loop;

	/* not portable */
	Display * display;
	int screen;
	XVisualInfo * visual;
} GToolkit;


/* variables */
static GToolkit _gt;


/* prototypes */
static int _gtoolkit_error(char const * message, int ret);


/* public */
/* functions */
/* accessors */
/* gtoolkit_get_display */
Display * gtoolkit_get_display(void)
{
	return _gt.display;
}


/* gtoolkit_get_visual */
XVisualInfo * gtoolkit_get_visual(void)
{
	return _gt.visual;
}


/* useful */
/* gtoolkit_init */
int gtoolkit_init(void)
{
	int attr[] =
	{
		GLX_RGBA, GLX_DOUBLEBUFFER,
		GLX_RED_SIZE, 4,
		GLX_GREEN_SIZE, 4,
		GLX_BLUE_SIZE, 4,
		GLX_DEPTH_SIZE, 16,
		None
	};

	if(_gt.init != 0)
		return 0;
	if((_gt.display = XOpenDisplay(NULL)) == NULL)
		return _gtoolkit_error("Could not open display", 1);
	_gt.screen = DefaultScreen(_gt.display);
	if((_gt.visual = glXChooseVisual(_gt.display, _gt.screen, attr))
			== NULL)
		return _gtoolkit_error("Could not choose visual", 1);
	_gt.loop = 0;
	_gt.init = 1;
	return 0;
}


/* gtoolkit_main */
int gtoolkit_main(void)
{
	XEvent event;

	if(_gt.loop != 0)
		return 1;
	for(_gt.loop = 1; _gt.loop == 1;)
	{
		while(XPending(_gt.display) > 0)
		{
			XNextEvent(_gt.display, &event);
#ifdef DEBUG
			fprintf(stderr, "DEBUG: Event %d\n", event.type);
#endif
		}
	}
	_gt.loop = 0;
	return 0;
}


/* gtoolkit_quit */
int gtoolkit_quit(void)
{
	if(_gt.init == 0)
		return 0;
	XCloseDisplay(_gt.display);
	memset(&_gt, 0, sizeof(_gt));
	_gt.init = 0;
	return 0;
}


/* private */
/* useful */
/* gtoolkit_error */
static int _gtoolkit_error(char const * message, int ret)
{
	fprintf(stderr, "%s%s\n", "GToolkit: ", message);
	return ret;
}
