
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-core.la

libmuposys_core_la_CXXFLAGS = $(FLAGS) 
libmuposys_core_la_LDFLAGS = 
libmuposys_core_la_SOURCES = Exception.cc
libmuposys_core_la_LIBADD =  $(LIBS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-core.pc
muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = core.hh Exception.hh