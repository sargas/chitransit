#ifndef HELPERS_H
#define HELPERS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>

/* our config file access 
 * Made by loadConfig() */
GKeyFile *configFile;

void openPDF(gchar* path);
gchar* getDataFile(gchar* file);
gchar* getProgData(gchar* append);
void loadConfig();
void saveConfig();

#endif
