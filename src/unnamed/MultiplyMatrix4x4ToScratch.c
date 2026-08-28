/* MultiplyMatrix4x4ToScratch - 0x004f1f50 in the original binary.
 *
 * Multiplies two 4x4 float matrices and leaves the product in one shared
 * static scratch matrix, DAT_005a9350, which it also returns.
 *
 * NAMED 2026-08-27, together with its in-place twin MultiplyMatrix4x4InPlace
 * (0x004f2240).  The arithmetic here is an algebraic identity rather than a
 * restatement of control flow -- out[r*4+c] = sum over k of lhs[r*4+k] *
 * rhs[k*4+c], the row-major 4x4 concatenation, with an exact shortcut when
 * the right operand's last column is (0,0,0,1) and the product's last column
 * is therefore the left operand's unchanged -- but what settles that the
 * operands really are matrices is outside the body:
 *
 *   - FUN_004f38a0 copies this function's sixteen-dword return straight into
 *     `param_1 + 0x120` and `param_1 + 0x160`, and takes its own ECX operand
 *     from `param_1 + 0xe0` and `param_1 + 0x120`.  Those, with the
 *     `param_1 + 0x1a0` the other callers pass, are four 0x40-byte matrix
 *     slots in one object.
 *   - FUN_004e9cc0 and FUN_004f37b0 fill the +0xe0 slot with a 4x4 IDENTITY
 *     when the node has no source transform: a sixteen-dword zero fill, then
 *     0x3f800000 (1.0f) written at int indices 0, 5, 10 and 15 -- the
 *     diagonal, and nothing else.
 *   - FUN_004e9cc0 builds one of the EAX operands, DAT_005a9290, as a
 *     D3D-style left-handed perspective projection: a sixteen-dword zero
 *     fill, then m00 = cot(fov) * the aspect term, m11 = cot(fov),
 *     m22 = zf / (zf - zn) at +0x28, m23 = 1.0 at +0x2c and
 *     m32 = -zn * zf / (zf - zn) at +0x38.  That is a matrix by construction.
 *
 * The name says ToScratch because the destination is a single fixed global
 * shared by every call, not caller-owned storage: FUN_004f38a0 copies it out
 * immediately, and FUN_004e9cc0 / FUN_004f37b0 hand it straight to
 * MultiplyMatrix4x4InPlace as that call's EAX operand, so the pair composes
 * as `node = node x scratch`.  No library identity backs the name -- the
 * binary carries no engine or source-path strings to match against.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * The note that follows predates the naming and still uses the old Ghidra
 * symbols: FUN_004f1f50 is MultiplyMatrix4x4ToScratch and FUN_004f2240 is
 * MultiplyMatrix4x4InPlace.  It is reproduced unchanged.
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

undefined4 * __fastcall MultiplyMatrix4x4ToScratch(float *param_1)

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

