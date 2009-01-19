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

#include <faq.h>

void load_faq() {
	//does the faq exist?
	GtkTextView *view = GTK_TEXT_VIEW(glade_xml_get_widget(xml,"faqviewer"));
	GtkTextBuffer* buff = gtk_text_view_get_buffer(view);
	if(g_access(getProgData("faq.txt"),R_OK) == 0) {
		//2^18 seems like a good value, the current size is 156602
		gchar* filecontents = g_malloc(262144);
		gsize length;
		g_file_get_contents(getProgData("faq.txt"),&filecontents,&length,NULL);
		gtk_text_buffer_set_text(buff,filecontents,length);
		g_free(filecontents);
	} else {
		gtk_text_buffer_set_text(buff,"Note: you need to have 'links' installed to retrieve the Chicago-l.org FAQ",-1);
	}
}

void on_btnfaq_clicked(GtkButton *button) {
	pid_t pid = fork();
	if(pid == 0) {
		//just for this fork, we'll redefine standard output
		g_freopen(getProgData("faq.txt"),"w",stdout);
		execlp("links","links","-dump","http://www.chicago-l.org/FAQ.html",0);
		fclose(stdout);
		//error
		_exit(-42);
	} else {
		int status,died;
		died = wait(&status);
		//printf("%d\n",WEXITSTATUS(status));
		if(WEXITSTATUS(status) != 0) {
			GtkTextView *view = GTK_TEXT_VIEW(glade_xml_get_widget(xml,"faqviewer"));
			GtkTextBuffer* buff = gtk_text_view_get_buffer(view);
			gtk_text_buffer_set_text(buff,"Running links -dump failed, make sure you have links installed",-1);
		} else {
			load_faq();
		}
	}
}
