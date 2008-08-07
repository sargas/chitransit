#!/usr/bin/perl

# we are generating c code to make gtk objects
# perl handles multidiminsional arrays better
# (and everythign else ;) )
#
# theres no runtime dependance, but this program needs to be rerun when theres
# updates to this @stations matrix
#
#
# yes, this is cheating c. so be it


# we take advantage of case-insensativity of cta servers
# when that aint enough, the optional second part of the station is a nice name
@stations = (
	[ 'yellow', [
		['Skokie'],
#		[Niles Center stop....someday...],	
		['Howard']
	]],
	[ 'purple', [
		['Linden'],
		['Central'],
		['Noyes'],
		['Foster'],
		['Davis'],
		['Dempster'],
		['Main'],
		['SouthBlvd','South Blvd'],
		['Howard']
	]],
	[ 'brown', [
		['Kimball'],
		['Kedzie'],
		['Francisco'],
		['Rockwell'],
		['Western'],
		['Montrose'],
		['Addison'],
		['Southport'],
		['Belmont'], #this and ahead include purple express
		['Diversey'],
		['Fullerton'],
		['Armitage'],
		['Sedgwick'],
		['Chicago','Chicago/Franklin'],
		['MerchandiseMart','Merchandise Mart'],
		['washington','Washington/Wells'],
		['Quincy'],
		['Lasalle','LaSalle/Van Buren'],
		['Library','Library-State/Van Burn'],
		['Adams','Adams/Wabash'],
		['Madison','Madison/Wabash'],
		['Randolph','Randolph/Wabash'],
		['State','State/Lake'],
		['Clark','Clark/Lake']
	]],
	[ 'red', [
		['Howard'],
		['Jarvis'],
		['Morse'],
		['Loyola'],
		['Granville'],
		['Thorndale'],
		['BrynMawr','Bryn Mawr'],
		['Berwyn'],
		['Argyle'],
		['Lawrence'],
		['Wilson'],
		['Sheridan'],
		['Addison'],
		['Belmont'],
		['Fullerton'],
		['NorthClybourn','North/Clybourn'],
		['ClarkDivision','Clark/Division'],
		['Chicago','Chicago'],
		['Grand'],
		['Lake'],
		['Monroe'],
		['Jackson'],
		['Harrison'],
		['Roosevelt'],
		['Cermak'],
		['Sox-35th'], #wow, its on their server in pretty form
		['47th'],
		['Garfield'],
		['63rd'],
		['69th'],
		['79th'],
		['87th'],
		['95th','95th/Dan Ryan']
	]],
	['blue', [
		['Ohare',"O'Hare"],
		['Rosemont'],
		['Cumberland'],
		['Harlem'],
		['JeffersonPark','Jefferson Park'], # good ol' jeff
		['Montrose'],
		['IrvingPark','Irving Park'],
		['Addison'],
		['Belmont'],
		['LoganSquare', 'Logan Square'],
		['CaliforniaOHare','California'], #probably cuz of cali in douglas branch
		['WesternOHare',"Western - O'Hare"],
		['Damen'],
		['Division'],
		['Chicago'],
		['Grand'],
		['Washington'],
		['Monroe'],
		['Jackson'],
		['LaSalle'],
		['Clinton'],
		['UICHalsted','UIC-Halsted'],
		['Racine'],
		['MedicalDistrict','Illinois Medical District'],
		['WesternCongress','Western - Forest Park'],
		['KedzieHoman','Kedzie-Homan'],
		['PulaskiCongress','Pulaski'],
		['CiceroCongress','Cicero'],
		['Austin'],
		['OakPark','Oak Park'],
		['HarlemCongress','Harlem - Forest Park'],
		['ForestPark','Forest Park']
	]],
	[ 'pink', [
		['54cermak','54th/Cermak'],
		['Cicero'],
		['Kostner'],
		['Pulaski'],
		['centralpark','Central Park'],
		['Kedzie'],
		['California'],
		['Western'],
		['Damen'],
		['18th'],
		['Polk'],
		['Ashland'],
		['Clinton'],
		['clarklake','Clark/Lake'],
		['statelake','State/Lake'],
		['Randolph'],
		['Madison'],
		['Adams','Adams/Wabash'],
		['Library','Library-State/Van Burn'],
		['Lasalle','LaSalle/Van Buren'],
		['Quincy'],
		['washington','Washington/Wells']
	]],
	[ 'orange', [
		['Midway'],
		['Pulaski'],
		['Kedzie'],
		['Western'],
		['35Archer','35th/Archer'],
		['Ashland'],
		['Halsted'],
		['Roosevelt'],
		['Library','Library-State/Van Burn'],
		['Lasalle','LaSalle/Van Buren'],
		['Quincy'],
		['washington','Washington/Wells'],
		['Clark','Clark/Lake'],
		['state','State/Lake'],
		['Randolph'],
		['Madison'],
		['Adams','Adams/Wabash']
	]],
	[ 'green', [
		['Harlem'],
		['OakPark','Oak Park'],
		['Ridgeland'],
		['Austin'],
		['Central'],
		['Laramie'],
		['Cicero'],
		['Pulaski'],
		['Conservatory','Conservatory - Central Park'],
		['Kedzie'],
		['California'],
		['Ashland'],
		['Clinton'],
		['Clark','Clark/Lake'],
		['state','State/Lake'],
		['Randolph'],
		['Madison'],
		['Adams','Adams/Wabash'],
		['Roosevelt'],
		['35th','35th-Bronzeville-IIT'],
		['Indiana'],
		['43rd'],
		['47th'],
		['51st'],
		['Garfield'],
		['Halsted'],
		['Ashland63','Ashland/63rd'],
		['KingDr','King Dr'],
		['East63rd','Cottage Grove - East 63rd']
	]]
);



##### PAST THIS, SHOULD NOT BE MODIFIED IF YOUR JUST ADDING/CHANGING STATIONS

foreach $line (@stations) {
	print "station " . $line->[0] . "stations[] = {\n";
	$blah = 0;
	foreach $station (@{$line->[1]}) {
		print ",\n" if($blah);$blah++;
		print "\t{\"" . $station->[0] . "\" , \"" .
			(defined($station->[1])?$station->[1]:$station->[0]) . "\" ,".($blah-1) ."}";
	}
	print "\n};\n";
}


print "trainline temp[] = {\n";
$blah = 0;
foreach $line (@stations) {
	print ",\n" if($blah != 0);$blah++;
	print "\t{";
	print "\"" . $line->[0] . 
		"\", GTK_COMBO_BOX(glade_xml_get_widget(xml, \"" . $line->[0] . "stations\")),". 
		"g_memdup(" . $line->[0] . "stations,sizeof(" . $line->[0] . "stations)), ". @{$line->[1]} . "}";
}
print "\n};\n";

print "\nlines = g_memdup(temp,sizeof(temp));\n";
print "num_of_lines = ". @stations . ";\n";
