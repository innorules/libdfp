/* _Decimal32 fpclassify classification function.

   Copyright (C) 2006 IBM Corporation.
   Copyright (C) 2010 Free Software Foundation, Inc.

   This file is part of the Decimal Floating Point C Library.

   Author(s): Steven Munroe <munroesj@us.ibm.com>
              Ryan S. Arnold <rsa@us.ibm.com>

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see libdfp/COPYING.txt for more information.  */

#ifndef _DECIMAL_SIZE
#  define _DECIMAL_SIZE 32
#endif

#include <math.h>

#define FUNCTION_NAME fpclassify

#include <dfpmacro.h>

int
INTERNAL_FUNCTION_NAME (DEC_TYPE x)
{
  int result = 0;
/* check in order, FP_NORMAL, FP_ZERO, FP_SUBNORMAL, FP_INFINITE,
   FP_NAN.  The though is the most liky case exits early.  */
  __asm__(	"dtstdc cr0,%1,0x08;"
		"li %0,4;"
		"beq cr0,1f;"
		"dtstdc cr0,%1,0x20;"
		"li %0,2;"
		"beq cr0,1f;"
		"dtstdc cr0,%1,0x10;"
		"li %0,3;"
		"beq cr0,1f;"
		"dtstdc cr0,%1,0x04;"
		"li %0,1;"
		"beq cr0,1f;"
		"li %0,0;"
	"1:;"
	: "=r" (result): "f" ((_Decimal64) x): "cr0");
  return result;
}

weak_alias (INTERNAL_FUNCTION_NAME, EXTERNAL_FUNCTION_NAME)
