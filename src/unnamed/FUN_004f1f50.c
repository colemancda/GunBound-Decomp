/* FUN_004f1f50 - 0x004f1f50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS RESOLVED BUT DELIBERATELY NOT APPLIED (2026-08-27).
 * This and its twin FUN_004f2240 are the same 4x4 matrix multiply: one
 * operand in ECX (this) or EBX (FUN_004f2240), the other in EAX, sixteen
 * floats each.  Every operand is settled --
 *
 *   FUN_004f1f50: ECX is `lea ecx,[esi + 0x1a0]` = param_1 + 0x68 at four
 *     sites and `lea ecx,[ebx + 0xe0]` / `[ebx + 0x120]` at FUN_004f38a0's
 *     two; EAX is `[esi+0xd0] + 0xe0` on the non-zero arms and the literals
 *     0x5a9130 / 0x5a93f0 / 0x5a9250 / 0x5a9290 elsewhere (the zero arms
 *     load the constant into EDX for FUN_004f3440, which only ever reads
 *     EDX, so the `mov eax,edx` after that call reloads the same value).
 *   FUN_004f2240: EBX is `param_1 + 0x38` at all four sites -- the local the
 *     callers already name piVar1 / piVar3 -- and EAX is FUN_004f1f50's
 *     return, which is unconditionally &DAT_005a9350.
 *
 * What blocks it is the globals, not the analysis.  Those five matrices are
 * modelled as SPLIT STRUCTS in globals.c, the same divergence FUN_004ee120
 * documents: each is 0x40 bytes in the original but only its first dword is
 * declared, with other fields broken out as separate scalars beside it.
 * DAT_005a9290 is the clearest case -- sizing it to 0x40 would swallow the
 * separately declared DAT_005a92a4, DAT_005a92b8, DAT_005a92bc and
 * DAT_005a92c8, which sit at +0x14, +0x28, +0x2c and +0x38 inside it.
 * DAT_005a9130, DAT_005a93f0 and DAT_005a9250 are not declared at all.
 *
 * So passing the operands would turn "reads an uninitialised matrix" into
 * "reads and writes 0x3c bytes past four-byte globals", which is the harder
 * failure to find, not the easier one.  The write side already overruns
 * DAT_005a9350 today, unconditionally and independently of these arguments.
 * Coalescing the matrix globals is the prerequisite; it is the same
 * split-struct job FUN_004ee120 is waiting on.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * __fastcall FUN_004f1f50(float *param_1)

{
  char cVar1;
  float *in_EAX;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float local_40 [4];
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  local_40[0] = param_1[3] * in_EAX[0xc] +
                *in_EAX * *param_1 + in_EAX[4] * param_1[1] + in_EAX[8] * param_1[2];
  local_40[1] = in_EAX[1] * *param_1 +
                in_EAX[9] * param_1[2] + in_EAX[5] * param_1[1] + in_EAX[0xd] * param_1[3];
  local_40[2] = in_EAX[10] * param_1[2] +
                in_EAX[6] * param_1[1] + param_1[3] * in_EAX[0xe] + in_EAX[2] * *param_1;
  local_30 = in_EAX[8] * param_1[6] +
             param_1[7] * in_EAX[0xc] + param_1[4] * *in_EAX + in_EAX[4] * param_1[5];
  local_2c = in_EAX[1] * param_1[4] +
             param_1[6] * in_EAX[9] + param_1[7] * in_EAX[0xd] + in_EAX[5] * param_1[5];
  local_28 = in_EAX[2] * param_1[4] +
             in_EAX[6] * param_1[5] + param_1[6] * in_EAX[10] + param_1[7] * in_EAX[0xe];
  local_20 = param_1[8] * *in_EAX +
             in_EAX[0xc] * param_1[0xb] + in_EAX[4] * param_1[9] + in_EAX[8] * param_1[10];
  local_1c = in_EAX[5] * param_1[9] +
             in_EAX[9] * param_1[10] + in_EAX[0xd] * param_1[0xb] + in_EAX[1] * param_1[8];
  local_18 = in_EAX[10] * param_1[10] +
             in_EAX[0xe] * param_1[0xb] + param_1[8] * in_EAX[2] + in_EAX[6] * param_1[9];
  local_10 = param_1[0xc] * *in_EAX +
             param_1[0xf] * in_EAX[0xc] + in_EAX[8] * param_1[0xe] + in_EAX[4] * param_1[0xd];
  local_c = param_1[0xc] * in_EAX[1] +
            param_1[0xd] * in_EAX[5] + param_1[0xe] * in_EAX[9] + in_EAX[0xd] * param_1[0xf];
  local_8 = param_1[0xd] * in_EAX[6] +
            param_1[0xe] * in_EAX[10] + param_1[0xf] * in_EAX[0xe] + param_1[0xc] * in_EAX[2];
  if (ABS(in_EAX[0xb]) < _DAT_0054c870) {
    if (ABS(in_EAX[0xf] - _DAT_00557fb0) < _DAT_0054c870) {
      if (ABS(in_EAX[3]) < _DAT_0054c870) {
        cVar1 = FUN_004e9490(in_EAX[7]);
        if (cVar1 != '\0') {
          local_40[3] = param_1[3];
          local_24 = param_1[7];
          local_14 = param_1[0xb];
          local_4 = param_1[0xf];
          goto LAB_004f221b;
        }
      }
    }
  }
  local_40[3] = in_EAX[3] * *param_1 +
                in_EAX[7] * param_1[1] + param_1[3] * in_EAX[0xf] + in_EAX[0xb] * param_1[2];
  local_24 = in_EAX[3] * param_1[4] +
             in_EAX[7] * param_1[5] + param_1[6] * in_EAX[0xb] + param_1[7] * in_EAX[0xf];
  local_14 = in_EAX[0xf] * param_1[0xb] +
             in_EAX[0xb] * param_1[10] + in_EAX[3] * param_1[8] + in_EAX[7] * param_1[9];
  local_4 = param_1[0xd] * in_EAX[7] +
            in_EAX[0xb] * param_1[0xe] + param_1[0xc] * in_EAX[3] + param_1[0xf] * in_EAX[0xf];
LAB_004f221b:
  pfVar3 = local_40;
  pfVar4 = (float *)&DAT_005a9350;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  return &DAT_005a9350;
}

