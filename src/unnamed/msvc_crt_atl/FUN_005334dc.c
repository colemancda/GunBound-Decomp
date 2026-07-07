/* FUN_005334dc - 0x005334dc in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Multiple Matches With Different Base Names
    __atodbl
    __atoflt
   
   Library: Visual Studio 2003 Release */

int __cdecl FID_conflict___atodbl(_CRT_FLOAT *_Result,char *_Str)

{
  INTRNCVT_STATUS IVar1;
  undefined1 local_18 [4];
  _LDBL12 local_14;
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  FUN_00535069(&local_14,local_18,_Str,0,0,0,0);
  IVar1 = FID_conflict___ld12tod(&local_14,(_CRT_DOUBLE *)_Result);
  return IVar1;
}

