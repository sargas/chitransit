#include <buses.h>
#include <main.h>

void on_btndownloadbus_clicked(GtkWidget *widget) {
	GtkSpinButton *busroute = GTK_SPIN_BUTTON(glade_xml_get_widget(xml, "busroute"));
	gint route = gtk_spin_button_get_value_as_int(busroute);
	char buffer[512];
	char dest[512];
	char buffer2[512];
	char dest2[512];
	FILE *map;
	FILE *sched;
	if(route < 205) {
		sprintf(buffer,"http://transitchicago.com/maps/Bus/Bus/%d.pdf",route);
		sprintf(dest,"/home/joe/.chitransit/ctabus/%d.pdf",route);
		map = fopen(dest,"w");
		curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, map);
		curl_easy_setopt(easyhandle, CURLOPT_URL, buffer);
		curl_easy_setopt(easyhandle, CURLOPT_ERRORBUFFER, buffer2);
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
			g_warning("Failed to get schedule of Pace route :/");
		}
		fclose(sched);
	}
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
