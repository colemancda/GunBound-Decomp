/* FUN_004056c0 - 0x004056c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-LENGTH FIX (2026-07-30): `unaff_EBX` is a real 3rd argument -
 * the byte count to copy/assign - dropped by Ghidra at EVERY one of this
 * function's ~20 call sites across the tree (a systemic gap, not specific
 * to this file; see functions.h's own K&R-empty declaration). Confirmed
 * via objdump (orig 0x40558b: `mov ebx,eax; call 0x4056c0`, where eax was
 * just computed by an inline strlen loop) - this is a CStringT-style
 * assign-from-buffer helper: `(dest, srcBuffer, length)`. Only the one
 * call site actually reachable in current live testing is fixed here
 * (FUN_00405510.c, itself reached via FUN_00415bc0/FUN_00415900's
 * FourWord.txt/Sound.txt word-list loading); the ~17 other call sites
 * across src/ui_widget and src/unnamed keep their existing (pre-existing,
 * not worsened by this fix) 2-arg calls against the K&R-empty decl -
 * fixing those needs each site's own length expression traced, deferred
 * as a separate sweep rather than guessed at here.
 */
#include "ghidra_types.h"


void FUN_004056c0(int *param_1,undefined4 *param_2,uint length)

{
  int iVar1;
  uint uVar2;
  uint unaff_EBX = length;
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
