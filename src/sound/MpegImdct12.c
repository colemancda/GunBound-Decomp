/* MpegImdct12 - 0x0051b436 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051b436.)
 *
 * Evidence for the name (all from outside the body):
 * Its only caller is the one-argument cdecl thunk MpegImdct12Thunk
 * (0x51c690), which MpegImdctViaKernels (0x517d40) calls once per remaining
 * subband block (those past the long-block limit, windowed with the type-2
 * window at 0xf25c20) and then combines the 18 in-place results with
 * short-window products. The tables it reads are the 12-point set built by
 * InitMpegImdctKernelTables (GetMpegImdctShortTables record 0x568810: the
 * entry loads edi=0xf258c0 and esi=0xf258e0 and multiplies by the scalar at
 * 0xf25a30). It reads in[0], in[3], in[6], in[9], in[12], in[15] (6 inputs at
 * stride 0xc bytes) and the same at offsets 1 and 2, i.e. three interleaved
 * 12-point transforms per 18-sample block, which is the ISO short-block
 * layout of three windows. MpegImdct36 is the long-block counterpart.
 * OPEN ITEM (do not change yet): the asm loads eax=0x568738 as the base of a
 * scratch array and indexes across it, while this port keeps those cells as
 * separate scalars DAT_00568738.. DAT_00568778; same issue as MpegImdct36.
 *
 * SIGNATURE CORRECTED (2026-08-25).  Same hand-written-asm shape as
 * MpegSynthWindow8HalfInterleaved and its two siblings: entry `push ebp; lea ebp,[esp+8];
 * pushal`, exit `popal; pop ebp; ret`, ret 0 with the caller cleaning up.
 * Every general register is saved and restored, so ECX, EDX and EAX are all
 * written before any read -- phantoms, not arguments -- and Ghidra's
 * `return CONCAT44(param_2,in_EAX)` is popal restoring EDX:EAX, not a value.
 * The real arguments are the 1 stack slot(s) its caller already passes.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl MpegImdct12(float *param_3)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  DAT_00568738 = param_3[0xf] * DAT_00f258d4 + *param_3 * DAT_00f258c0;
  DAT_00568744 = (*param_3 * DAT_00f258c0 - param_3[0xf] * DAT_00f258d4) * DAT_00f258e0;
  DAT_0056873c = param_3[0xc] * DAT_00f258d0 + param_3[3] * DAT_00f258c4;
  DAT_00568748 = (param_3[3] * DAT_00f258c4 - param_3[0xc] * DAT_00f258d0) * DAT_00f258e4;
  DAT_00568740 = param_3[9] * DAT_00f258cc + param_3[6] * DAT_00f258c8;
  DAT_0056874c = (param_3[6] * DAT_00f258c8 - param_3[9] * DAT_00f258cc) * DAT_00f258e8;
  DAT_00568750 = param_3[0x10] * DAT_00f258d4 + param_3[1] * DAT_00f258c0;
  DAT_0056875c = (param_3[1] * DAT_00f258c0 - param_3[0x10] * DAT_00f258d4) * DAT_00f258e0;
  DAT_00568754 = param_3[0xd] * DAT_00f258d0 + param_3[4] * DAT_00f258c4;
  DAT_00568760 = (param_3[4] * DAT_00f258c4 - param_3[0xd] * DAT_00f258d0) * DAT_00f258e4;
  DAT_00568758 = param_3[10] * DAT_00f258cc + param_3[7] * DAT_00f258c8;
  DAT_00568764 = (param_3[7] * DAT_00f258c8 - param_3[10] * DAT_00f258cc) * DAT_00f258e8;
  DAT_00568768 = param_3[0x11] * DAT_00f258d4 + param_3[2] * DAT_00f258c0;
  DAT_00568774 = (param_3[2] * DAT_00f258c0 - param_3[0x11] * DAT_00f258d4) * DAT_00f258e0;
  DAT_0056876c = param_3[0xe] * DAT_00f258d0 + param_3[5] * DAT_00f258c4;
  DAT_00568778 = (param_3[5] * DAT_00f258c4 - param_3[0xe] * DAT_00f258d0) * DAT_00f258e4;
  DAT_00568770 = param_3[0xb] * DAT_00f258cc + param_3[8] * DAT_00f258c8;
  DAT_0056877c = (param_3[8] * DAT_00f258c8 - param_3[0xb] * DAT_00f258cc) * DAT_00f258e8;
  fVar1 = DAT_00568738 + DAT_00568740;
  fVar6 = DAT_00568744 + DAT_0056874c;
  fVar2 = fVar1 + DAT_0056873c;
  *param_3 = fVar2;
  fVar4 = fVar6 + DAT_00568748;
  fVar5 = (DAT_00568738 - DAT_00568740) * _DAT_00f25a30;
  fVar3 = (DAT_00568744 - DAT_0056874c) * _DAT_00f25a30 - fVar4;
  fVar4 = fVar4 - fVar2;
  param_3[1] = fVar4;
  fVar5 = fVar5 - fVar4;
  param_3[2] = fVar5;
  fVar1 = (fVar1 - DAT_0056873c) - DAT_0056873c;
  fVar2 = (fVar6 - DAT_00568748) - DAT_00568748;
  fVar5 = fVar3 - fVar5;
  param_3[3] = fVar5;
  fVar1 = fVar1 - fVar5;
  param_3[4] = fVar1;
  param_3[5] = (fVar2 - fVar3) - fVar1;
  fVar1 = DAT_00568750 + DAT_00568758;
  fVar6 = DAT_0056875c + DAT_00568764;
  fVar2 = fVar1 + DAT_00568754;
  param_3[6] = fVar2;
  fVar4 = fVar6 + DAT_00568760;
  fVar5 = (DAT_00568750 - DAT_00568758) * _DAT_00f25a30;
  fVar3 = (DAT_0056875c - DAT_00568764) * _DAT_00f25a30 - fVar4;
  fVar4 = fVar4 - fVar2;
  param_3[7] = fVar4;
  fVar5 = fVar5 - fVar4;
  param_3[8] = fVar5;
  fVar1 = (fVar1 - DAT_00568754) - DAT_00568754;
  fVar2 = (fVar6 - DAT_00568760) - DAT_00568760;
  fVar5 = fVar3 - fVar5;
  param_3[9] = fVar5;
  fVar1 = fVar1 - fVar5;
  param_3[10] = fVar1;
  param_3[0xb] = (fVar2 - fVar3) - fVar1;
  fVar1 = DAT_00568768 + DAT_00568770;
  fVar6 = DAT_00568774 + DAT_0056877c;
  fVar2 = fVar1 + DAT_0056876c;
  param_3[0xc] = fVar2;
  fVar4 = fVar6 + DAT_00568778;
  fVar5 = (DAT_00568768 - DAT_00568770) * _DAT_00f25a30;
  fVar3 = (DAT_00568774 - DAT_0056877c) * _DAT_00f25a30 - fVar4;
  fVar4 = fVar4 - fVar2;
  param_3[0xd] = fVar4;
  fVar5 = fVar5 - fVar4;
  param_3[0xe] = fVar5;
  fVar1 = (fVar1 - DAT_0056876c) - DAT_0056876c;
  fVar2 = (fVar6 - DAT_00568778) - DAT_00568778;
  fVar5 = fVar3 - fVar5;
  param_3[0xf] = fVar5;
  fVar1 = fVar1 - fVar5;
  param_3[0x10] = fVar1;
  param_3[0x11] = (fVar2 - fVar3) - fVar1;
  return;
}

