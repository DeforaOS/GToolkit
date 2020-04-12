/* $Id$ */
/* Copyright (c) 2020 Pierre Pronchery <khorben@defora.org> */
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



#include <stdarg.h>
#include <stdlib.h>
#include "common.h"


/* GWidget */
/* private */
/* types */
typedef void (*GWidgetHandlerSelf)(void * self);

struct _GWidget
{
	GWidget * gwidget;

	/* GWidget */
	void * self;

	/* handlers */
	GWidgetHandlerSelf handler_hide;
	GWidgetHandlerSelf handler_show;
};


/* public */
/* functions */
/* gwidget_new */
GWidget * gwidget_new(void)
{
	GWidget * gwidget;

	if((gwidget = malloc(sizeof(*gwidget))) == NULL)
		return NULL;
	gwidget->gwidget = gwidget;
	gwidget->self = NULL;
	gwidget->handler_hide = NULL;
	gwidget->handler_show = NULL;
	return gwidget;
}


/* gwidget_delete */
void gwidget_delete(GWidget * gwidget)
{
	free(gwidget);
}


/* accessors */
/* gwidget_set_handler */
void gwidget_set_handler(GWidget * gwidget, GWidgetHandler handler, ...)
{
	va_list ap;

	va_start(ap, handler);
	switch(handler)
	{
		case GWIDGET_HANDLER_HIDE:
			gwidget->handler_hide = va_arg(ap, GWidgetHandlerSelf);
			break;
		case GWIDGET_HANDLER_SHOW:
			gwidget->handler_show = va_arg(ap, GWidgetHandlerSelf);
			break;
	}
	va_end(ap);
}


/* gwidget_set_self */
void gwidget_set_self(GWidget * gwidget, void * self)
{
	gwidget->self = self;
}


/* useful */
/* gwidget_hide */
void gwidget_hide(GWidget * gwidget)
{
	if(gwidget->gwidget != gwidget)
		gwidget = gwidget->gwidget;
	if(gwidget->handler_hide != NULL)
		gwidget->handler_hide(gwidget->self);
}


/* gwidget_show */
void gwidget_show(GWidget * gwidget)
{
	if(gwidget->gwidget != gwidget)
		gwidget = gwidget->gwidget;
	if(gwidget->handler_show != NULL)
		gwidget->handler_show(gwidget->self);
}
