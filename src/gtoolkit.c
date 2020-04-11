/* $Id$ */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GToolkit/GWindow.h"
#include "common.h"


/* GToolkit */
/* private */
/* types */
typedef struct _GToolkit 
{
	int init;

	/* main loop */
	int loop;

	GWindow ** windows;
	size_t windows_cnt;

	/* not portable */
	Display * display;
	int screen;
	XVisualInfo * visual;
	Colormap colormap;
} GToolkit;


/* variables */
static GToolkit _gt;


/* prototypes */
/* accessors */
static GWindow * _gtoolkit_get_gwindow(Window window);

/* useful */
static int _gtoolkit_error(char const * message, int ret);


/* public */
/* functions */
/* accessors */
Colormap gtoolkit_get_colormap(void)
{
	return _gt.colormap;
}


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
/* gtoolkit_register_window */
void gtoolkit_deregister_window(GWindow * gwindow)
{
	size_t i;

	/* FIXME free memory if possible */
	for(i = 0; i < _gt.windows_cnt; i++)
		if(_gt.windows[i] == gwindow)
		{
			_gt.windows[i] = NULL;
			return;
		}
}


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
	_gt.colormap = XCreateColormap(_gt.display,
			RootWindow(_gt.display, _gt.screen),
			_gt.visual->visual, AllocNone);
	_gt.loop = 0;
	_gt.init = 1;
	return 0;
}


/* gtoolkit_main */
static void _main_configure_notify(XConfigureEvent * event);

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
			switch(event.type)
			{
				case ConfigureNotify:
					_main_configure_notify(&event.xconfigure);
					break;
#if 0
				case Expose:
				case KeyPress:
				case KeyRelease:
				case ClientMessage:
#endif
				default:
					break;
			}
		}
	}
	_gt.loop = 0;
	return 0;
}

static void _main_configure_notify(XConfigureEvent * event)
{
	GWindow * gwindow;

	if((gwindow = _gtoolkit_get_gwindow(event->window)) == NULL)
		return;
	gwindow_event_configure(gwindow, event);
}


/* gtoolkit_register_window */
void gtoolkit_register_window(GWindow * gwindow)
{
	GWindow ** p;

	/* FIXME look for an empty spot first */
	if((p = realloc(_gt.windows, sizeof(*p) * _gt.windows_cnt + 1)) == NULL)
		/* XXX ignore errors */
		return;
	_gt.windows = p;
	_gt.windows[_gt.windows_cnt++] = gwindow;
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
/* accessors */
/* gtoolkit_get_gwindow */
static GWindow * _gtoolkit_get_gwindow(Window window)
{
	size_t i;

	for(i = 0; i < _gt.windows_cnt; i++)
		if(_gt.windows[i] != NULL
				&& gwindow_get_window(_gt.windows[i]) == window)
			return _gt.windows[i];
	/* XXX report error */
	return NULL;
}


/* useful */
/* gtoolkit_error */
static int _gtoolkit_error(char const * message, int ret)
{
	fprintf(stderr, "%s%s\n", "GToolkit: ", message);
	return ret;
}
