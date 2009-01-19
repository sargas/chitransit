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

#include <helpers.h>

/* Runs the user's pdf viewer on a file *
 * TODO: use libpoppler to have a quick internal pdf viewer
*/
void openPDF(gchar* path) {
	if(path == NULL) {
		return;
	} else if(g_access(path,R_OK) != 0) {
		g_warning("Tried to open a pdf we can't read");
		return;
	}
	pid_t pid = fork();
	if(pid == 0) {
		execlp(g_key_file_get_string(configFile,"chitransit","pdfviewer",NULL),g_key_file_get_string(configFile,"chitransit","pdfviewer",NULL),path,0);
		//if we got here, damn
		g_warning("Problem loading PDF");
		_exit(32);
	}
}

/* returns the path to a given data file (usually prepends /usr/share/) 
*/
const char* getDataFile(const char* file) {
	return g_strconcat(DATADIR,"/chitransit/",file,NULL);
}

/* returns the path to our downloads
 * usually this will be in /tmp/chitransit/
 * appends anything given to it
*/
const gchar* getProgData(const gchar* append) {
	return g_strconcat(g_key_file_get_string(configFile,"chitransit","datapath",NULL),append,NULL);
}

/* load config file
 * why does this function look so ugly!?!?!?!?
 */
void loadConfig() {
	gint fid = -42;
	//we have a fixed path, $HOME/.chitransit/config
	//we gotta make sure this exists first though
	
	//aparently i need to create the key file, even though it starts empty :/
	configFile = g_key_file_new();
	
	if(g_mkdir_with_parents(g_strconcat(g_get_home_dir(),"/.chitransit/",NULL),0755) == 0) {
		if( g_access(g_strconcat(g_get_home_dir(),"/.chitransit/config",NULL),R_OK) == 0
				|| (fid = g_creat((g_strconcat(g_get_home_dir(),"/.chitransit/config",NULL)),0644 )) > 0) {
			if(fid != -42) { //this means that we created (and opened) a file......we ready for the responsibility?
				close(fid);
				/* write some dummy content, else gkeyfile wouldn't load */
				//note, this is where the default settings are set
				g_file_set_contents(g_strconcat(g_get_home_dir(),"/.chitransit/config",NULL),
						"[chitransit]\ndatapath=/tmp/chitransit/\npdfviewer=epdfview\n"
						,-1,NULL);
			}
			if(g_key_file_load_from_file(configFile,g_strconcat(g_get_home_dir(),"/.chitransit/config",NULL),0,NULL) == FALSE) {
				g_error("~/.chitransit/config aint a valid key-value pairs file aparently?");
				exit(-1);
			}
		} else {
			g_error("Couldn't open or create ~/.chitransit/config");
			exit(-1);
		}
	} else {
		g_error("Couldn't open ~/.chitransit");
		exit(-1);
	}
}

void saveConfig() {
	//simple, we just convert to string, then put the string in our file
	gchar* configstring;
	gsize length;

	configstring = g_key_file_to_data(configFile,&length,NULL);
	g_file_set_contents(g_strconcat(g_get_home_dir(),"/.chitransit/config",NULL),configstring,length,NULL);
}

gboolean downOneFile(gchar* url, gchar* local) {
	GSList* lurl = NULL;
	lurl = g_slist_append(lurl,url);
	GSList* llocal = g_slist_append(NULL,local);
	gboolean status = downFile(lurl,llocal);
	g_slist_free(lurl);g_slist_free(llocal);
	return status;
}

/* downloads a file
 * assumes parent directories have already been made
 * versa */
// TODO: make this not flash auxilary window so much
// TODO: make it assert same size lists
gboolean downFile(GSList* url, GSList* local ) {
	pthread_t tid;
	pthread_attr_t attr;
	
	//load nice gui
	GtkWindow *win = GTK_WINDOW(glade_xml_get_widget(xml,"downwin"));
	gtk_window_present(win);
	
	//pthread stuff
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	tempstruct.url = url;tempstruct.local = local;
	pthread_create(&tid,&attr,downFileHelper,&tempstruct);
	pthread_attr_destroy(&attr);

	//waste time waiting....
	flagGETTHEFUCKOUT  = FALSE;
	currentlydowning = TRUE;
	downerrorhappened = FALSE;
	pthread_join(tid,NULL);

	while (currentlydowning || gtk_events_pending())
		gtk_main_iteration();

	gtk_widget_hide(GTK_WIDGET(win));
	if(flagGETTHEFUCKOUT //aka we canceled
		|| downerrorhappened) //or couldn't get everything
		return FALSE;

	return TRUE;
}

void* downFileHelper(void *ptr) {
	filehelper *temp2 = (filehelper*)ptr;
	filehelper temp = *temp2;
	GSList* lurl = temp.url;
	GSList* llocal = temp.local;
	gchar* url;
	gchar* local;
	FILE* localfile = NULL;
	GtkProgressBar *bar = GTK_PROGRESS_BAR(glade_xml_get_widget(xml,"progbar"));
	//i no, its bad
	numFiles = g_slist_position(lurl,g_slist_last(lurl))+1;
	numFilesDone = 0;
	for(;lurl != NULL;lurl = g_slist_next(lurl)) {
		//TODO: don't use internal structure of GSList's
		//maybe use g_slist_foreach
		url = (gchar*)lurl->data;
		local = (gchar*)llocal->data;
		llocal = g_slist_next(llocal); //want to inc after
		localfile = g_fopen(local,"w");

		curl_easy_setopt(easyhandle,CURLOPT_WRITEDATA,localfile);
		curl_easy_setopt(easyhandle,CURLOPT_URL,url);
		curl_easy_setopt(easyhandle, CURLOPT_NOPROGRESS, 0);
		curl_easy_setopt(easyhandle,CURLOPT_PROGRESSFUNCTION,progress_callback);
		curl_easy_setopt(easyhandle,CURLOPT_PROGRESSDATA, bar);
		//to keep like this or not? hmm...
		curl_easy_setopt(easyhandle,CURLOPT_VERBOSE,1);
		if(curl_easy_perform(easyhandle) != 0) {
			g_warning(g_strconcat("The following url could not be downloaded: ",url,NULL));
			downerrorhappened  = TRUE;
			goto ENDING_down_helper;
		}
		if(flagGETTHEFUCKOUT) goto ENDING_down_helper;
		numFilesDone++;
	}
ENDING_down_helper:
	fclose(localfile);
	currentlydowning = FALSE;
	pthread_exit((void*) 0);
}

int progress_callback(void *vbar,double t,double d,double a,double b) {
	GtkProgressBar* bar = (GtkProgressBar*)vbar; //prevents warnings
	//progress on current file, times number of file+1 / total number of files
	if(t != 0) gtk_progress_bar_set_fraction(bar,d/t*(numFilesDone+1)/numFiles);
	if(flagGETTHEFUCKOUT) return 1; //listen to the flag
	return 0;
}

void on_btnCancelDl_clicked(GtkButton *button) {
	flagGETTHEFUCKOUT = TRUE;
}
