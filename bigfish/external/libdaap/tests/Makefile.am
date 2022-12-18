#
# $Id: Makefile.am,v 1.4 2003/05/29 16:11:14 bootc Exp $
# libdaap: Makefile.am
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

INCLUDES = -I$(top_srcdir)/include

EXTRA_DIST = server-info content-codes

check_PROGRAMS = chunk-read chunk-build

chunk_read_SOURCES = chunk-read.cpp
chunk_read_LDADD = $(top_srcdir)/lib/libdaap.la

chunk_build_SOURCES = chunk-build.cpp
chunk_build_LDADD = $(top_srcdir)/lib/libdaap.la

TESTS = $(check_PROGRAMS)
