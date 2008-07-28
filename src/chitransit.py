#!/usr/bin/python
import gtk
import gtk.glade

def on_mainwindow_destroy(widget):
	gtk.main_quit()


xml = gtk.glade.XML('chitransit.glade')
widget = xml.get_widget('mainwindow')
xml.signal_autoconnect({
	'on_mainwindow_destroy': on_mainwindow_destroy
})
gtk.main()
