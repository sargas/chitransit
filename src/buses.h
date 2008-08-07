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

#ifndef BUSES_H
#define BUSES_H

#include <glib.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include <stdlib.h>
#include <stdio.h>

#include <main.h>
#include <helpers.h>

void buses_load();
void on_btndownloadbus_clicked(GtkWidget *widget);
void on_ctaroutes_changed(GtkWidget *widget);
void on_btnpacemap_clicked(GtkWidget *widget);
void on_btnpacesched_clicked(GtkWidget *widget);

#endif

