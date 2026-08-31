/* FUN_004f3440 - 0x004f3440 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-31): the real live-ins are EDX (the target
 * matrix both callers preload - 0x5a9130 at 0x4e9d4d, 0x5a93f0 at
 * 0x4f3838 - and re-read after this returns) and ESI (the scene node).
 * The declared ECX param_1 was a FABRICATION: the entry `push ecx` at
 * 0x4f3440 only reserves the fstp scratch slot, and the incoming ECX is
 * dead - the FUN_004f3a60 operands are built here (`lea eax,[esi+0x1e0]`
 * / `lea ecx,[esi+0xa8]` at 0x4f3441/0x4f3447), not passed through.
 * param_1 stays as a placeholder so param_2 keeps the EDX slot under
 * real MSVC __fastcall; callers pass 0. Ghidra's param_2 after the
 * FUN_004f3a60 call was really the untouched incoming EDX. */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f3440(undefined4 param_1,float *param_2,int regEsi)

{
  float *pfVar1;
  
  pfVar1 = (float *)FUN_004f3a60((float *)(regEsi + 0xa8),(float *)(regEsi + 0x1e0));
  _DAT_005a93e0 = *pfVar1;
  _DAT_005a93e4 = pfVar1[1];
  _DAT_005a93e8 = pfVar1[2];
  _DAT_005a93ec = pfVar1[3];
  FUN_004f3ba0(param_2,(float *)DAT_005a93e0);
  param_2[0xc] = *(float *)(regEsi + 0x98);
  param_2[0xd] = *(float *)(regEsi + 0x9c);
  param_2[0xe] = *(float *)(regEsi + 0xa0);
  if (_DAT_0054c870 <= ABS(*(float *)(regEsi + 0xb8) - _DAT_00557fb0)) {
    *param_2 = *(float *)(regEsi + 0xb8) * *param_2;
    param_2[1] = param_2[1] * *(float *)(regEsi + 0xb8);
    param_2[2] = param_2[2] * *(float *)(regEsi + 0xb8);
    param_2[4] = param_2[4] * *(float *)(regEsi + 0xb8);
    param_2[5] = param_2[5] * *(float *)(regEsi + 0xb8);
    param_2[6] = param_2[6] * *(float *)(regEsi + 0xb8);
    param_2[8] = param_2[8] * *(float *)(regEsi + 0xb8);
    param_2[9] = param_2[9] * *(float *)(regEsi + 0xb8);
    param_2[10] = param_2[10] * *(float *)(regEsi + 0xb8);
  }
  return;
}

