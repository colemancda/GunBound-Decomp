/* MultiplyMatrix4x4InPlace - 0x004f2240 in the original binary.
 *
 * Multiplies two 4x4 float matrices and writes the product back over the
 * left operand.
 *
 * NAMED 2026-08-27, together with MultiplyMatrix4x4ToScratch (0x004f1f50).
 * The two bodies are the same multiply term for term -- out[r*4+c] = sum
 * over k of lhs[r*4+k] * rhs[k*4+c], the row-major 4x4 concatenation, and
 * the same exact shortcut when the right operand's last column is
 * (0,0,0,1) -- with EBX standing in for the other's ECX.  The one
 * difference is the destination, and it is what the two names contrast:
 * the closing sixteen-float copy targets EBX itself, and there is no
 * return value, where 0x004f1f50 copies into the shared static DAT_005a9350
 * and returns it.
 *
 * The external evidence that these are matrices is written up in
 * MultiplyMatrix4x4ToScratch.c: four 0x40-byte matrix slots at +0xe0,
 * +0x120, +0x160 and +0x1a0 of one object, the 4x4 identity fill FUN_004e9cc0
 * and FUN_004f37b0 put in the +0xe0 slot, and the D3D-style left-handed
 * perspective projection FUN_004e9cc0 builds into DAT_005a9290.  Specific to
 * this half: tools/callsite_regs.py reports EBX UNIFORM = ebp at all four
 * sites, which the callers set to that +0xe0 slot, and EAX is the
 * immediately preceding 0x004f1f50 return, so the pair composes as
 * `node = node x scratch` and this call is the one that lands the result.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * The note that follows predates the naming and still uses the old Ghidra
 * symbols: FUN_004f1f50 is MultiplyMatrix4x4ToScratch and FUN_004f2240 is
 * MultiplyMatrix4x4InPlace.  It is reproduced unchanged.
 *
 * DROPPED REGISTERS RESOLVED 2026-08-27 and APPLIED 2026-08-31, once the
 * five matrix globals were given real 0x40 extents in globals_sized.c -
 * the split-struct blocker the note below describes no longer holds.
 * The operand analysis it records was applied verbatim: EBX and EAX are
 * the regEbx/regEax parameters (dest, then source), and every caller
 * passes MultiplyMatrix4x4ToScratch's return for regEax.
 * This and its twin FUN_004f1f50 are the same 4x4 matrix multiply: one
 * operand in ECX (FUN_004f1f50) or EBX (this), the other in EAX, sixteen
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
 * (Historical: passing the operands before the sizing would have turned
 * "reads an uninitialised matrix" into "reads and writes 0x3c bytes past
 * four-byte globals". The sizing landed first, in the same change.)
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void MultiplyMatrix4x4InPlace(float *regEbx,float *regEax)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
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
  
  local_40[0] = regEbx[3] * regEax[0xc] +
                *regEax * *regEbx + regEax[4] * regEbx[1] + regEax[8] * regEbx[2];
  local_40[1] = regEax[1] * *regEbx +
                regEax[9] * regEbx[2] + regEax[5] * regEbx[1] + regEax[0xd] * regEbx[3];
  local_40[2] = regEax[10] * regEbx[2] +
                regEax[6] * regEbx[1] + regEbx[3] * regEax[0xe] + regEax[2] * *regEbx;
  local_30 = regEax[8] * regEbx[6] +
             regEbx[7] * regEax[0xc] + regEbx[4] * *regEax + regEax[4] * regEbx[5];
  local_2c = regEax[1] * regEbx[4] +
             regEbx[6] * regEax[9] + regEbx[7] * regEax[0xd] + regEax[5] * regEbx[5];
  local_28 = regEax[2] * regEbx[4] +
             regEax[6] * regEbx[5] + regEbx[6] * regEax[10] + regEbx[7] * regEax[0xe];
  local_20 = regEbx[8] * *regEax +
             regEax[0xc] * regEbx[0xb] + regEax[4] * regEbx[9] + regEax[8] * regEbx[10];
  local_1c = regEax[5] * regEbx[9] +
             regEax[9] * regEbx[10] + regEax[0xd] * regEbx[0xb] + regEax[1] * regEbx[8];
  local_18 = regEax[10] * regEbx[10] +
             regEax[0xe] * regEbx[0xb] + regEbx[8] * regEax[2] + regEax[6] * regEbx[9];
  local_10 = regEbx[0xc] * *regEax +
             regEbx[0xf] * regEax[0xc] + regEax[8] * regEbx[0xe] + regEax[4] * regEbx[0xd];
  local_c = regEbx[0xc] * regEax[1] +
            regEbx[0xd] * regEax[5] + regEbx[0xe] * regEax[9] + regEax[0xd] * regEbx[0xf];
  local_8 = regEbx[0xd] * regEax[6] +
            regEbx[0xe] * regEax[10] + regEbx[0xf] * regEax[0xe] + regEbx[0xc] * regEax[2];
  if (ABS(regEax[0xb]) < _DAT_0054c870) {
    if (ABS(regEax[0xf] - _DAT_00557fb0) < _DAT_0054c870) {
      if (ABS(regEax[3]) < _DAT_0054c870) {
        cVar1 = FUN_004e9490(regEax[7]);
        if (cVar1 != '\0') {
          local_40[3] = regEbx[3];
          local_24 = regEbx[7];
          local_4 = regEbx[0xf];
          local_14 = regEbx[0xb];
          pfVar3 = local_40;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *regEbx = *pfVar3;
            pfVar3 = pfVar3 + 1;
            regEbx = regEbx + 1;
          }
          return;
        }
      }
    }
  }
  local_40[3] = regEax[3] * *regEbx +
                regEax[7] * regEbx[1] + regEbx[3] * regEax[0xf] + regEax[0xb] * regEbx[2];
  local_24 = regEax[3] * regEbx[4] +
             regEax[7] * regEbx[5] + regEbx[6] * regEax[0xb] + regEbx[7] * regEax[0xf];
  local_14 = regEax[0xf] * regEbx[0xb] +
             regEax[0xb] * regEbx[10] + regEax[3] * regEbx[8] + regEax[7] * regEbx[9];
  local_4 = regEbx[0xd] * regEax[7] +
            regEax[0xb] * regEbx[0xe] + regEbx[0xc] * regEax[3] + regEbx[0xf] * regEax[0xf]
  ;
  pfVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *regEbx = *pfVar3;
    pfVar3 = pfVar3 + 1;
    regEbx = regEbx + 1;
  }
  return;
}

