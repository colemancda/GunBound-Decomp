/* FUN_004fd880 - 0x004fd880 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall FUN_004fd880(int param_1,int param_2,char *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *_Dest;
  uint uVar4;
  char acStack_176e [5994];
  undefined4 uStack_4;
  
  uStack_4 = 0x4fd88a;
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0x1700;
  }
  _Dest = acStack_176e;
  iVar3 = 0;
  for (uVar4 = 0;
      (iVar1 = *(int *)(param_2 + 4), iVar1 != 0 &&
      (uVar4 < (uint)((*(int *)(param_2 + 8) - iVar1) / 0x12))); uVar4 = uVar4 + 1) {
    _strncpy(_Dest,(char *)(iVar3 + iVar1),0x10);
    _Dest = _Dest + 0x10;
    iVar3 = iVar3 + 0x12;
  }
  _strncpy(_Dest,param_3,0x14);
  uVar2 = FUN_00502500(0x3004);
  return uVar2;
}

