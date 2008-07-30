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
		execl("/usr/bin/epdfview","epdfview",path,0);
	}
}

/* returns the path to a given data file (usually prepends /usr/share/) */
gchar* getDataFile(gchar* file) {
	return g_strconcat(DATADIR,"/chitransit/",file,NULL);
}
