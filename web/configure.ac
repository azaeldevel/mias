
AC_INIT(mias-web, 0.30.0-alpha, azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11])
AM_SILENT_RULES([yes])
AC_PROG_CXX
LT_INIT

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
dnl IT_PROG_INTLTOOL([0.35.0])

dnl GETTEXT_PACKAGE=muposys_web
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
dnl AM_GLIB_GNU_GETTEXT

PKG_CHECK_MODULES(MIAS_WEB, [openssl octetos-core octetos-db-abstract muposys-cgi mias-core])

AC_ARG_ENABLE([os],[AS_HELP_STRING([--enable-os],[Enable configuration for particular OS])])
case $enableval in
	  	archlinux)
			AC_DEFINE([LINUX_ARCH], [], [Enable configuration for Arch-Linux])
			AC_SUBST([DATABASE_DIR],[$datarootdir])
			AC_SUBST([DATABASE_FN],[http])
			AC_SUBST([USER_GROUP],[http:http])
		;;
	  	debian) 
			AC_DEFINE([LINUX_DEBIAN], [], [Enable configuration for Debian])
		;;
	  	*)
			AC_MSG_ERROR([unknown option '$enable_os' for --enable-os])
		;;
esac

AC_ARG_ENABLE([tdd],[AS_HELP_STRING([--enable-tdd],[Enable Test-Drive Developing mode)])])
if test "x$enable_tdd" = "xyes"; then 
	AM_CONDITIONAL(MIAS_WEB_ENABLE_TDD, true)
	PKG_CHECK_MODULES(CUNIT, [cunit])
else
	AM_CONDITIONAL(MIAS_WEB_ENABLE_TDD, false)
fi

AM_CONDITIONAL(OCTETOS_DB_MEDIUMWORD,false)
AM_CONDITIONAL(DATABASE_ENGINE_MARIA,false)
AM_CONDITIONAL(DATABASE_ENGINE_MYSQL,false)
AM_CONDITIONAL(DATABASE_ENGINE_POSTGRESQL,false)
AC_ARG_ENABLE([database],[AS_HELP_STRING([--enable-database],[Enabling sopport for Database])])
case $enableval in
	maria)
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-maria])
		AM_CONDITIONAL(OCTETOS_DB_MEDIUMWORD,true)
		AM_CONDITIONAL(DATABASE_ENGINE_MARIA,true)
	;;
	mysql)
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-mysql])
		AM_CONDITIONAL(OCTETOS_DB_MEDIUMWORD,true)
		AM_CONDITIONAL(DATABASE_ENGINE_MYSQL,true)
	;;
	postgresql)
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-postgresql])
		AM_CONDITIONAL(OCTETOS_DB_MEDIUMWORD,true)
		AM_CONDITIONAL(DATABASE_ENGINE_POSTGRESQL,true)
	;;
	*)
		AC_MSG_ERROR([unknown option '$enable_database' for --enable-database])
	;;
esac

AC_ARG_ENABLE([runnable],[AS_HELP_STRING([--enable-runnable],[Enable Test-Drive Developing mode feature)])])
if test "x$enable_runnable" = "xyes"; then 
	AM_CONDITIONAL(MIAS_WEB_ENABLE_RUNNABLE, true)
else
	AM_CONDITIONAL(MIAS_WEB_ENABLE_RUNNABLE, false)
fi



AC_OUTPUT([
Makefile
cgi/Makefile
])
