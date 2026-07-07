/* FUN_0052e9fe - 0x0052e9fe in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __cftoe
   
   Library: Visual Studio 2003 Release */

errno_t __cdecl __cftoe(double *_Value,char *_Buf,size_t _SizeInBytes,int _Dec,int _Caps)

{
  size_t unaff_ESI;
  STRFLT _PtFlt;
  _strflt local_30;
  char local_20 [24];
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  _PtFlt = *(STRFLT *)_Value;
  __fltout2((_CRT_DOUBLE)*_Value,&local_30,local_20,unaff_ESI);
  __fptostr(_Buf + (uint)(0 < (int)_SizeInBytes) + (uint)(local_30.sign == 0x2d),_SizeInBytes + 1,
            (int)&local_30,_PtFlt);
  __cftoe2(_SizeInBytes,_Dec,0);
  return (errno_t)_Buf;
}

