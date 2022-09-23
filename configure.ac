
AC_INIT(mias, 0.1.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
dnl IT_PROG_INTLTOOL([0.35.0])

dnl GETTEXT_PACKAGE=mias
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
dnl AM_GLIB_GNU_GETTEXT



dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin*)
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")


LT_INIT


PKG_CHECK_MODULES(MUPOSYS, [muposys-apidb muposys-cgi])

AC_ARG_ENABLE([os],[AS_HELP_STRING([--enable-os],[Enable configuration for particular OS])])
	case $enableval in
	  	archlinux)
			AC_DEFINE([LINUX_ARCH], [], [Enable configuration for Arch-Linux])
			AC_SUBST([DATABASE],[$datarootdir/http])
			AC_SUBST([USER_GROUP],[http:http])
			AC_DEFINE_UNQUOTED([DATABASE], ["$DATABASE"] ,[Full path for database file])
		;;
	  	debian) 
			AC_DEFINE([LINUX_DEBIAN], [], [Enable configuration for Debian])
		;;
	  	*)
			AC_MSG_ERROR([unknown option '$enable_os' for --enable-os])
		;;
	esac


AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi

AC_ARG_ENABLE([devel], AS_HELP_STRING([--enable-devel], [Soport de desarrollador activo]))
if test "x$enable_devel" = "xyes"; then 
	dnl AC_SUBST([ENABLE_DEVEL],[true])
	AC_DEFINE_UNQUOTED([ENABLE_DEVEL], [], [Soporte de desarrollador activo])
	AM_CONDITIONAL(ENABLE_DEVEL, true)
else 
	AM_CONDITIONAL(ENABLE_DEVEL, false)
fi

AC_ARG_ENABLE([database],[AS_HELP_STRING([--enable-database],[Enabling sopport for Database])])
case $enableval in
	maria)
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-maria])
		AM_CONDITIONAL(WITH_MARIADB,true)
		AM_CONDITIONAL(WITH_MYSQL,false)
		AM_CONDITIONAL(WITH_POSTGRESQL,false)
		AC_DEFINE_UNQUOTED([DATABASE_ENGINE_MARIA], [], [Enabling Database Server MariaDB])
		AC_DEFINE_UNQUOTED([OCTETOS_DB_MEDIUMWORD], [], [Enabling medium word size for database])
	;;
	mysql) 
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-mysql])
		AM_CONDITIONAL(WITH_MARIADB,false)
		AM_CONDITIONAL(WITH_MYSQL,true)
		AM_CONDITIONAL(WITH_POSTGRESQL,false)
		AC_DEFINE_UNQUOTED([DATABASE_ENGINE_MYSQL], [], [Enabling Database Server MySQL])
		AC_DEFINE_UNQUOTED([OCTETOS_DB_MEDIUMWORD], [], [Enabling medium word size for database])
	;;
	postgresql) 
		PKG_CHECK_MODULES(OCTETOS_DB, [octetos-db-postgresql])
		AM_CONDITIONAL(WITH_MARIADB,false)
		AM_CONDITIONAL(WITH_MYSQL,false)
		AM_CONDITIONAL(WITH_POSTGRESQL,true)
		AC_DEFINE_UNQUOTED([DATABASE_ENGINE_POSTGRESQL], [], [Enabling Database Server PostgreSQL])
		AC_DEFINE_UNQUOTED([OCTETOS_DB_MEDIUMWORD], [], [Enabling medium word size for database])
	;;
	*)
		AC_MSG_ERROR([unknown option '$enable_database' for --enable-database])
	;;
esac





AC_OUTPUT([
Makefile
src/Makefile
])
