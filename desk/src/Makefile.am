
muposysdir = $(datadir)/mias
muposys_DATA = mias.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DMUPOSYS_DATA_DIR=\""$(datadir)/muposys"\" \
	-DDATA_DIR=\""$(datadir)/mias"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/mias"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(GTK_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = mias-desk 

lib_LTLIBRARIES = libmias-desk.la

LIBS = $(GTK_LIBS) $(MUPOSYS_LIBS)
FLAGS = $(GTK_CFLAGS) $(MUPOSYS_CFLAGS)
if MIAS_DESK_ENABLE_TDD
FLAGS += -DMIAS_DESK_ENABLE_TDD
endif
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
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