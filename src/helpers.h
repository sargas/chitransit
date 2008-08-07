#ifndef HELPERS_H
#define HELPERS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include <curl/curl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <main.h>

typedef struct {
	const gchar* url;
	const gchar* local;
} filehelper;

//worked better like this for some reason
filehelper tempstruct;
//needed for timing purposes
gboolean currentlydowning;

/* our config file access 
 * Made by loadConfig() */
GKeyFile *configFile;

void openPDF(gchar* path);
gchar* getDataFile(gchar* file);
gchar* getProgData(gchar* append);
void loadConfig();
void saveConfig();
gboolean downFile(const gchar* url, const gchar* local);
void* downFileHelper(void *ptr);
#endif
