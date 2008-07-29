#include <helpers.h>

void openPDF(gchar* path) {
	if(path == NULL) {
		return;
	}
	pid_t pid = fork();
	if(pid == 0) {
		execl("/usr/bin/epdfview","epdfview",path,0);
	}
}