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
