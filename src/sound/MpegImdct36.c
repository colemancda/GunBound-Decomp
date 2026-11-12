/* MpegImdct36 - 0x0051b030 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section. (Previously FUN_0051b030.)
 *
 * Evidence for the name (all from outside the body):
 * Its only caller is the one-argument cdecl thunk MpegImdct36Thunk
 * (0x51c680), which MpegImdctViaKernels (0x517d40) calls once per 18-sample
 * subband block with a pointer into the granule's spectrum (stride 0x48
 * bytes = 18 floats per block); the caller then reads the 18 results back from
 * the same block in place (offsets 0x24 and 0x44 bytes) and multiplies them by
 * the 36-sample window rows at 0xf25b00 + block_type * 0x90. The constants
 * it reads are the 36-point set that InitMpegImdctKernelTables builds
 * (GetMpegImdctLongTables record 0x568800: its entry loads edi=0xf25900,
 * esi=0xf25960, ecx=0xf259a0, i.e. the 18, 9 and 36 entry tables of
 * 2cos((2k+1)pi/72), 2cos((2k+1)pi/36) and cos(i*j*pi/36)). The function
 * at 0x51b667 (MpegImdct) contains the same arithmetic inline over the same
 * three tables. The 12-sample short-block counterpart is MpegImdct12; the
 * 36 is the long block length.
 * OPEN ITEM (do not change yet): the asm loads eax=0x568738 and ebx=0x568798
 * as the bases of two scratch arrays and indexes across them, while this
 * port (and MpegImdct, MpegImdct12) keeps those cells as separate scalars
 * DAT_00568738.. DAT_005687b8. The scratch cells really are two contiguous
 * arrays; the port is not yet coalesced.
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

void __cdecl MpegImdct36(float *param_3)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar1 = DAT_00f25944 * param_3[0x11] + DAT_00f25900 * *param_3;
  fVar2 = (DAT_00f25900 * *param_3 - DAT_00f25944 * param_3[0x11]) * DAT_00f25960;
  fVar4 = DAT_00f25924 * param_3[9] + DAT_00f25920 * param_3[8];
  fVar3 = (DAT_00f25920 * param_3[8] - DAT_00f25924 * param_3[9]) * DAT_00f25980;
  DAT_00568738 = fVar1 + fVar4;
  DAT_0056874c = fVar1 - fVar4;
  DAT_00568798 = fVar3 + fVar2;
  DAT_005687ac = fVar2 - fVar3;
  fVar1 = DAT_00f25940 * param_3[0x10] + DAT_00f25904 * param_3[1];
  fVar2 = (DAT_00f25904 * param_3[1] - DAT_00f25940 * param_3[0x10]) * DAT_00f25964;
  fVar4 = DAT_00f25928 * param_3[10] + DAT_00f2591c * param_3[7];
  fVar3 = (DAT_00f2591c * param_3[7] - DAT_00f25928 * param_3[10]) * DAT_00f2597c;
  DAT_0056873c = fVar1 + fVar4;
  DAT_00568750 = fVar1 - fVar4;
  DAT_0056879c = fVar3 + fVar2;
  DAT_005687b0 = fVar2 - fVar3;
  fVar1 = DAT_00f2593c * param_3[0xf] + DAT_00f25908 * param_3[2];
  fVar2 = (DAT_00f25908 * param_3[2] - DAT_00f2593c * param_3[0xf]) * DAT_00f25968;
  fVar4 = DAT_00f2592c * param_3[0xb] + DAT_00f25918 * param_3[6];
  fVar3 = (DAT_00f25918 * param_3[6] - DAT_00f2592c * param_3[0xb]) * DAT_00f25978;
  DAT_00568740 = fVar1 + fVar4;
  DAT_00568754 = fVar1 - fVar4;
  DAT_005687a0 = fVar3 + fVar2;
  DAT_005687b4 = fVar2 - fVar3;
  fVar1 = DAT_00f25938 * param_3[0xe] + DAT_00f2590c * param_3[3];
  fVar2 = (DAT_00f2590c * param_3[3] - DAT_00f25938 * param_3[0xe]) * DAT_00f2596c;
  fVar4 = DAT_00f25930 * param_3[0xc] + DAT_00f25914 * param_3[5];
  fVar3 = (DAT_00f25914 * param_3[5] - DAT_00f25930 * param_3[0xc]) * DAT_00f25974;
  DAT_00568744 = fVar1 + fVar4;
  DAT_00568758 = fVar1 - fVar4;
  DAT_005687a4 = fVar3 + fVar2;
  DAT_005687b8 = fVar2 - fVar3;
  DAT_00568748 = DAT_00f25934 * param_3[0xd] + DAT_00f25910 * param_3[4];
  DAT_005687a8 = (DAT_00f25910 * param_3[4] - DAT_00f25934 * param_3[0xd]) * DAT_00f25970;
  fVar1 = (DAT_00568738 + DAT_0056873c + DAT_00568740 + DAT_00568744 + DAT_00568748) * _DAT_005687f8
  ;
  *param_3 = fVar1;
  fVar2 = (DAT_00568798 + DAT_0056879c + DAT_005687a0 + DAT_005687a4 + DAT_005687a8) * _DAT_005687f8
  ;
  fVar4 = DAT_00f259b0 * DAT_0056874c;
  fVar6 = DAT_00f259b4 * DAT_00568750;
  fVar5 = DAT_00f259b8 * DAT_00568754;
  fVar7 = DAT_00f259bc * DAT_00568758;
  fVar3 = (DAT_00f259bc * DAT_005687b8 +
          DAT_00f259b8 * DAT_005687b4 + DAT_00f259b4 * DAT_005687b0 + DAT_00f259b0 * DAT_005687ac) -
          fVar2;
  fVar2 = fVar2 - fVar1;
  param_3[1] = fVar2;
  fVar2 = (fVar7 + fVar5 + fVar6 + fVar4) - fVar2;
  param_3[2] = fVar2;
  fVar1 = (DAT_00f259cc * DAT_00568744 +
          DAT_00f259c8 * DAT_00568740 + DAT_00f259c4 * DAT_0056873c + DAT_00f259c0 * DAT_00568738) -
          DAT_00568748;
  fVar4 = ((DAT_00f259cc * DAT_005687a4 +
           DAT_00f259c8 * DAT_005687a0 + DAT_00f259c4 * DAT_0056879c + DAT_00f259c0 * DAT_00568798)
          - DAT_005687a8) - fVar3;
  fVar3 = fVar3 - fVar2;
  param_3[3] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[4] = fVar1;
  fVar2 = ((DAT_0056874c - DAT_00568754) - DAT_00568758) * DAT_00f259d0;
  fVar3 = ((DAT_005687ac - DAT_005687b4) - DAT_005687b8) * DAT_00f259d0 - fVar4;
  fVar4 = fVar4 - fVar1;
  param_3[5] = fVar4;
  fVar2 = fVar2 - fVar4;
  param_3[6] = fVar2;
  fVar1 = DAT_00f259ec * DAT_00568744 +
          DAT_00f259e8 * DAT_00568740 + DAT_00f259e4 * DAT_0056873c + DAT_00f259e0 * DAT_00568738 +
          DAT_00568748;
  fVar4 = (DAT_00f259ec * DAT_005687a4 +
           DAT_00f259e8 * DAT_005687a0 + DAT_00f259e4 * DAT_0056879c + DAT_00f259e0 * DAT_00568798 +
          DAT_005687a8) - fVar3;
  fVar3 = fVar3 - fVar2;
  param_3[7] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[8] = fVar1;
  fVar3 = DAT_00f259f0 * DAT_0056874c;
  fVar6 = DAT_00f259f4 * DAT_00568750;
  fVar5 = DAT_00f259f8 * DAT_00568754;
  fVar7 = DAT_00f259fc * DAT_00568758;
  fVar2 = (DAT_00f259fc * DAT_005687b8 +
          DAT_00f259f8 * DAT_005687b4 + DAT_00f259f4 * DAT_005687b0 + DAT_00f259f0 * DAT_005687ac) -
          fVar4;
  fVar4 = fVar4 - fVar1;
  param_3[9] = fVar4;
  fVar4 = (fVar7 + fVar5 + fVar6 + fVar3) - fVar4;
  param_3[10] = fVar4;
  fVar1 = ((DAT_00568738 + DAT_00568740 + DAT_00568744) * _DAT_005687f8 - DAT_0056873c) -
          DAT_00568748;
  fVar3 = (((DAT_00568798 + DAT_005687a0 + DAT_005687a4) * _DAT_005687f8 - DAT_0056879c) -
          DAT_005687a8) - fVar2;
  fVar2 = fVar2 - fVar4;
  param_3[0xb] = fVar2;
  fVar1 = fVar1 - fVar2;
  param_3[0xc] = fVar1;
  fVar2 = DAT_00f25a10 * DAT_0056874c;
  fVar6 = DAT_00f25a14 * DAT_00568750;
  fVar5 = DAT_00f25a18 * DAT_00568754;
  fVar7 = DAT_00f25a1c * DAT_00568758;
  fVar4 = (DAT_00f25a1c * DAT_005687b8 +
          DAT_00f25a18 * DAT_005687b4 + DAT_00f25a14 * DAT_005687b0 + DAT_00f25a10 * DAT_005687ac) -
          fVar3;
  fVar3 = fVar3 - fVar1;
  param_3[0xd] = fVar3;
  fVar3 = (fVar7 + fVar5 + fVar6 + fVar2) - fVar3;
  param_3[0xe] = fVar3;
  fVar1 = DAT_00f25a2c * DAT_00568744 +
          DAT_00f25a28 * DAT_00568740 + DAT_00f25a24 * DAT_0056873c + DAT_00f25a20 * DAT_00568738 +
          DAT_00568748;
  fVar2 = DAT_00f25a2c * DAT_005687a4 +
          DAT_00f25a28 * DAT_005687a0 + DAT_00f25a24 * DAT_0056879c + DAT_00f25a20 * DAT_00568798 +
          DAT_005687a8;
  fVar3 = fVar4 - fVar3;
  param_3[0xf] = fVar3;
  fVar1 = fVar1 - fVar3;
  param_3[0x10] = fVar1;
  param_3[0x11] = (fVar2 - fVar4) - fVar1;
  return;
}

