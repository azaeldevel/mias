
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = application.cgi

application_cgi_SOURCES = application-main.cc
application_cgi_LDADD = $(MUPOSYS_LIBS)
application_cgi_CXXFLAGS = $(MUPOSYS_FLAGS)


