/* $Id$ */



#ifndef GTOOLKIT_GWINDOW_H
# define GTOOLKIT_GWINDOW_H


/* GWindow */
/* types */
typedef struct _GWindow GWindow;


/* functions */
GWindow * gwindow_new(void);


/* accessors */
char const * gwindow_get_title(GWindow * gwindow);
void gwindow_set_title(GWindow * gwindow, char const * title);

/* useful */
void gwindow_show(GWindow * gwindow);

#endif /* !GTOOLKIT_GWINDOW_H */
