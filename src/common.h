/* $Id$ */



#ifndef GTOOLKIT_COMMON_H
# define GTOOLKIT_COMMON_H

# include <X11/Xlib.h>
# include <GL/glu.h>
# include <GL/glx.h>


/* GToolkit */
/* accessors */
Display * gtoolkit_get_display(void);
Colormap gtoolkit_get_colormap(void);
XVisualInfo * gtoolkit_get_visual(void);

/* useful */
void gtoolkit_register_window(GWindow * gwindow);
void gtoolkit_deregister_window(GWindow * gwindow);


/* GWindow */
/* accessors */
Window gwindow_get_window(GWindow * gwindow);

/* useful */
void gwindow_event_configure(GWindow * gwindow, XConfigureEvent * event);
void gwindow_event_map(GWindow * gwindow, XMapEvent * event);

#endif
