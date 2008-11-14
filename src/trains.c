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

#include <trains.h>

void load_trains() {
	station yellowstations[] = {
		{"Skokie" , "Skokie" ,0},
		{"Howard" , "Howard" ,1}
	};
	station purplestations[] = {
		{"Linden" , "Linden" ,0},
		{"Central" , "Central" ,1},
		{"Noyes" , "Noyes" ,2},
		{"Foster" , "Foster" ,3},
		{"Davis" , "Davis" ,4},
		{"Dempster" , "Dempster" ,5},
		{"Main" , "Main" ,6},
		{"SouthBlvd" , "South Blvd" ,7},
		{"Howard" , "Howard" ,8}
	};
	station brownstations[] = {
		{"Kimball" , "Kimball" ,0},
		{"Kedzie" , "Kedzie" ,1},
		{"Francisco" , "Francisco" ,2},
		{"Rockwell" , "Rockwell" ,3},
		{"Western" , "Western" ,4},
		{"Montrose" , "Montrose" ,5},
		{"Addison" , "Addison" ,6},
		{"Southport" , "Southport" ,7},
		{"Belmont" , "Belmont" ,8},
		{"Diversey" , "Diversey" ,9},
		{"Fullerton" , "Fullerton" ,10},
		{"Armitage" , "Armitage" ,11},
		{"Sedgwick" , "Sedgwick" ,12},
		{"Chicago" , "Chicago/Franklin" ,13},
		{"MerchandiseMart" , "Merchandise Mart" ,14},
		{"washington" , "Washington/Wells" ,15},
		{"Quincy" , "Quincy" ,16},
		{"Lasalle" , "LaSalle/Van Buren" ,17},
		{"Library" , "Library-State/Van Burn" ,18},
		{"Adams" , "Adams/Wabash" ,19},
		{"Madison" , "Madison/Wabash" ,20},
		{"Randolph" , "Randolph/Wabash" ,21},
		{"State" , "State/Lake" ,22},
		{"Clark" , "Clark/Lake" ,23}
	};
	station redstations[] = {
		{"Howard" , "Howard" ,0},
		{"Jarvis" , "Jarvis" ,1},
		{"Morse" , "Morse" ,2},
		{"Loyola" , "Loyola" ,3},
		{"Granville" , "Granville" ,4},
		{"Thorndale" , "Thorndale" ,5},
		{"BrynMawr" , "Bryn Mawr" ,6},
		{"Berwyn" , "Berwyn" ,7},
		{"Argyle" , "Argyle" ,8},
		{"Lawrence" , "Lawrence" ,9},
		{"Wilson" , "Wilson" ,10},
		{"Sheridan" , "Sheridan" ,11},
		{"Addison" , "Addison" ,12},
		{"Belmont" , "Belmont" ,13},
		{"Fullerton" , "Fullerton" ,14},
		{"NorthClybourn" , "North/Clybourn" ,15},
		{"ClarkDivision" , "Clark/Division" ,16},
		{"Chicago" , "Chicago" ,17},
		{"Grand" , "Grand" ,18},
		{"Lake" , "Lake" ,19},
		{"Monroe" , "Monroe" ,20},
		{"Jackson" , "Jackson" ,21},
		{"Harrison" , "Harrison" ,22},
		{"Roosevelt" , "Roosevelt" ,23},
		{"Cermak" , "Cermak" ,24},
		{"Sox-35th" , "Sox-35th" ,25},
		{"47th" , "47th" ,26},
		{"Garfield" , "Garfield" ,27},
		{"63rd" , "63rd" ,28},
		{"69th" , "69th" ,29},
		{"79th" , "79th" ,30},
		{"87th" , "87th" ,31},
		{"95th" , "95th/Dan Ryan" ,32}
	};
	station bluestations[] = {
		{"Ohare" , "O'Hare" ,0},
		{"Rosemont" , "Rosemont" ,1},
		{"Cumberland" , "Cumberland" ,2},
		{"Harlem" , "Harlem" ,3},
		{"JeffersonPark" , "Jefferson Park" ,4},
		{"Montrose" , "Montrose" ,5},
		{"IrvingPark" , "Irving Park" ,6},
		{"Addison" , "Addison" ,7},
		{"Belmont" , "Belmont" ,8},
		{"LoganSquare" , "Logan Square" ,9},
		{"CaliforniaOHare" , "California" ,10},
		{"WesternOHare" , "Western - O'Hare" ,11},
		{"Damen" , "Damen" ,12},
		{"Division" , "Division" ,13},
		{"Chicago" , "Chicago" ,14},
		{"Grand" , "Grand" ,15},
		{"Washington" , "Washington" ,16},
		{"Monroe" , "Monroe" ,17},
		{"Jackson" , "Jackson" ,18},
		{"LaSalle" , "LaSalle" ,19},
		{"Clinton" , "Clinton" ,20},
		{"UICHalsted" , "UIC-Halsted" ,21},
		{"Racine" , "Racine" ,22},
		{"MedicalDistrict" , "Illinois Medical District" ,23},
		{"WesternCongress" , "Western - Forest Park" ,24},
		{"KedzieHoman" , "Kedzie-Homan" ,25},
		{"PulaskiCongress" , "Pulaski" ,26},
		{"CiceroCongress" , "Cicero" ,27},
		{"Austin" , "Austin" ,28},
		{"OakPark" , "Oak Park" ,29},
		{"HarlemCongress" , "Harlem - Forest Park" ,30},
		{"ForestPark" , "Forest Park" ,31}
	};
	station pinkstations[] = {
		{"54cermak" , "54th/Cermak" ,0},
		{"Cicero" , "Cicero" ,1},
		{"Kostner" , "Kostner" ,2},
		{"Pulaski" , "Pulaski" ,3},
		{"centralpark" , "Central Park" ,4},
		{"Kedzie" , "Kedzie" ,5},
		{"California" , "California" ,6},
		{"Western" , "Western" ,7},
		{"Damen" , "Damen" ,8},
		{"18th" , "18th" ,9},
		{"Polk" , "Polk" ,10},
		{"Ashland" , "Ashland" ,11},
		{"Clinton" , "Clinton" ,12},
		{"clarklake" , "Clark/Lake" ,13},
		{"statelake" , "State/Lake" ,14},
		{"Randolph" , "Randolph" ,15},
		{"Madison" , "Madison" ,16},
		{"Adams" , "Adams/Wabash" ,17},
		{"Library" , "Library-State/Van Burn" ,18},
		{"Lasalle" , "LaSalle/Van Buren" ,19},
		{"Quincy" , "Quincy" ,20},
		{"washington" , "Washington/Wells" ,21}
	};
	station orangestations[] = {
		{"Midway" , "Midway" ,0},
		{"Pulaski" , "Pulaski" ,1},
		{"Kedzie" , "Kedzie" ,2},
		{"Western" , "Western" ,3},
		{"35Archer" , "35th/Archer" ,4},
		{"Ashland" , "Ashland" ,5},
		{"Halsted" , "Halsted" ,6},
		{"Roosevelt" , "Roosevelt" ,7},
		{"Library" , "Library-State/Van Burn" ,8},
		{"Lasalle" , "LaSalle/Van Buren" ,9},
		{"Quincy" , "Quincy" ,10},
		{"washington" , "Washington/Wells" ,11},
		{"Clark" , "Clark/Lake" ,12},
		{"state" , "State/Lake" ,13},
		{"Randolph" , "Randolph" ,14},
		{"Madison" , "Madison" ,15},
		{"Adams" , "Adams/Wabash" ,16}
	};
	station greenstations[] = {
		{"Harlem" , "Harlem" ,0},
		{"OakPark" , "Oak Park" ,1},
		{"Ridgeland" , "Ridgeland" ,2},
		{"Austin" , "Austin" ,3},
		{"Central" , "Central" ,4},
		{"Laramie" , "Laramie" ,5},
		{"Cicero" , "Cicero" ,6},
		{"Pulaski" , "Pulaski" ,7},
		{"Conservatory" , "Conservatory - Central Park" ,8},
		{"Kedzie" , "Kedzie" ,9},
		{"California" , "California" ,10},
		{"Ashland" , "Ashland" ,11},
		{"Clinton" , "Clinton" ,12},
		{"Clark" , "Clark/Lake" ,13},
		{"state" , "State/Lake" ,14},
		{"Randolph" , "Randolph" ,15},
		{"Madison" , "Madison" ,16},
		{"Adams" , "Adams/Wabash" ,17},
		{"Roosevelt" , "Roosevelt" ,18},
		{"35th" , "35th-Bronzeville-IIT" ,19},
		{"Indiana" , "Indiana" ,20},
		{"43rd" , "43rd" ,21},
		{"47th" , "47th" ,22},
		{"51st" , "51st" ,23},
		{"Garfield" , "Garfield" ,24},
		{"Halsted" , "Halsted" ,25},
		{"Ashland63" , "Ashland/63rd" ,26},
		{"KingDr" , "King Dr" ,27},
		{"East63rd" , "Cottage Grove - East 63rd" ,28}
	};

	trainline temp[] = {
		{"yellow", GTK_COMBO_BOX(glade_xml_get_widget(xml, "yellowstations")),g_memdup(yellowstations,sizeof(yellowstations)), 2},
		{"purple", GTK_COMBO_BOX(glade_xml_get_widget(xml, "purplestations")),g_memdup(purplestations,sizeof(purplestations)), 9},
		{"brown", GTK_COMBO_BOX(glade_xml_get_widget(xml, "brownstations")),g_memdup(brownstations,sizeof(brownstations)), 24},
		{"red", GTK_COMBO_BOX(glade_xml_get_widget(xml, "redstations")),g_memdup(redstations,sizeof(redstations)), 33},
		{"blue", GTK_COMBO_BOX(glade_xml_get_widget(xml, "bluestations")),g_memdup(bluestations,sizeof(bluestations)), 32},
		{"pink", GTK_COMBO_BOX(glade_xml_get_widget(xml, "pinkstations")),g_memdup(pinkstations,sizeof(pinkstations)), 22},
		{"orange", GTK_COMBO_BOX(glade_xml_get_widget(xml, "orangestations")),g_memdup(orangestations,sizeof(orangestations)), 17},
		{"green", GTK_COMBO_BOX(glade_xml_get_widget(xml, "greenstations")),g_memdup(greenstations,sizeof(greenstations)), 29}
	};

	lines = g_memdup(temp,sizeof(temp));
	num_of_lines = 8;

	if(g_mkdir_with_parents(getProgData("trains"),0755) != 0) {
		g_warning("Couldn't create folder for train data!");
	}
	GDir* traindir = g_dir_open(getProgData("trains"),0,NULL);
	if(g_dir_read_name(traindir) == NULL) { //only happens if there are zero items in the folder
		return;
	}

	for(gint i=0;i<num_of_lines;++i) {
		GtkListStore* model = GTK_LIST_STORE(gtk_combo_box_get_model(lines[i].box));
		gtk_list_store_clear(model);
		for(gint j=0;j<lines[i].num;++j) {
			gtk_combo_box_append_text(lines[i].box,lines[i].stations[j].displayname);
		}
	}
}

void on_btnupdate_clicked(GtkButton *button) {
	//down em all
	for(gint i=0;i<num_of_lines;++i) {
		gchar trainfolder[512];
		g_snprintf(trainfolder,512,"%s/%s",getProgData("trains"),lines[i].line);
		g_mkdir_with_parents(trainfolder,0755);
		for(gint j=0;j<lines[i].num;++j) {
			gchar url[200];
			gchar dest[512];
			g_snprintf(dest,512,"%s/%s.pdf",trainfolder,lines[i].stations[j].name);
			g_snprintf(url,200,"http://transitchicago.com/maps/rail/%s/%s.pdf\n",lines[i].line,lines[i].stations[j].name);
			downFile(url,dest);
		}
	}
	load_trains();
}

void openStation(GtkComboBox *box) {
	if(gtk_combo_box_get_active_text(box) == NULL) return; //happens initially
	for(gint i=0;i<num_of_lines;++i) {
		if(box == lines[i].box) { //found ya ;)
			gint pos = gtk_combo_box_get_active(box);
			gchar pdf[512];
			g_snprintf(pdf,512,"%s/%s/%s.pdf",getProgData("trains"),lines[i].line,lines[i].stations[pos].name);
			openPDF(pdf);
			return;
		}
	}
}
