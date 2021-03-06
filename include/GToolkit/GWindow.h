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



#ifndef GTOOLKIT_GWINDOW_H
# define GTOOLKIT_GWINDOW_H

# include <stdbool.h>


/* GWindow */
/* types */
typedef struct _GWindow GWindow;


/* functions */
GWindow * gwindow_new(void);
void gwindow_delete(GWindow * gwindow);


/* accessors */
bool gwindow_get_decorated(GWindow * gwindow);
bool gwindow_get_modal(GWindow * gwindow);
bool gwindow_get_resizable(GWindow * gwindow);
void gwindow_get_size(GWindow * gwindow, int * width, int * height);
char const * gwindow_get_title(GWindow * gwindow);
void gwindow_set_resizable(GWindow * gwindow, bool resizable);
void gwindow_set_title(GWindow * gwindow, char const * title);

/* useful */
void gwindow_move(GWindow * gwindow, int x, int y);
void gwindow_present(GWindow * gwindow);
void gwindow_resize(GWindow * gwindow, int width, int height);

#endif /* !GTOOLKIT_GWINDOW_H */
