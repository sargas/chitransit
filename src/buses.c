/********************************************************************
* This file is part of ChiTransit.
* Copyright 2008 Joseph Jon Booker

* ChiTransit is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.

* ChiTransit is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with ChiTransit.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
#include <buses.h>

//download either pace or cta bus info
void on_btndownloadbus_clicked(GtkWidget *widget) {
	GtkSpinButton *busroute = GTK_SPIN_BUTTON(glade_xml_get_widget(xml, "busroute"));
	gint route = gtk_spin_button_get_value_as_int(busroute);
	/* buffer stores urls, dest stores where we put em */
	gchar buffer[512];
	gchar dest[512];
	gchar buffer2[512];
	gchar dest2[512];

	if(route < 205) {
		g_snprintf(buffer,512,"http://transitchicago.com/maps/Bus/Bus/%d.pdf",route);
		g_snprintf(dest,512,"%s/ctabus/%d.pdf",getProgData(NULL),route);
		downOneFile(buffer,dest);
	} else {
		g_snprintf(buffer,512,"http://pacebus.com/pdf/schedules/%dsched.pdf",route);
		g_snprintf(dest,512,"%s/pacebus/%dsched.pdf",getProgData(NULL),route);
		g_snprintf(buffer2,512,"http://pacebus.com/pdf/maps/%dmap.pdf",route);
		g_snprintf(dest2,512,"%s/pacebus/%dmap.pdf",getProgData(NULL),route);
		downOneFile(buffer,dest);
		downOneFile(buffer2,dest2);
	}
	buses_load(); /* reload em */
}
void on_ctaroutes_changed(GtkWidget *widget) {
	/* so, ya wanta no your way around the chitown buses, eh? */
	GtkComboBox* routeWidget = GTK_COMBO_BOX(widget);
	gchar* route = gtk_combo_box_get_active_text(routeWidget);
	gchar url[512];
	if(route == NULL) {
		return; //this happens when page loads
	} //note: since getProgData(NULL) will have an ending slash,
	  //      we'll have a double slash. better then alternative
	g_snprintf(url,512,"%s/ctabus/%s.pdf",getProgData(NULL),route);
	openPDF(url);
}
void on_btnpacemap_clicked(GtkWidget *widget) {
	GtkComboBox *routeWidget = GTK_COMBO_BOX(glade_xml_get_widget(xml, "paceroutes"));
	gchar* route = gtk_combo_box_get_active_text(routeWidget);
	gchar url[512];
	g_snprintf(url,512,"%s/pacebus/%smap.pdf",getProgData(NULL),route);
	openPDF(url);
}
void on_btnpacesched_clicked(GtkWidget *widget) {
	GtkComboBox *routeWidget = GTK_COMBO_BOX(glade_xml_get_widget(xml, "paceroutes"));
	gchar* route = gtk_combo_box_get_active_text(routeWidget);
	gchar url[512];
	g_snprintf(url,512,"%s/pacebus/%ssched.pdf",getProgData(NULL),route);
	openPDF(url);
}


void buses_load() {
	if(g_mkdir_with_parents(getProgData("pacebus"),0755) != 0
		|| g_mkdir_with_parents(getProgData("ctabus"),0755) != 0) {
		g_warning("Couldn't create buses folders");
	}
	GDir* pacebuses = g_dir_open(getProgData("pacebus"),0,NULL);
	GDir* ctabuses   = g_dir_open(getProgData("ctabus"),0,NULL);
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
