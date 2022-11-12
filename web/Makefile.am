
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

html_user_mang_permissionsdir=$(bindir)/user-mang/permissions
html_user_mang_permissions_DATA=

cssdir=$(bindir)/css/Mkos-Big-Sur
css_DATA=

css_appearancedir=$(bindir)/css/Mkos-Big-Sur/appearance
css_appearance_DATA=

css_iconsdir=$(bindir)/css/Mkos-Big-Sur/icons
css_icons_DATA=

jsdir=$(bindir)/js
js_DATA=html/js/mias.js

themedir=$(bindir)/js
theme_DATA=

if MIAS_WEB_ENABLE_RUNNABLE

install-data-hook:
	

install-exec-hook:
	

uninstall-hook:
	

endif

