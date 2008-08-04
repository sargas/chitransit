#ifndef TRAINS_H
#define TRAINS_H


#include <gtk/gtk.h>
#include <glade/glade.h>

#include <main.h>
#include <helpers.h>

typedef struct {
	gchar* name;
	gchar* displayname;
	gint pos;
} station;

typedef struct {
	gchar* line;
	GtkComboBox* box;
	station* stations;
	gint num;
} trainline;

trainline* lines;
gint num_of_lines;

void load_trains();
void on_btnupdate_clicked(GtkButton *button);
void openStation(GtkComboBox *box);

#endif
