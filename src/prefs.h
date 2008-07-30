#ifndef PREFS_H
#define PREFS_H

#include <gtk/gtk.h>

#include <glade/glade.h>
#include <main.h>

void prefs_load();
void fill_combo_box(gchar *widgetname, gchar *settingsname);
void on_btnApplyPrefs_clicked(GtkButton *button);
void update_settings(gchar* widgetname, gchar *settingsname);
#endif
