#include <main.h>

void on_mainwindow_destroy(GtkWidget *widget){
	gtk_main_quit ();
}

void loadpage(GtkNotebook *notebook, GtkNotebookPage *page,guint page_num, gpointer user_data) {
	if(page_num == 1){
		buses_load();
	}
}

int main (int argc, char **argv) {
	gtk_init(&argc, &argv);
	xml = glade_xml_new(getDataFile("chitransit.glade"), NULL,NULL);
	
	/* setup curl */
	curl_global_init(CURL_GLOBAL_ALL); 
	easyhandle = curl_easy_init(); 
	
	if (!xml) {
		g_warning("something bad happened while creating the interface");
		return 1;
	}

	/* connect signal handlers
	glade_xml_signal_autoconnect(xml); */
	/* TODO: wonder why this doesn't work? */
	glade_xml_signal_connect(xml,"on_mainwindow_destroy",G_CALLBACK(on_mainwindow_destroy));
	glade_xml_signal_connect(xml,"on_btndownloadbus_clicked",G_CALLBACK(on_btndownloadbus_clicked));
	glade_xml_signal_connect(xml,"loadpage",G_CALLBACK(loadpage));
	glade_xml_signal_connect(xml,"on_ctaroutes_changed",G_CALLBACK(on_ctaroutes_changed));
	glade_xml_signal_connect(xml,"on_btnpacemap_clicked",G_CALLBACK(on_btnpacemap_clicked));
	glade_xml_signal_connect(xml,"on_btnpacesched_clicked",G_CALLBACK(on_btnpacesched_clicked));
	glade_xml_signal_connect(xml,"on_pdfviewer_changed",G_CALLBACK(on_pdfviewer_changed));
	glade_xml_signal_connect(xml,"on_datapath_changed",G_CALLBACK(on_datapath_changed));

	gtk_main();
	return 0;
}
