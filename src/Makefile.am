
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = application.cgi

LIBS_LIST = $(MUPOSYS_LIBS) $(OCTETOS_DB_LIBS)
LIBS_FLAGS = $(MUPOSYS_CFLAGS) $(OCTETOS_DB_CFLAGS)
 
application_cgi_SOURCES = application-main.cc application.cc
application_cgi_LDADD = $(LIBS_LIST)
application_cgi_CXXFLAGS = $(LIBS_FLAGS)


