#
# $Id: configure.ac,v 1.6 2003/05/29 16:11:14 bootc Exp $
# libdaap: configure.am
#
# Created by Chris Boot on Sun May 04 2003.
# Copyright (C) 2003 Chris Boot
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
# Process this file with autoconf to produce a configure script.
#

AC_PREREQ(2.57)

AC_INIT(libdaap, [0.0.4], [bootc@mac.com])
AC_CONFIG_SRCDIR([lib/chunk.cpp])

AM_INIT_AUTOMAKE([gnu dist-bzip2])
AM_CONFIG_HEADER([config.h])
AM_MAINTAINER_MODE

DAAP_VERSION_INFO=0:3:0

AC_SUBST(DAAP_VERSION_INFO)
AC_REVISION($Revision: 1.6 $)

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_BIGENDIAN
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

# Check for debugging
CFLAGS="$CFLAGS -Wall -Wno-unknown-pragmas"
CXXFLAGS="$CXXFLAGS -Wall -Wno-unknown-pragmas"
AC_MSG_CHECKING([whether to enable debug options])
AC_ARG_ENABLE(debug,
[  --enable-debug          Enable debugging
  --disable-debug         Disable debugging],
[ case "$enableval" in
  no)
       AC_MSG_RESULT(no)

    # strip off debugger flags
    NEWFLAGS=""
    for flag in $CFLAGS; do
      case "$flag" in
      -g*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CFLAGS="$NEWFLAGS"

    # strip off debugger flags
    NEWFLAGS=""
    for flag in $CXXFLAGS; do
      case "$flag" in
      -g*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CXXFLAGS="$NEWFLAGS"
       ;;
  *)   AC_MSG_RESULT(yes)

    # strip off optimizer flags
    NEWFLAGS=""
    for flag in $CFLAGS; do
      case "$flag" in
      -O*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CFLAGS="$NEWFLAGS"

    # strip off optimizer flags
    NEWFLAGS=""
    for flag in $CXXFLAGS; do
      case "$flag" in
      -O*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CXXFLAGS="$NEWFLAGS"
       ;;
  esac ],
       AC_MSG_RESULT(no)
[
    # strip off debugger flags
    NEWFLAGS=""
    for flag in $CFLAGS; do
      case "$flag" in
      -g*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CFLAGS="$NEWFLAGS"

    # strip off debugger flags
    NEWFLAGS=""
    for flag in $CXXFLAGS; do
      case "$flag" in
      -g*)
        dnl echo "cut off $flag"
        ;;
      *)
        NEWFLAGS="$NEWFLAGS $flag"
        ;;
      esac
    done
    CXXFLAGS="$NEWFLAGS"
]
)

# Output files
AC_CONFIG_FILES([
    Makefile
    include/Makefile
    lib/Makefile
    macosx/Makefile
    tests/Makefile
])
AC_OUTPUT
