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

#ifndef HELPERS_H
#define HELPERS_H

#include <glib.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include <curl/curl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include <main.h>

typedef struct {
	GSList* url;
	GSList* local;
} filehelper;

//worked better like this for some reason
filehelper tempstruct;
//needed for timing purposes
gboolean currentlydowning;
//TODO: refactor code to not need this
gboolean downerrorhappened;

/* our config file access 
 * Made by loadConfig() */
GKeyFile *configFile;

//cancel the dl
void on_btnCancelDl_clicked(GtkButton *button);
gboolean flagGETTHEFUCKOUT;

//for tracking multiple dls
gint numFiles;
gint numFilesDone;

void openPDF(gchar* path);
const gchar* getDataFile(const gchar* file);
const gchar* getProgData(const gchar* append);
void loadConfig();
void saveConfig();
//convience function
gboolean downOneFile(gchar* url, gchar* local);
//Both GSLists are of gchar*
gboolean downFile(GSList* url, GSList* local);
int progress_callback(void*,double,double,double,double);
void* downFileHelper(void *ptr);
#endif
