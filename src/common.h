/* $Id$ */



#ifndef GTOOLKIT_COMMON_H
# define GTOOLKIT_COMMON_H

# include <X11/Xlib.h>
# include <GL/glx.h>


/* GToolkit */
/* accessors */
Display * gtoolkit_get_display(void);
XVisualInfo * gtoolkit_get_visual(void);

#endif
