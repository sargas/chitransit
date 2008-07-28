#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>
#include <glade/glade.h>

#include <curl/curl.h>

#include <buses.h>


/* declared up here so call back functions can use it */
GladeXML *xml;
CURL *easyhandle;

#endif