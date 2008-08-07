#include <maps.h>

void maps_load() {
	chimap temp[] = {
		{
			GTK_BUTTON(glade_xml_get_widget(xml, "btnrails")),
			GTK_BUTTON(glade_xml_get_widget(xml, "btndownrails")),
			"http://transitchicago.com/maps/maps/fwebmaptrain.pdf",
			"rails.pdf",
			"76K"
		}, {
			GTK_BUTTON(glade_xml_get_widget(xml, "btnpeds")),
			GTK_BUTTON(glade_xml_get_widget(xml, "btndownpeds")),
			"http://www.spiegl.org/pedway/234-235.pdf",
			"peds.pdf",
			"101K"
		}, {
			GTK_BUTTON(glade_xml_get_widget(xml, "btnsys")),
			GTK_BUTTON(glade_xml_get_widget(xml, "btndownsys")),
			"http://rtachicago.com/CMS400Min/uploadedFiles/RTA_May%202008_System_Map.pdf",
			"sys.pdf",
			"3.4M"
		}
	};
	
	num_of_maps = 3;
	chimaps = g_memdup(temp,sizeof(temp));

	if(g_mkdir_with_parents(getProgData("maps"),0755) != 0) {
		g_warning("Couldn't create maps folder");
	}

	for(gint i=0;i<num_of_maps;i++) {
		if(g_access(g_strconcat(getProgData("maps/"),chimaps[i].localname,NULL),R_OK) != 0) {
			gtk_widget_set_sensitive(GTK_WIDGET(chimaps[i].button),FALSE);
			gtk_button_set_label(chimaps[i].downloadbtn,g_strconcat("Download (",chimaps[i].size,")",NULL));
		} else {
			gtk_widget_set_sensitive(GTK_WIDGET(chimaps[i].button),TRUE);
			gtk_button_set_label(chimaps[i].downloadbtn,g_strconcat("Update (",chimaps[i].size,")",NULL));
		}
	}
}

void downmaps(GtkButton *button) {
	for(gint i=0;i<num_of_maps;++i) {
		/* looks wrong since we are comparing pointers, but we want pointers to teh same object */
		if(button == chimaps[i].downloadbtn) {
			gchar* dest = g_strconcat(getProgData("maps/"),chimaps[i].localname,NULL);
			downFile(chimaps[i].url,dest);
			break;
		}
	}
	maps_load(); //reload em :)
}

void mapview(GtkButton *button) {
	for(gint i=0;i<num_of_maps;++i) {
		if(button == chimaps[i].button) {
			openPDF(g_strconcat(getProgData("maps/"),chimaps[i].localname,NULL));
			break;
		}
	}
}
