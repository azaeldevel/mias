
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = application.cgi

LIBS = $(MIAS_WEB_LIBS) $(OCTETOS_DB_LIBS)
FLAGS = $(MIAS_WEB_CFLAGS) $(OCTETOS_DB_CFLAGS)
if MIAS_WEB_ENABLE_TDD
FLAGS += -DMIAS_WEB_ENABLE_TDD
endif
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
endif

application_cgi_SOURCES = application-main.cc application.cc application-pizza.cc application-stove.cc application-making.cc
application_cgi_LDADD = $(LIBS)
application_cgi_CXXFLAGS = $(FLAGS)


