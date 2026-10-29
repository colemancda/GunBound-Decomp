/* FUN_00409d10 - 0x00409d10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * (FUN_00426780 below is now StringMap_Find_10.)
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): __thiscall with 4 real params
 * (ECX=`this` + ret 0xc = 3 stack dwords, disasm 0x409d10-0x409deb); the
 * declared shape was already correct. The sole caller
 * (fileformat/ParseChooseEventLine.c) dropped `this` entirely (wrote only
 * the 3 stack args). See that file's own header for the call-site
 * reconstruction: `this` = the hash-bucket index FUN_00426780 wrote into
 * its caller's `local_8` out-param.
 *
 * DROPPED-KEY FIX (2026-10-29): the ConstructStringFromText(iVar3) call
 * dropped the key, which the original passes in ECX (`mov ecx,[ebp+0xc]`
 * at 0x409d8b = param_3, with the node pushed at 0x409d8e).  So every
 * ChooseEvent.txt node was built with no key string and
 * StringMap_Find_10 could never match one.  It now passes (key, node).
 * The same bug in the CString-valued twin is fixed in
 * StringMap_Insert_CString's node constructor
 * StringMap_ConstructNode_CString.  The SEH registration through the
 * uninitialised `unaff_FS_OFFSET`, which wrote
 * through a garbage pointer on every call, is stripped too, as in
 * ConstructStringFromText.c.
 */
#include "ghidra_types.h"


int __thiscall FUN_00409d10(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;

  if (param_2[0xb] == 0) {
    piVar1 = _malloc(param_2[9] * 0x10 + 4);
    if (piVar1 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
    *piVar1 = param_2[10];
    param_2[10] = (int)piVar1;
    iVar3 = param_2[9];
    piVar1 = piVar1 + iVar3 * 4 + -3;
    if (-1 < iVar3 + -1) {
      do {
        piVar1[2] = param_2[0xb];
        param_2[0xb] = (int)piVar1;
        piVar1 = piVar1 + -4;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  iVar3 = param_2[0xb];
  param_2[0xb] = *(int *)(iVar3 + 8);
  ConstructStringFromText((char *)param_3,(int *)iVar3);
  *(undefined4 *)(iVar3 + 0xc) = param_4;
  param_2[1] = param_2[1] + 1;
  *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(*param_2 + param_1 * 4);
  *(int *)(*param_2 + param_1 * 4) = iVar3;
  if (((uint)param_2[6] < (uint)param_2[1]) && (param_2[8] == 0)) {
    uVar2 = FUN_00500e30();
    FUN_00409e20(param_2,uVar2);
  }
  return iVar3;
}

