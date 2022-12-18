//===-------------------------- cxa_apple.cxx -----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "libdaap/cxxabi.h"

//
// This file implements Apple extensions to the __cxa_* C++ ABI:
//
void __cxa_bad_typeid()
{
	//abort_message("__cxa_bad_typeid() called during dynamic cast");
}

void __cxa_bad_cast()
{
	//abort_message("__cxa_bad_cast() called");
}
