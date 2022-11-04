
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
cgi_DATA=cgi/http

htmldir=$(bindir)
html_DATA=html/login.html html/user-register.html html/index.html html/user-mang.html

html_user_mang_permissionsdir=$(bindir)/user-mang/permissions
html_user_mang_permissions_DATA=html/user-mang/permissions/add.html

cssdir=$(bindir)/css/Mkos-Big-Sur
css_DATA=html/css/Mkos-Big-Sur/login.css

css_appearancedir=$(bindir)/css/Mkos-Big-Sur/appearance
css_appearance_DATA=html/css/Mkos-Big-Sur/appearance/muposys.css

css_iconsdir=$(bindir)/css/Mkos-Big-Sur/icons
css_icons_DATA=html/css/Mkos-Big-Sur/icons/application.css

jsdir=$(bindir)/js
js_DATA=html/js/login.js html/js/muposys.js

themedir=$(bindir)/js
theme_DATA=html/js/login.js

if MIAS_WEB_ENABLE_RUNNABLE

install-data-hook:
	chmod a+w $(bindir)/*.html
	chmod a+w -R $(bindir)/css
	chmod a+w -R $(bindir)/js
	chmod a+w -R $(bindir)/user-mang
	chown $(USER_GROUP) $(DATABASE_DIR)
	chown $(USER_GROUP) $(DATABASE_DIR)/$(DATABASE_FN)
	chmod a+w $(DATABASE_DIR)/$(DATABASE_FN)
	chown $(USER_GROUP) $(bindir)/*.html
	chown $(USER_GROUP) -R $(bindir)/css
	chown $(USER_GROUP) -R $(bindir)/js
	chown $(USER_GROUP) -R $(bindir)/user-mang
	mkdir -p $(bindir)/theme
	tar -xf $(top_srcdir)/html/Mkos-Big-Sur.tar.xz -C $(bindir)/theme
	chown $(USER_GROUP) -R $(bindir)/theme

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi

uninstall-hook:
	rm -r $(bindir)/*
	rm -r $(DATABASE_DIR)

endif

