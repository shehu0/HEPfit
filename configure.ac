AC_PREREQ([2.59])
AC_INIT([SusyFit], [0.2], [shehu@cantab.net], [SusyFit], [susyfit.roma1.infn.it])
AC_CONFIG_AUX_DIR([Config])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([Config/config.h])

AM_INIT_AUTOMAKE
AM_PROG_AR

AC_LANG(C++)
AM_INIT_AUTOMAKE([1.10 -Wall -Werror no-define])
LT_INIT


AC_PROG_CC([gcc])
AC_PROG_CXX([g++])
AC_PROG_F77
AC_F77_LIBRARY_LDFLAGS

AX_PATH_GSL(1.11, , AC_MSG_ERROR(could not find required version of GSL)) #GSL 
ROOT_PATH(3.03/05, AC_DEFUN([HAVE_ROOT]), AC_MSG_ERROR(ROOT is not found or version is too old)) #ROOT
SUSYFIT_CHECK_GSL
SUSYFIT_LOOPTOOLS_PATH
BOOST_REQUIRE
BOOST_PROGRAM_OPTIONS  
SUSYFIT_BAT_PATH

AC_SUBST(SuF_CFLAGS)
AC_SUBST(SuF_LIBS)

AC_SUBST([SusyFit_SO_VERSION], [0:2:0])
AC_SUBST([SusyFit_API_VERSION], [0.2])

AC_CONFIG_FILES([Makefile
		SusyFit-${SusyFit_API_VERSION}.pc:SusyFit.pc.in
		susyfit-config
		], [chmod +x susyfit-config])



AC_SUBST([susyFitCflags],["$(export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:.; ./susyfit-config --cflags)"])
AC_SUBST([susyFitLibs],["$(export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:.; ./susyfit-config --libs)"])

SUSYFIT_OVERVIEW

AC_CONFIG_COMMANDS([summary],[cat config.susyfit])

AC_OUTPUT
