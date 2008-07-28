#include <buses.h>
#include <main.h>

//download either pace or cta bus info
void on_btndownloadbus_clicked(GtkWidget *widget) {
	GtkSpinButton *busroute = GTK_SPIN_BUTTON(glade_xml_get_widget(xml, "busroute"));
	gint route = gtk_spin_button_get_value_as_int(busroute);
	/* buffer stores urls, dest stores where we put em */
	char buffer[512];
	char dest[512];
	char buffer2[512];
	char dest2[512];
	FILE *map;
	FILE *sched; /* not used for cta */

	if(route < 205) {
		sprintf(buffer,"http://transitchicago.com/maps/Bus/Bus/%d.pdf",route);
		sprintf(dest,"/home/joe/.chitransit/ctabus/%d.pdf",route);
		map = fopen(dest,"w");
		curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, map);
		curl_easy_setopt(easyhandle, CURLOPT_URL, buffer);
		curl_easy_setopt(easyhandle, CURLOPT_ERRORBUFFER, buffer2);
		/* TODO: Handle error conditions better */
		if(curl_easy_perform(easyhandle) != 0) {
			g_warning("Failed to get CTA Bus route!");
			g_warning(buffer2);
			fclose(map);
			return;
		}
		fclose(map);
	} else {
		sprintf(buffer,"http://pacebus.com/pdf/schedules/%dsched.pdf",route);
		sprintf(dest,"/home/joe/.chitransit/pacebus/%dsched.pdf",route);
		sprintf(buffer2,"http://pacebus.com/pdf/maps/%dmap.pdf",route);
		sprintf(dest2,"/home/joe/.chitransit/pacebus/%dmap.pdf",route);
		map = fopen(dest,"w");
		curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, map);
		curl_easy_setopt(easyhandle, CURLOPT_URL, buffer);
		if(curl_easy_perform(easyhandle) != 0) {
			g_warning("Failed to get map of Pace Route!");
			fclose(map);
			return;
		}
		fclose(map);sched = fopen(dest2,"w");
		curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, sched);
		curl_easy_setopt(easyhandle, CURLOPT_URL, buffer2);
		if(curl_easy_perform(easyhandle) != 0) {
			/* TODO delete the map if the schedule failed, so we dont have half a route */
			g_warning("Failed to get schedule of Pace route :/");
		}
		fclose(sched);
	}
	buses_load(); /* reload em */
}
void on_ctaroutes_changed(GtkWidget *widget) {
	return;
}
void on_btnpacemap_clicked(GtkWidget *widget) {
	return;
}
void on_btnpacesced_clicked(GtkWidget *widget) {
	return;
}


void buses_load() {
	GDir* pacebuses = g_dir_open("/home/joe/.chitransit/pacebus/",0,NULL);
	GDir* ctabuses   = g_dir_open("/home/joe/.chitransit/ctabus",0,NULL);
	const gchar *name;
	GRegex *regex;
	GMatchInfo *match_info;
	GtkComboBox *paceroutes = GTK_COMBO_BOX(glade_xml_get_widget(xml, "paceroutes"));
	GtkComboBox *ctaroutes = GTK_COMBO_BOX(glade_xml_get_widget(xml, "ctaroutes"));
	
	/* clear these routes first, bad experiences if we don't 
	   hopefully its ok to reuse model like this, i doubt we gotta clear it
	*/
	GtkListStore* model = GTK_LIST_STORE(gtk_combo_box_get_model(paceroutes));
	gtk_list_store_clear(model);
	model = GTK_LIST_STORE(gtk_combo_box_get_model(ctaroutes));
	gtk_list_store_clear(model);

	/* handle pace buses first */
	name = g_dir_read_name(pacebuses);
	regex = g_regex_new("(\\d+)map\\.pdf$",0,0,NULL);
	while (name != NULL) {
		//check we got the right kind....we skip schedules, hope that if theres a map theres both
		if(g_regex_match(regex,name,0,&match_info)) {
			gchar *busroute = g_match_info_fetch (match_info, 1);
			gtk_combo_box_append_text(paceroutes,busroute);
			g_free(busroute);
		}
		g_match_info_free(match_info);
		name = g_dir_read_name(pacebuses);
	}
	g_regex_unref(regex);
	g_dir_close(pacebuses);
	
	/* now for CTA stuff */
	name = g_dir_read_name(ctabuses);
	regex = g_regex_new("(\\d+)\\.pdf$",0,0,NULL);
	while(name != NULL) {
		/* this would only not match if people are putting crap in the directory */
		if(g_regex_match(regex,name,0,&match_info)) {
			gchar *busroute = g_match_info_fetch (match_info, 1);
			gtk_combo_box_append_text(ctaroutes,busroute);
			g_free(busroute);
		}
		g_match_info_free(match_info);
		name = g_dir_read_name(ctabuses);
	}
	g_regex_unref(regex);
	g_dir_close(ctabuses);
}
