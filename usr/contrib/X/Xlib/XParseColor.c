#include <X/mit-copyright.h>

/* $Header: XParseColor.c,v 10.4 86/02/01 15:37:40 tony Rel $ */
/* Copyright    Massachusetts Institute of Technology    1985	*/

#include "XlibInternal.h"

Status XParseColor (spec, def)
	register char *spec;
	Color *def;
{
	register Display *dpy;
	register XReq *req;
	XRep rep;
	register int n, i;
	int r, g, b;
	char c;

	n = strlen (spec);
	if (*spec != '#') {
	    GetReq (X_LookupColor, 0);
	    req->param.s[0] = n;
	    Data (dpy, spec, n);
	    if (!_XReply (dpy, &rep))
	    	return (0);
	    def->red = rep.param.u[0];
	    def->green = rep.param.u[1];
	    def->blue = rep.param.u[2];
	    return (1);
	}
	spec++;
	n--;
	if (n != 3 && n != 6 && n != 9 && n != 12)
	    return (0);
	n /= 3;
	r = g = b = 0;
	do {
	    r = g;
	    g = b;
	    b = 0;
	    for (i = n; --i >= 0; ) {
		c = *spec++;
		b <<= 4;
		if (c >= '0' && c <= '9')
		    b |= c - '0';
		else if (c >= 'A' && c <= 'F')
		    b |= c - ('A' - 10);
		else if (c >= 'a' && c <= 'f')
		    b |= c - ('a' - 10);
		else return (0);
	    }
	} while (*spec);
	n <<= 2;
	n = 16 - n;
	def->red = r << n;
	def->green = g << n;
	def->blue = b << n;
	return (1);
}
