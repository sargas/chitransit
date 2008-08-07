/********************************************************************
* This file is part of ChiTransit.
* Copyright 2008 Joseph Jon Booker

* ChiTransit is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* ChiTransit is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with ChiTransit.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#ifndef MAPS_H
#define MAPS_H

#include <gtk/gtk.h>

#include <main.h>

/* used to describe one of our big maps */
typedef struct {
	GtkButton* button; /* the button to see it */
	GtkButton* downloadbtn; /* the download button */
	const gchar* url; /* the url (on cta/rta/pace servers) */
	const gchar* localname; /* our localname for the pdf */
	gchar* size; /* size of the pdf, w/ units */
} chimap;

chimap *chimaps; /* array of chimap's, loaded in maps_load */
guint num_of_maps;

void maps_load();
void downmaps(GtkButton *button);
void mapview(GtkButton *button);

#endif
