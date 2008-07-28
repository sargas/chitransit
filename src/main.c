#include <stdlib.h>
#include <stdio.h>

#include <gtk/gtk.h>
#include <glade/glade.h>

void on_mainwindow_destroy(GtkWidget *widget){
	gtk_main_quit ();
}
int main (int argc, char **argv) {
	GladeXML *xml;

	gtk_init(&argc, &argv);
	xml = glade_xml_new("chitransit.glade", NULL,NULL);
	
	if (!xml) {
		g_warning("something bad happened while creating the interface");
		return 1;
	}

	/* connect signal handlers 
	glade_xml_signal_autoconnect(xml);*/
	/* TODO: wonder why this doesn't work? */
	glade_xml_signal_connect(xml,"on_mainwindow_destroy",G_CALLBACK(on_mainwindow_destroy));
	
	gtk_main();
	return 0;
}
