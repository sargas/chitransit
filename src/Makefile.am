INCLUDES = -I$(top_srcdir)

AM_CPPFLAGS = \
  -DPKGDATADIR=\"$(pkgdatadir)\" \
  -DTERMINAL_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
  -DDATADIR=\""$(datadir)"\" -D_GNU_SOURCE

AM_CFLAGS = -Wall -pedantic -std=c99 @DEPENDENCIES_CFLAGS@

# add the name of your application
bin_PROGRAMS = chitransit

# add the sources to compile for your application
chitransit_SOURCES = \
  main.c buses.c

chitransit_LDADD  = @DEPENDENCIES_LIBS@

MAINTAINERCLEANFILES  = config.h.in Makefile.in

