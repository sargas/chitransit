#include <gtk/gtk.h>

int main (int argc, char **argv) {
	GladeXML *xml;
	GtkWidget *widget;

	gtk_init(&argc, &argv);
	xml = glade_xml_new("chitransit.glade", NULL, NULL);

	/* connect signal handlers */
	glade_xml_signal_autoconnect(xml);

	gtk_main();
	return 0;
}