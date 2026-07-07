/* FUN_0052eb06 - 0x0052eb06 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __cftof
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl __cftof(double *_Value,char *_Buf,size_t _SizeInBytes,int _Dec)

{
  size_t unaff_ESI;
  STRFLT _PtFlt;
  _strflt local_30;
  char local_20 [24];
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  _PtFlt = *(STRFLT *)_Value;
  __fltout2((_CRT_DOUBLE)*_Value,&local_30,local_20,unaff_ESI);
  __fptostr(_Buf + (local_30.sign == 0x2d),local_30.decpt + _SizeInBytes,(int)&local_30,_PtFlt);
  __cftof2(_Buf,_SizeInBytes,0);
  return (errno_t)_Buf;
}

