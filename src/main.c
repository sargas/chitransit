#include <main.h>

void on_mainwindow_destroy(GtkWidget *widget){
	gtk_main_quit ();
}


int main (int argc, char **argv) {
	gtk_init(&argc, &argv);
	xml = glade_xml_new("chitransit.glade", NULL,NULL);
	
	/* setup curl */
	curl_global_init(CURL_GLOBAL_ALL); 
	easyhandle = curl_easy_init(); 
	
	if (!xml) {
		g_warning("something bad happened while creating the interface");
		return 1;
	}

	/* connect signal handlers 
	glade_xml_signal_autoconnect(xml);*/
	/* TODO: wonder why this doesn't work? */
	glade_xml_signal_connect(xml,"on_mainwindow_destroy",G_CALLBACK(on_mainwindow_destroy));
	glade_xml_signal_connect(xml,"on_btndownloadbus_clicked",G_CALLBACK(on_btndownloadbus_clicked));
	
	gtk_main();
	return 0;
}
