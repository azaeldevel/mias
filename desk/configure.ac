
AC_INIT(mias-desk, 0.5.0-beta, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX

LT_INIT

PKG_CHECK_MODULES(GTK, [gtkmm-3.0])

PKG_CHECK_MODULES(MUPOSYS, [muposys-desk mias-core])

dnl AC_DEFINE_UNQUOTED([MUPOSYS], [true] ,[Signal for local compilation])

AC_ARG_ENABLE([os],[AS_HELP_STRING([--enable-os],[Enable configuration for particular OS])])
case $enableval in
	  	archlinux)
			AC_DEFINE([LINUX_ARCH], [], [Enable configuration for Arch-Linux])
			AC_SUBST([DATABASE_DIR],[$datarootdir])
			AC_SUBST([DATABASE_FN],[http])
			AC_SUBST([USER_GROUP],[http:http])
			AC_DEFINE_UNQUOTED([DATABASE_DIR], ["$DATABASE_DIR"] ,[Full path for database file])
			AC_DEFINE_UNQUOTED([DATABASE_FN], ["$DATABASE_FN"] ,[Full path for database file])
			AC_DEFINE_UNQUOTED([DATABASE], ["$DATABASE_DIR/$DATABASE_FN"] ,[Full path for database file])
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
	AM_CONDITIONAL(MIAS_DESK_ENABLE_TDD, true)
	PKG_CHECK_MODULES(CUNIT, [cunit])
else
	AM_CONDITIONAL(MIAS_DESK_ENABLE_TDD, false)
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

AC_OUTPUT([
Makefile
src/Makefile
])
