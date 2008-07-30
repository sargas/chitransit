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
} chimap;

chimap *chimaps; /* array of chimap's, loaded in maps_load */
guint num_of_maps;

void maps_load();
void downmaps(GtkButton *button);
void mapview(GtkButton *button);

#endif
