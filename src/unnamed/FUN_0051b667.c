/* FUN_0051b667 - 0x0051b667 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SIGNATURE FIX (2026-09-20, no-prototype sweep). Ghidra's original
 * `undefined8 __fastcall FUN_0051b667(undefined4 param_1,undefined4
 * param_2, float *param_3, ...)` over-declared by TWO phantom leading
 * parameters. Evidence: the prologue is `push ebp; lea ebp,[esp+8];
 * pushal` - ebp is set to point at the FIRST caller-pushed stack
 * argument (no register args are consumed for it), so `[ebp+0]` is the
 * float* array the body actually uses first (old `param_3`), not a
 * third argument after two register ones. The lone epilogue (orig
 * 0x51c560-0x51c567: `popal; pop ebp; mov eax,[0x5687fc]; ret`) is a
 * BARE `ret` with no stack-cleanup operand - i.e. all 7 real arguments
 * are plain caller-cleaned stack params, matching the 7 args the sole
 * caller (FUN_00517d10, itself just a `void` passthrough) already
 * passes. The old `param_1` (would-be ECX) is never read anywhere in
 * the body - fully vestigial, dropped outright. The old `param_2`
 * (would-be EDX) is never read for computation either, but IS threaded
 * into the final `CONCAT44(param_2,DAT_005687fc)` 64-bit return - since
 * nothing ever set EDX in this function, `popal` simply restores
 * whatever the caller happened to leave there. The sole caller discards
 * the return value entirely (`void FUN_00517d10` never captures it), so
 * this is provably inconsequential; modelled as `in_EDX` (Ghidra's usual
 * idiom for "value read from a register this function never wrote"),
 * not as a formal parameter callers must supply. Renumbered the 7 real
 * parameters param_1..param_7 (were param_3..param_9).
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined8
FUN_0051b667(float *param_1,float *param_2,int param_3,int param_4,int param_5,int param_6,
            int param_7)

{
  undefined4 in_EDX;
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int iVar9;
  
  if (param_4 == 2) {
    param_4 = 0;
  }
  iVar8 = (int)((ulonglong)(longlong)(param_5 + 0x11) / 0x12);
  iVar9 = 0;
  if (0 < iVar8) {
    do {
      fVar1 = DAT_00f25944 * param_1[0x11] + DAT_00f25900 * *param_1;
      fVar4 = (DAT_00f25900 * *param_1 - DAT_00f25944 * param_1[0x11]) * DAT_00f25960;
      fVar2 = DAT_00f25924 * param_1[9] + DAT_00f25920 * param_1[8];
      fVar3 = (DAT_00f25920 * param_1[8] - DAT_00f25924 * param_1[9]) * DAT_00f25980;
      DAT_00568738 = fVar1 + fVar2;
      DAT_0056874c = fVar1 - fVar2;
      DAT_00568798 = fVar3 + fVar4;
      DAT_005687ac = fVar4 - fVar3;
      fVar1 = DAT_00f25940 * param_1[0x10] + DAT_00f25904 * param_1[1];
      fVar4 = (DAT_00f25904 * param_1[1] - DAT_00f25940 * param_1[0x10]) * DAT_00f25964;
      fVar2 = DAT_00f25928 * param_1[10] + DAT_00f2591c * param_1[7];
      fVar3 = (DAT_00f2591c * param_1[7] - DAT_00f25928 * param_1[10]) * DAT_00f2597c;
      DAT_0056873c = fVar1 + fVar2;
      DAT_00568750 = fVar1 - fVar2;
      DAT_0056879c = fVar3 + fVar4;
      DAT_005687b0 = fVar4 - fVar3;
      fVar1 = DAT_00f2593c * param_1[0xf] + DAT_00f25908 * param_1[2];
      fVar4 = (DAT_00f25908 * param_1[2] - DAT_00f2593c * param_1[0xf]) * DAT_00f25968;
      fVar2 = DAT_00f2592c * param_1[0xb] + DAT_00f25918 * param_1[6];
      fVar3 = (DAT_00f25918 * param_1[6] - DAT_00f2592c * param_1[0xb]) * DAT_00f25978;
      DAT_00568740 = fVar1 + fVar2;
      DAT_00568754 = fVar1 - fVar2;
      DAT_005687a0 = fVar3 + fVar4;
      DAT_005687b4 = fVar4 - fVar3;
      fVar1 = DAT_00f25938 * param_1[0xe] + DAT_00f2590c * param_1[3];
      fVar4 = (DAT_00f2590c * param_1[3] - DAT_00f25938 * param_1[0xe]) * DAT_00f2596c;
      fVar2 = DAT_00f25930 * param_1[0xc] + DAT_00f25914 * param_1[5];
      fVar3 = (DAT_00f25914 * param_1[5] - DAT_00f25930 * param_1[0xc]) * DAT_00f25974;
      DAT_00568744 = fVar1 + fVar2;
      DAT_00568758 = fVar1 - fVar2;
      DAT_005687a4 = fVar3 + fVar4;
      DAT_005687b8 = fVar4 - fVar3;
      DAT_00568748 = DAT_00f25934 * param_1[0xd] + DAT_00f25910 * param_1[4];
      DAT_005687a8 = (DAT_00f25910 * param_1[4] - DAT_00f25934 * param_1[0xd]) * DAT_00f25970;
      fVar1 = (DAT_00568738 + DAT_0056873c + DAT_00568740 + DAT_00568744 + DAT_00568748) *
              _DAT_005687f8;
      *param_1 = fVar1;
      fVar2 = (DAT_00568798 + DAT_0056879c + DAT_005687a0 + DAT_005687a4 + DAT_005687a8) *
              _DAT_005687f8;
      fVar4 = DAT_00f259b0 * DAT_0056874c;
      fVar6 = DAT_00f259b4 * DAT_00568750;
      fVar5 = DAT_00f259b8 * DAT_00568754;
      fVar7 = DAT_00f259bc * DAT_00568758;
      fVar3 = (DAT_00f259bc * DAT_005687b8 +
              DAT_00f259b8 * DAT_005687b4 +
              DAT_00f259b4 * DAT_005687b0 + DAT_00f259b0 * DAT_005687ac) - fVar2;
      fVar2 = fVar2 - fVar1;
      param_1[1] = fVar2;
      fVar2 = (fVar7 + fVar5 + fVar6 + fVar4) - fVar2;
      param_1[2] = fVar2;
      fVar1 = (DAT_00f259cc * DAT_00568744 +
              DAT_00f259c8 * DAT_00568740 +
              DAT_00f259c4 * DAT_0056873c + DAT_00f259c0 * DAT_00568738) - DAT_00568748;
      fVar4 = ((DAT_00f259cc * DAT_005687a4 +
               DAT_00f259c8 * DAT_005687a0 +
               DAT_00f259c4 * DAT_0056879c + DAT_00f259c0 * DAT_00568798) - DAT_005687a8) - fVar3;
      fVar3 = fVar3 - fVar2;
      param_1[3] = fVar3;
      fVar1 = fVar1 - fVar3;
      param_1[4] = fVar1;
      fVar2 = ((DAT_0056874c - DAT_00568754) - DAT_00568758) * DAT_00f259d0;
      fVar3 = ((DAT_005687ac - DAT_005687b4) - DAT_005687b8) * DAT_00f259d0 - fVar4;
      fVar4 = fVar4 - fVar1;
      param_1[5] = fVar4;
      fVar2 = fVar2 - fVar4;
      param_1[6] = fVar2;
      fVar1 = DAT_00f259ec * DAT_00568744 +
              DAT_00f259e8 * DAT_00568740 +
              DAT_00f259e4 * DAT_0056873c + DAT_00f259e0 * DAT_00568738 + DAT_00568748;
      fVar4 = (DAT_00f259ec * DAT_005687a4 +
               DAT_00f259e8 * DAT_005687a0 +
               DAT_00f259e4 * DAT_0056879c + DAT_00f259e0 * DAT_00568798 + DAT_005687a8) - fVar3;
      fVar3 = fVar3 - fVar2;
      param_1[7] = fVar3;
      fVar1 = fVar1 - fVar3;
      param_1[8] = fVar1;
      fVar3 = DAT_00f259f0 * DAT_0056874c;
      fVar6 = DAT_00f259f4 * DAT_00568750;
      fVar5 = DAT_00f259f8 * DAT_00568754;
      fVar7 = DAT_00f259fc * DAT_00568758;
      fVar2 = (DAT_00f259fc * DAT_005687b8 +
              DAT_00f259f8 * DAT_005687b4 +
              DAT_00f259f4 * DAT_005687b0 + DAT_00f259f0 * DAT_005687ac) - fVar4;
      fVar4 = fVar4 - fVar1;
      param_1[9] = fVar4;
      fVar4 = (fVar7 + fVar5 + fVar6 + fVar3) - fVar4;
      param_1[10] = fVar4;
      fVar1 = ((DAT_00568738 + DAT_00568740 + DAT_00568744) * _DAT_005687f8 - DAT_0056873c) -
              DAT_00568748;
      fVar3 = (((DAT_00568798 + DAT_005687a0 + DAT_005687a4) * _DAT_005687f8 - DAT_0056879c) -
              DAT_005687a8) - fVar2;
      fVar2 = fVar2 - fVar4;
      param_1[0xb] = fVar2;
      fVar1 = fVar1 - fVar2;
      param_1[0xc] = fVar1;
      fVar2 = DAT_00f25a10 * DAT_0056874c;
      fVar6 = DAT_00f25a14 * DAT_00568750;
      fVar5 = DAT_00f25a18 * DAT_00568754;
      fVar7 = DAT_00f25a1c * DAT_00568758;
      fVar4 = (DAT_00f25a1c * DAT_005687b8 +
              DAT_00f25a18 * DAT_005687b4 +
              DAT_00f25a14 * DAT_005687b0 + DAT_00f25a10 * DAT_005687ac) - fVar3;
      fVar3 = fVar3 - fVar1;
      param_1[0xd] = fVar3;
      fVar3 = (fVar7 + fVar5 + fVar6 + fVar2) - fVar3;
      param_1[0xe] = fVar3;
      fVar1 = DAT_00f25a2c * DAT_00568744 +
              DAT_00f25a28 * DAT_00568740 +
              DAT_00f25a24 * DAT_0056873c + DAT_00f25a20 * DAT_00568738 + DAT_00568748;
      fVar2 = DAT_00f25a2c * DAT_005687a4 +
              DAT_00f25a28 * DAT_005687a0 +
              DAT_00f25a24 * DAT_0056879c + DAT_00f25a20 * DAT_00568798 + DAT_005687a8;
      fVar3 = fVar4 - fVar3;
      param_1[0xf] = fVar3;
      fVar1 = fVar1 - fVar3;
      param_1[0x10] = fVar1;
      param_1[0x11] = (fVar2 - fVar4) - fVar1;
      *(float *)(param_3 + iVar9 * 4) =
           (float)(&DAT_00f25b00)[param_4 * 0x24] * param_1[9] + *param_2;
      *(float *)(param_3 + 0x480 + iVar9 * 4) =
           (float)(&DAT_00f25b24)[param_4 * 0x24] * param_1[0x11] + param_2[9];
      *(float *)(param_3 + 0x80 + iVar9 * 4) =
           (float)(&DAT_00f25b04)[param_4 * 0x24] * param_1[10] + param_2[1];
      *(float *)(param_3 + 0x500 + iVar9 * 4) =
           (float)(&DAT_00f25b28)[param_4 * 0x24] * param_1[0x10] + param_2[10];
      *(float *)(param_3 + 0x100 + iVar9 * 4) =
           (float)(&DAT_00f25b08)[param_4 * 0x24] * param_1[0xb] + param_2[2];
      *(float *)(param_3 + 0x580 + iVar9 * 4) =
           (float)(&DAT_00f25b2c)[param_4 * 0x24] * param_1[0xf] + param_2[0xb];
      *(float *)(param_3 + 0x180 + iVar9 * 4) =
           (float)(&DAT_00f25b0c)[param_4 * 0x24] * param_1[0xc] + param_2[3];
      *(float *)(param_3 + 0x600 + iVar9 * 4) =
           (float)(&DAT_00f25b30)[param_4 * 0x24] * param_1[0xe] + param_2[0xc];
      *(float *)(param_3 + 0x200 + iVar9 * 4) =
           (float)(&DAT_00f25b10)[param_4 * 0x24] * param_1[0xd] + param_2[4];
      *(float *)(param_3 + 0x680 + iVar9 * 4) =
           (float)(&DAT_00f25b34)[param_4 * 0x24] * param_1[0xd] + param_2[0xd];
      *(float *)(param_3 + 0x280 + iVar9 * 4) =
           (float)(&DAT_00f25b14)[param_4 * 0x24] * param_1[0xe] + param_2[5];
      *(float *)(param_3 + 0x700 + iVar9 * 4) =
           (float)(&DAT_00f25b38)[param_4 * 0x24] * param_1[0xc] + param_2[0xe];
      *(float *)(param_3 + 0x300 + iVar9 * 4) =
           (float)(&DAT_00f25b18)[param_4 * 0x24] * param_1[0xf] + param_2[6];
      *(float *)(param_3 + 0x780 + iVar9 * 4) =
           (float)(&DAT_00f25b3c)[param_4 * 0x24] * param_1[0xb] + param_2[0xf];
      *(float *)(param_3 + 0x380 + iVar9 * 4) =
           (float)(&DAT_00f25b1c)[param_4 * 0x24] * param_1[0x10] + param_2[7];
      *(float *)(param_3 + 0x800 + iVar9 * 4) =
           (float)(&DAT_00f25b40)[param_4 * 0x24] * param_1[10] + param_2[0x10];
      *(float *)(param_3 + 0x400 + iVar9 * 4) =
           (float)(&DAT_00f25b20)[param_4 * 0x24] * param_1[0x11] + param_2[8];
      *(float *)(param_3 + 0x880 + iVar9 * 4) =
           (float)(&DAT_00f25b44)[param_4 * 0x24] * param_1[9] + param_2[0x11];
      fVar1 = *param_1;
      fVar2 = param_1[8];
      *param_1 = (float)(&DAT_00f25b48)[param_4 * 0x24] * fVar2;
      param_1[8] = (float)(&DAT_00f25b68)[param_4 * 0x24] * fVar1;
      param_1[9] = fVar1 * (float)(&DAT_00f25b6c)[param_4 * 0x24];
      param_1[0x11] = fVar2 * (float)(&DAT_00f25b8c)[param_4 * 0x24];
      fVar1 = param_1[1];
      fVar2 = param_1[7];
      param_1[1] = (float)(&DAT_00f25b4c)[param_4 * 0x24] * fVar2;
      param_1[7] = (float)(&DAT_00f25b64)[param_4 * 0x24] * fVar1;
      param_1[10] = fVar1 * (float)(&DAT_00f25b70)[param_4 * 0x24];
      param_1[0x10] = fVar2 * (float)(&DAT_00f25b88)[param_4 * 0x24];
      fVar1 = param_1[2];
      fVar2 = param_1[6];
      param_1[2] = (float)(&DAT_00f25b50)[param_4 * 0x24] * fVar2;
      param_1[6] = (float)(&DAT_00f25b60)[param_4 * 0x24] * fVar1;
      param_1[0xb] = fVar1 * (float)(&DAT_00f25b74)[param_4 * 0x24];
      param_1[0xf] = fVar2 * (float)(&DAT_00f25b84)[param_4 * 0x24];
      fVar1 = param_1[3];
      fVar2 = param_1[5];
      param_1[3] = (float)(&DAT_00f25b54)[param_4 * 0x24] * fVar2;
      param_1[5] = (float)(&DAT_00f25b5c)[param_4 * 0x24] * fVar1;
      param_1[0xc] = fVar1 * (float)(&DAT_00f25b78)[param_4 * 0x24];
      param_1[0xe] = fVar2 * (float)(&DAT_00f25b80)[param_4 * 0x24];
      fVar1 = param_1[4];
      fVar2 = (float)(&DAT_00f25b7c)[param_4 * 0x24];
      param_1[4] = fVar1 * (float)(&DAT_00f25b58)[param_4 * 0x24];
      param_1[0xd] = fVar1 * fVar2;
      param_1 = param_1 + 0x12;
      param_2 = param_2 + 0x12;
      iVar9 = iVar9 + 1;
    } while (iVar9 < iVar8);
  }
  for (; iVar9 < (int)((ulonglong)(longlong)(param_6 + 0x11) / 0x12); iVar9 = iVar9 + 1) {
    DAT_00568738 = param_1[0xf] * DAT_00f258d4 + *param_1 * DAT_00f258c0;
    DAT_00568744 = (*param_1 * DAT_00f258c0 - param_1[0xf] * DAT_00f258d4) * DAT_00f258e0;
    DAT_0056873c = param_1[0xc] * DAT_00f258d0 + param_1[3] * DAT_00f258c4;
    DAT_00568748 = (param_1[3] * DAT_00f258c4 - param_1[0xc] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568740 = param_1[9] * DAT_00f258cc + param_1[6] * DAT_00f258c8;
    DAT_0056874c = (param_1[6] * DAT_00f258c8 - param_1[9] * DAT_00f258cc) * DAT_00f258e8;
    DAT_00568750 = param_1[0x10] * DAT_00f258d4 + param_1[1] * DAT_00f258c0;
    DAT_0056875c = (param_1[1] * DAT_00f258c0 - param_1[0x10] * DAT_00f258d4) * DAT_00f258e0;
    DAT_00568754 = param_1[0xd] * DAT_00f258d0 + param_1[4] * DAT_00f258c4;
    DAT_00568760 = (param_1[4] * DAT_00f258c4 - param_1[0xd] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568758 = param_1[10] * DAT_00f258cc + param_1[7] * DAT_00f258c8;
    DAT_00568764 = (param_1[7] * DAT_00f258c8 - param_1[10] * DAT_00f258cc) * DAT_00f258e8;
    DAT_00568768 = param_1[0x11] * DAT_00f258d4 + param_1[2] * DAT_00f258c0;
    DAT_00568774 = (param_1[2] * DAT_00f258c0 - param_1[0x11] * DAT_00f258d4) * DAT_00f258e0;
    DAT_0056876c = param_1[0xe] * DAT_00f258d0 + param_1[5] * DAT_00f258c4;
    DAT_00568778 = (param_1[5] * DAT_00f258c4 - param_1[0xe] * DAT_00f258d0) * DAT_00f258e4;
    DAT_00568770 = param_1[0xb] * DAT_00f258cc + param_1[8] * DAT_00f258c8;
    DAT_0056877c = (param_1[8] * DAT_00f258c8 - param_1[0xb] * DAT_00f258cc) * DAT_00f258e8;
    fVar1 = DAT_00568738 + DAT_00568740;
    fVar6 = DAT_00568744 + DAT_0056874c;
    fVar2 = fVar1 + DAT_0056873c;
    *param_1 = fVar2;
    fVar4 = fVar6 + DAT_00568748;
    fVar5 = (DAT_00568738 - DAT_00568740) * _DAT_00f25a30;
    fVar3 = (DAT_00568744 - DAT_0056874c) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_1[1] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_1[2] = fVar5;
    fVar1 = (fVar1 - DAT_0056873c) - DAT_0056873c;
    fVar2 = (fVar6 - DAT_00568748) - DAT_00568748;
    fVar5 = fVar3 - fVar5;
    param_1[3] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_1[4] = fVar1;
    param_1[5] = (fVar2 - fVar3) - fVar1;
    fVar1 = DAT_00568750 + DAT_00568758;
    fVar6 = DAT_0056875c + DAT_00568764;
    fVar2 = fVar1 + DAT_00568754;
    param_1[6] = fVar2;
    fVar4 = fVar6 + DAT_00568760;
    fVar5 = (DAT_00568750 - DAT_00568758) * _DAT_00f25a30;
    fVar3 = (DAT_0056875c - DAT_00568764) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_1[7] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_1[8] = fVar5;
    fVar1 = (fVar1 - DAT_00568754) - DAT_00568754;
    fVar2 = (fVar6 - DAT_00568760) - DAT_00568760;
    fVar5 = fVar3 - fVar5;
    param_1[9] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_1[10] = fVar1;
    param_1[0xb] = (fVar2 - fVar3) - fVar1;
    fVar1 = DAT_00568768 + DAT_00568770;
    fVar6 = DAT_00568774 + DAT_0056877c;
    fVar2 = fVar1 + DAT_0056876c;
    param_1[0xc] = fVar2;
    fVar4 = fVar6 + DAT_00568778;
    fVar5 = (DAT_00568768 - DAT_00568770) * _DAT_00f25a30;
    fVar3 = (DAT_00568774 - DAT_0056877c) * _DAT_00f25a30 - fVar4;
    fVar4 = fVar4 - fVar2;
    param_1[0xd] = fVar4;
    fVar5 = fVar5 - fVar4;
    param_1[0xe] = fVar5;
    fVar1 = (fVar1 - DAT_0056876c) - DAT_0056876c;
    fVar2 = (fVar6 - DAT_00568778) - DAT_00568778;
    fVar5 = fVar3 - fVar5;
    param_1[0xf] = fVar5;
    fVar1 = fVar1 - fVar5;
    param_1[0x10] = fVar1;
    param_1[0x11] = (fVar2 - fVar3) - fVar1;
    *(float *)(param_3 + iVar9 * 4) = *param_2;
    *(float *)(param_3 + 0x180 + iVar9 * 4) = param_2[3];
    fVar1 = DAT_00f25c20;
    *(float *)(param_3 + 0x300 + iVar9 * 4) = param_1[3] * DAT_00f25c20 + param_2[6];
    fVar2 = DAT_00f25c2c;
    *(float *)(param_3 + 0x480 + iVar9 * 4) = param_1[5] * DAT_00f25c2c + param_2[9];
    *(float *)(param_3 + 0x600 + iVar9 * 4) =
         fVar1 * param_1[9] + param_2[0xc] + DAT_00f25c38 * param_1[2];
    *(float *)(param_3 + 0x780 + iVar9 * 4) =
         fVar2 * param_1[0xb] + param_2[0xf] + DAT_00f25c44 * *param_1;
    *(float *)(param_3 + 0x80 + iVar9 * 4) = param_2[1];
    *(float *)(param_3 + 0x200 + iVar9 * 4) = param_2[4];
    fVar1 = DAT_00f25c24;
    *(float *)(param_3 + 0x380 + iVar9 * 4) = param_1[4] * DAT_00f25c24 + param_2[7];
    fVar2 = DAT_00f25c30;
    *(float *)(param_3 + 0x500 + iVar9 * 4) = param_1[4] * DAT_00f25c30 + param_2[10];
    *(float *)(param_3 + 0x680 + iVar9 * 4) =
         fVar1 * param_1[10] + param_2[0xd] + DAT_00f25c3c * param_1[1];
    *(float *)(param_3 + 0x800 + iVar9 * 4) =
         fVar2 * param_1[10] + param_2[0x10] + DAT_00f25c48 * param_1[1];
    *(float *)(param_3 + 0x100 + iVar9 * 4) = param_2[2];
    *(float *)(param_3 + 0x280 + iVar9 * 4) = param_2[5];
    fVar1 = DAT_00f25c28;
    *(float *)(param_3 + 0x400 + iVar9 * 4) = param_1[5] * DAT_00f25c28 + param_2[8];
    fVar2 = DAT_00f25c34;
    *(float *)(param_3 + 0x580 + iVar9 * 4) = param_1[3] * DAT_00f25c34 + param_2[0xb];
    *(float *)(param_3 + 0x700 + iVar9 * 4) =
         fVar1 * param_1[0xb] + param_2[0xe] + DAT_00f25c40 * *param_1;
    *(float *)(param_3 + 0x880 + iVar9 * 4) =
         fVar2 * param_1[9] + param_2[0x11] + DAT_00f25c4c * param_1[2];
    *param_1 = DAT_00f25c20 * param_1[0xf] + DAT_00f25c38 * param_1[8];
    param_1[3] = DAT_00f25c2c * param_1[0x11] + DAT_00f25c44 * param_1[6];
    param_1[1] = DAT_00f25c24 * param_1[0x10] + DAT_00f25c3c * param_1[7];
    param_1[4] = DAT_00f25c30 * param_1[0x10] + DAT_00f25c48 * param_1[7];
    param_1[2] = DAT_00f25c28 * param_1[0x11] + DAT_00f25c40 * param_1[6];
    param_1[5] = DAT_00f25c34 * param_1[0xf] + DAT_00f25c4c * param_1[8];
    param_1[6] = DAT_00f25c38 * param_1[0xe];
    param_1[9] = DAT_00f25c44 * param_1[0xc];
    param_1[7] = DAT_00f25c3c * param_1[0xd];
    param_1[10] = DAT_00f25c48 * param_1[0xd];
    param_1[8] = DAT_00f25c40 * param_1[0xc];
    param_1[0xb] = DAT_00f25c4c * param_1[0xe];
    param_1[0xc] = 0.0;
    param_1[0xf] = 0.0;
    param_1[0xd] = 0.0;
    param_1[0x10] = 0.0;
    param_1[0xe] = 0.0;
    param_1[0x11] = 0.0;
    param_1 = param_1 + 0x12;
    param_2 = param_2 + 0x12;
  }
  iVar8 = DAT_00563d98;
  for (; DAT_00563d98 = iVar8, iVar9 < (int)((ulonglong)(longlong)(param_7 + 0x11) / 0x12);
      iVar9 = iVar9 + 1) {
    *(float *)(param_3 + iVar9 * 4) = *param_2;
    *(float *)(param_3 + 0x80 + iVar9 * 4) = param_2[1];
    *(float *)(param_3 + 0x100 + iVar9 * 4) = param_2[2];
    *(float *)(param_3 + 0x180 + iVar9 * 4) = param_2[3];
    *(float *)(param_3 + 0x200 + iVar9 * 4) = param_2[4];
    *(float *)(param_3 + 0x280 + iVar9 * 4) = param_2[5];
    *(float *)(param_3 + 0x300 + iVar9 * 4) = param_2[6];
    *(float *)(param_3 + 0x380 + iVar9 * 4) = param_2[7];
    *(float *)(param_3 + 0x400 + iVar9 * 4) = param_2[8];
    *(float *)(param_3 + 0x480 + iVar9 * 4) = param_2[9];
    *(float *)(param_3 + 0x500 + iVar9 * 4) = param_2[10];
    *(float *)(param_3 + 0x580 + iVar9 * 4) = param_2[0xb];
    *(float *)(param_3 + 0x600 + iVar9 * 4) = param_2[0xc];
    *(float *)(param_3 + 0x680 + iVar9 * 4) = param_2[0xd];
    *(float *)(param_3 + 0x700 + iVar9 * 4) = param_2[0xe];
    *(float *)(param_3 + 0x780 + iVar9 * 4) = param_2[0xf];
    *(float *)(param_3 + 0x800 + iVar9 * 4) = param_2[0x10];
    *(float *)(param_3 + 0x880 + iVar9 * 4) = param_2[0x11];
    param_2 = param_2 + 0x12;
    iVar8 = DAT_00563d98;
  }
  DAT_005687fc = iVar9 * 0x12;
  for (; iVar9 < iVar8; iVar9 = iVar9 + 1) {
    *(undefined4 *)(param_3 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x80 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x100 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x180 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x200 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x280 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x300 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x380 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x400 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x480 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x500 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x580 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x600 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x680 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x700 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x780 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x800 + iVar9 * 4) = 0;
    *(undefined4 *)(param_3 + 0x880 + iVar9 * 4) = 0;
  }
  return CONCAT44(in_EDX,DAT_005687fc);
}

