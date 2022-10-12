
muposysdir = $(datadir)/muposys/mias/desk
muposys_DATA = mias-desk.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DDATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)/muposys/mias/desk"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(GTK_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = mias-desk 

lib_LTLIBRARIES = libmias-desk.la

LIBS = $(GTK_LIBS) $(MUPOSYS_LIBS)
FLAGS = $(GTK_CFLAGS) $(MUPOSYS_CFLAGS)
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif

mias-glade.c : $(top_srcdir)/resources.xml $(top_srcdir)/desk.ui
	glib-compile-resources --generate-source --c-name rc_glade_mias --target=mias-glade.c $(top_srcdir)/resources.xml --sourcedir $(top_srcdir)/
	
mias_desk_LDADD = $(LIBS)
mias_desk_CXXFLAGS = $(FLAGS)
mias_desk_SOURCES = desk.cc desk.hh desk-main.cc

libmias_desk_la_CXXFLAGS = $(FLAGS) 
libmias_desk_la_LDFLAGS = 
libmias_desk_la_SOURCES = desk.cc desk.hh 
libmias_desk_la_LIBADD =  $(LIBS)

EXTRA_DIST = $(muposys_DATA)

uninstall-local:
	-rm -r $(muposysdir)