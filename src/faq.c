#include <faq.h>

void load_faq() {
	//does the faq exist?
	GtkTextView *view = GTK_TEXT_VIEW(glade_xml_get_widget(xml,"faqviewer"));
	if(g_access(getProgData("faq.txt"),R_OK) == 0) {
		GtkTextBuffer* buff = gtk_text_view_get_buffer(view);
		//2^18 seems like a good value, the current size is 156602
		gchar* filecontents = g_malloc(262144);
		gsize length;
		g_file_get_contents(getProgData("faq.txt"),&filecontents,&length,NULL);
		gtk_text_buffer_set_text(buff,filecontents,length);
		g_free(filecontents);
	}
}

void on_btnfaq_clicked(GtkButton *button) {
	pid_t pid = fork();
	if(pid == 0) {
		//just for this fork, we'll redefine standard output
		g_freopen(getProgData("faq.txt"),"w",stdout);
		execlp("links2","links2","-dump","http://www.chicago-l.org/FAQ.html",0);
		fclose(stdout);
		//error
		_exit(-42);
	} else {
		int status,died;
		died = wait(&status);
		printf("%d\n",WEXITSTATUS(status));
		if(WEXITSTATUS(status) != 0) {
			GtkTextView *view = GTK_TEXT_VIEW(glade_xml_get_widget(xml,"faqviewer"));
			GtkTextBuffer* buff = gtk_text_view_get_buffer(view);
			gtk_text_buffer_set_text(buff,"Running links2 -dump failed, make sure you have links2 installed",-1);
		} else {
			load_faq();
		}
	}
}
