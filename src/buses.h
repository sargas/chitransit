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