/* FUN_00533687 - 0x00533687 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __fltout2
   
   Library: Visual Studio 2003 Release */

STRFLT __cdecl __fltout2(_CRT_DOUBLE _Dbl,STRFLT _Flt,char *_ResultStr,size_t _SizeInBytes)

{
  int iVar1;
  short local_30;
  char local_2e;
  undefined1 local_2c [24];
  undefined4 local_14;
  undefined4 uStack_10;
  undefined2 uStack_c;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  ___dtold(&local_14,&_Dbl);
  iVar1 = _I10_OUTPUT(local_14,uStack_10,uStack_c,0x11,0,&local_30);
  _Flt->flag = iVar1;
  _Flt->sign = (int)local_2e;
  _Flt->decpt = (int)local_30;
  FUN_0052baa0(_ResultStr,local_2c);
  _Flt->mantissa = _ResultStr;
  return _Flt;
}

