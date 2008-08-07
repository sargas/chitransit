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

#include <prefs.h>

void prefs_load() {
	fill_combo_box("datapath","datapath");
	fill_combo_box("pdfviewer","pdfviewer");
}

/* nice little helper function, fills a combo w/o removing old values, sets one in settings to current value */
void fill_combo_box(gchar* widgetname, gchar *settingsname) {
	 GtkComboBox *combobox = GTK_COMBO_BOX(glade_xml_get_widget(xml, widgetname));
	 GtkTreeModel* model = gtk_combo_box_get_model(combobox);
	 GtkTreeIter iter;
	 gboolean have_iter;
	 have_iter = gtk_tree_model_get_iter_first(model,&iter);
	 gboolean found = FALSE;

	 while(have_iter) {
		GValue value = {0, };
		gtk_tree_model_get_value(model,&iter,0,&value);
		if(g_strcmp0(g_value_get_string(&value),g_key_file_get_string(configFile,"chitransit",settingsname,NULL)) == 0) {
			found = TRUE;
			gtk_combo_box_set_active_iter(combobox,&iter); //make this in the combobox
		}/*else {
			g_printf("Compared %s and %s\n",g_value_get_string(&value),g_key_file_get_string(configFile,"chitransit","datapath",NULL));
		}*/
		g_value_unset(&value);
		have_iter = gtk_tree_model_iter_next(model,&iter);
	 }
	 if(!found) {
		 gtk_list_store_prepend(GTK_LIST_STORE(model),&iter);
		 gtk_list_store_set(GTK_LIST_STORE(model),&iter,0,g_key_file_get_string(configFile,"chitransit",settingsname,NULL),-1);
		 gtk_combo_box_set_active_iter(combobox,&iter);
	 }
}

/* another helper function, to update in-memory settings */
void update_settings(gchar* widgetname, gchar *settingsname) {
	GtkComboBox *widget = GTK_COMBO_BOX(glade_xml_get_widget(xml,widgetname));
	g_key_file_set_string(configFile,"chitransit",settingsname,gtk_combo_box_get_active_text(GTK_COMBO_BOX(widget)));
}

/* no need to check if paths exist, since we call g_mkdir_with_parents on all data files
 * also, pdfviewer's existance is handled in the helper */
void on_btnApplyPrefs_clicked(GtkButton *button) {
	update_settings("datapath","datapath");
	update_settings("pdfviewer","pdfviewer");
	prefs_load();
	saveConfig();
}
