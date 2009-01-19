INCLUDES = -I$(top_srcdir)

AM_CPPFLAGS = \
  -DPKGDATADIR=\"$(pkgdatadir)\" \
  -DDATADIR=\""$(datadir)"\" -D_GNU_SOURCE

AM_CFLAGS = -Wall -Werror -pedantic -std=c99 @DEPENDENCIES_CFLAGS@

# add the name of your application
bin_PROGRAMS = chitransit

# add the sources to compile for your application
chitransit_SOURCES = \
  main.c buses.c helpers.c prefs.c maps.c trains.c faq.c

chitransit_LDADD  = @DEPENDENCIES_LIBS@

MAINTAINERCLEANFILES  = config.h.in Makefile.in

