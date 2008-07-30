#include <helpers.h>

/* Runs the user's pdf viewer on a file *
 * TODO: check if file exists, ignore this case
 * TODO: make pdf viewer customizable
*/
void openPDF(gchar* path) {
	if(path == NULL) {
		return;
	}
	pid_t pid = fork();
	if(pid == 0) {
		execlp(g_key_file_get_string(configFile,"chitransit","pdfviewer",NULL),g_key_file_get_string(configFile,"chitransit","pdfviewer",NULL),path,0);
	}
}

/* returns the path to a given data file (usually prepends /usr/share/) 
 * TODO: use platform-independant directory seperators in this and
 * 	next function
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
 * TODO: gconf? dconf? pleh
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
