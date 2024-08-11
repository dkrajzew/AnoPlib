dnl Process this file with autoconf to produce a configure script.
AC_INIT(anoplib, 0.1)
AC_CONFIG_SRCDIR(src/AnoPtest.cpp)
AC_CANONICAL_SYSTEM

dnl create an config-header
AC_CONFIG_HEADER(src/config.h)

dnl enable automake-support
AM_INIT_AUTOMAKE([gnu dist-zip tar-ustar dist-bzip2])


dnl the debug check has to be made before the program checks
dnl because it modifies CXXFLAGS
AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],[enable sumo debugging code [default=no].])])
if test x$enable_debug = xyes; then
    AC_DEFINE(_DEBUG, 1, [Define to 1 in order to enable sumo debugging code.])
    CXXFLAGS="-g $CXXFLAGS"
    ac_enabled="$ac_enabled Debug"
else
    CXXFLAGS="-O2 -DNDEBUG $CXXFLAGS"
    ac_disabled="$ac_disabled Debug"
fi


dnl Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

dnl enable libtool-support
dnl gives a deprecated warning for RANLIB with newer libtools
AC_PROG_RANLIB
AM_PROG_LIBTOOL


dnl Check for enable-features that shall go into config.h
AM_CONDITIONAL([WITH_VERSION_H], test -f .svn/entries)
if test -f .svn/entries; then
   AC_DEFINE([HAVE_VERSION_H], [1], [Define if auto-generated version.h should be used.])
else
   AC_DEFINE_UNQUOTED(VERSION_STRING, "$PACKAGE_VERSION", [Defined if auto-generated version.h is unavailable.])
fi

dnl ---------------------------------------------
dnl Platform specific stuff
dnl - - - - - - - - - - - - - - - - - - - - - - -

case "$host" in
   *-cygwin*)
   AC_DEFINE([HAVE_CYGWIN], [1], [Define if compiling under cygwin])
   AC_DEFINE([WIN32], [1], [Xerces and Fox expect this to be defined (cygwin)])
   AC_DEFINE([NOMINMAX], [1], [Including windows.h gives errors otherwise (cygwin)])
   ;;
esac


dnl ---------------------------------------------
dnl check for libraries...
dnl - - - - - - - - - - - - - - - - - - - - - - -
AC_CHECK_HEADERS(GL/gl.h GL/glu.h GL/glut.h,,AC_MSG_ERROR([
Mesa header not found. The Mesa graphics
library is required to compile and run
vdinner.
Check http://mesa3d.sourceforge.net]))

CFLAGS="$CFLAGS $X_CFLAGS"
LIBS="$X_PRE_LIBS $X_LIBS -lX11 -lXext -lXmu -lXt $X_EXTRA_LIBS -lGL -lGLU -lglut -lm"

AC_MSG_CHECKING(for the Mesa graphics library)
AC_TRY_LINK([
#include <GL/glut.h>
],[
glutInitWindowSize(400,400);
glutCreateWindow("test");
glEnable(GL_DEPTH_TEST);
glShadeModel(GL_FLAT);
],AC_MSG_RESULT(yes),AC_MSG_ERROR([
Unable to link to Mesa library. If you
just installed it: try running ldconfig
as root]))

AM_CPPFLAGS="-I$PWD/$srcdir/src $AM_CPPFLAGS"
AC_SUBST(AM_CPPFLAGS)
AC_SUBST(AM_CXXFLAGS)


dnl ---------------------------------------------
dnl Checks proposed by autoscan.
dnl Checks for header files.
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([float.h limits.h malloc.h math.h stddef.h stdlib.h string.h sys/time.h unistd.h wchar.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_C_VOLATILE

dnl Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_CHECK_FUNCS([floor getcwd gettimeofday memset pow select socket sqrt])


dnl ---------------------------------------------
dnl add here all your Makefiles. These will be created by configure
AC_CONFIG_FILES([
bin/Makefile
build/Makefile
build/AnoPtest/Makefile
gfx/Makefile
src/Makefile
Makefile])
AC_OUTPUT

