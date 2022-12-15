
SUBDIRS = cgi 


dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

uninstall-local:
	-rm -r $(docdir)

cgidir=$(datarootdir)
cgi_DATA=

htmldir=$(bindir)
html_DATA=

cssdir=$(bindir)/css/
css_DATA=html/css/mias.css

css_appearancedir=$(bindir)/css/Mkos-Big-Sur/appearance
css_appearance_DATA=

css_iconsdir=$(bindir)/css/Mkos-Big-Sur/icons
css_icons_DATA=

jsdir=$(bindir)/js
js_DATA=html/js/mias.js

themedir=$(bindir)/theme/Mkos-Big-Sur
theme_DATA=

if MIAS_WEB_ENABLE_RUNNABLE

install-data-hook:
	chown $(USER_GROUP) -R $(bindir)/css
	chown $(USER_GROUP) -R $(bindir)/js
	cp $(top_srcdir)/icons/eat-pizza.svg $(bindir)/theme/Mkos-Big-Sur/24x24/actions
	
install-exec-hook:
	

uninstall-hook:
	

endif

