
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmias-core.la

LIBS = $(OCTETOS_DB_LIBS) $(MUPOSYS_LIBS)
FLAGS = $(OCTETOS_DB_CFLAGS) $(MUPOSYS_CFLAGS)
if MIAS_DESK_ENABLE_TDD
FLAGS += -DMIAS_DESK_ENABLE_TDD
endif
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
endif


libmias_core_la_CXXFLAGS = $(FLAGS) 
libmias_core_la_LDFLAGS = 
libmias_core_la_SOURCES = Exception.cc core.cc
libmias_core_la_LIBADD =  $(LIBS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = mias-core.pc
mias_includedir = $(includedir)/mias/core
mias_include_HEADERS = core.hh Exception.hh