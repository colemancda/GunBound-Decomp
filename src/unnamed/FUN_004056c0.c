/* FUN_004056c0 - 0x004056c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004056c0(int *param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  uint unaff_EBX;
  undefined4 *_Dst;
  
  if (unaff_EBX == 0) {
    FUN_00405760();
    return;
  }
  if (param_2 != (undefined4 *)0x0) {
    iVar1 = *param_1;
    uVar2 = *(uint *)(iVar1 + -0xc);
    if ((int)(1U - *(int *)(iVar1 + -4) | *(int *)(iVar1 + -8) - unaff_EBX) < 0) {
      FUN_004057c0();
    }
    _Dst = (undefined4 *)*param_1;
    if (uVar2 < (uint)((int)param_2 - iVar1)) {
      for (uVar2 = unaff_EBX >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *_Dst = *param_2;
        param_2 = param_2 + 1;
        _Dst = _Dst + 1;
      }
      for (uVar2 = unaff_EBX & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined1 *)_Dst = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        _Dst = (undefined4 *)((int)_Dst + 1);
      }
    }
    else {
      _memmove(_Dst,(undefined1 *)((int)_Dst + ((int)param_2 - iVar1)),unaff_EBX);
    }
    if ((-1 < (int)unaff_EBX) && ((int)unaff_EBX <= *(int *)(*param_1 + -8))) {
      *(uint *)(*param_1 + -0xc) = unaff_EBX;
      *(undefined1 *)(unaff_EBX + *param_1) = 0;
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  ThrowCxxException(0x80070057);
}

