/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NLyvOiSU1QzVRVJIFvNgTjVMj35/rFDkpkV7Zl2
1aXTABJDIo2DfMyS4O4gk9AB5sxKNNShEd+QK9ReVre41Hihx+TR5BgpMtmLb0PU8HWaSha3
j8EP9pQVDTQtj8FJ6SbI9GDpg6zHc7uaplAoL5uE0KOKqh8waQWonMdFcX6jEA==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/
























/* Copyright (C) 1991,95,96,2002 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

//#include <signal.h>
//#include <errno.h>

/* Raise the signal SIG.  */
int
raise (sig)
     int sig;
{
//  __set_errno (ENOSYS);
//  return -1;
	return 0;
}
//weak_alias (raise, gsignal)

//stub_warning (raise)
//stub_warning (gsignal)
//#include <stub-tag.h>
