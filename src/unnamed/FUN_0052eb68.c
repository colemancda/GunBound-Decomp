/* FUN_0052eb68 - 0x0052eb68 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __cftog
   
   Library: Visual Studio 2003 Release */

void __cftog(double *param_1,int param_2,size_t param_3,undefined4 param_4)

{
  char *_Buf;
  int iVar1;
  size_t unaff_EDI;
  char *pcVar2;
  STRFLT _PtFlt;
  _strflt local_30;
  char local_20 [24];
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  _PtFlt = *(STRFLT *)param_1;
  __fltout2((_CRT_DOUBLE)*param_1,&local_30,local_20,unaff_EDI);
  iVar1 = local_30.decpt + -1;
  _Buf = (char *)((uint)(local_30.sign == 0x2d) + param_2);
  __fptostr(_Buf,param_3,(int)&local_30,_PtFlt);
  local_30.decpt = local_30.decpt + -1;
  if ((local_30.decpt < -4) || ((int)param_3 <= local_30.decpt)) {
    __cftoe2(param_3,param_4,1);
  }
  else {
    if (iVar1 < local_30.decpt) {
      do {
        pcVar2 = _Buf;
        _Buf = pcVar2 + 1;
      } while (*pcVar2 != '\0');
      pcVar2[-1] = '\0';
    }
    __cftof2(param_2,param_3,1);
  }
  return;
}

