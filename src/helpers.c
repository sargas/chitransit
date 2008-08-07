#include <helpers.h>

/* Runs the user's pdf viewer on a file *
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
gchar* getDataFile(gchar* file) {
	return g_strconcat(DATADIR,"/chitransit/",file,NULL);
}

/* returns the path to our downloads
 * usually this will be in /tmp/chitransit/
 * appends anything given to it
*/
gchar* getProgData(gchar* append) {
	return g_strconcat(g_key_file_get_string(configFile,"chitransit","datapath",NULL),append,NULL);
}

/* load config file
 */
void loadConfig() {
	gint fid = -42;
	//we have a fixed path, $HOME/.chitransit/config
	//we gotta make sure this exists first though
	
	//aparently i need to create the key file, even though it starts empty :/
	configFile = g_key_file_new();
	
	if(g_mkdir_with_parents(g_strconcat(g_getenv("HOME"),"/.chitransit/",NULL),0755) == 0) {
		if( g_access(g_strconcat(g_getenv("HOME"),"/.chitransit/config",NULL),R_OK) == 0
				|| (fid = g_creat((g_strconcat(g_getenv("HOME"),"/.chitransit/config",NULL)),0644 )) > 0) {
			if(fid != -42) { //this means that we created (and opened) a file......we ready for the responsibility?
				close(fid);
				/* write some dummy content, else gkeyfile wouldn't load */
				g_file_set_contents(g_strconcat(g_getenv("HOME"),"/.chitransit/config",NULL),
						"[chitransit]\ndatapath=/tmp/chitransit/\npdfviewer=epdfview\n"
						,-1,NULL);
			}
			if(g_key_file_load_from_file(configFile,g_strconcat(getenv("HOME"),"/.chitransit/config",NULL),0,NULL) == FALSE) {
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
	g_file_set_contents(g_strconcat(g_getenv("HOME"),"/.chitransit/config",NULL),configstring,length,NULL);
}

/* downloads a file
 * assumes parent directories have already been made */
gboolean downFile(const gchar* url, const gchar* local) {
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

	pthread_join(tid,NULL);

	//waste time waiting....
	currentlydowning = TRUE;
	while (currentlydowning)
		gtk_main_iteration();

	gtk_widget_hide(GTK_WIDGET(win));
	return TRUE;
}

void* downFileHelper(void *ptr) {
	filehelper *temp2 = (filehelper*)ptr;
	filehelper temp = *temp2;
	const gchar* url = temp.url;
	FILE* localfile = g_fopen(temp.local,"w");
	curl_easy_setopt(easyhandle,CURLOPT_WRITEDATA,localfile);
	curl_easy_setopt(easyhandle,CURLOPT_URL,url);
	if(curl_easy_perform(easyhandle) != 0) {
		g_warning(g_strconcat("The following url could not be downloaded: ",url,NULL));
	}
	fclose(localfile);
	currentlydowning = FALSE;
	pthread_exit((void*) 0);
}
