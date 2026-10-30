/* Vector_CopyBackward_12 - 0x005042f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_005042f0).  _Copy_backward over
 * 0x12-byte elements: walk [EDX, ECX) downward, writing below EAX, so an
 * overlapping shift-up cannot clobber what it has yet to read - the 0x12
 * twin of Vector_CopyBackward_1e. Registers: EDX (param_2) the source
 * start and stop pointer, ECX (param_1) the source end, EAX (regEax) the
 * destination end; bare ret.
 *
 * Its one caller is FUN_00502b70, the 0x12 vector's _Insert_n, at
 * 0x502dea in the shift arm: right after Vector_UninitCopy_12 has
 * constructed the last n elements one stride-block up and stored the new
 * _Mylast, it calls this with EDX = _Where, ECX = old _Mylast - n*0x12
 * and EAX = the old _Mylast ([ebp+8], saved at 0x502d64) - VC7.1's
 * `copy_backward(_Where, _Oldend - _Count, _Oldend)`, the slot
 * Vector_CopyBackward_1e/_34 fill in their own _Insert_n. Assignment is
 * the plain 16+2-byte member copy Vector_FillN_12 also uses.
 */
#include "ghidra_types.h"


void __fastcall Vector_CopyBackward_12(undefined4 *param_1,undefined4 *param_2,undefined4 *regEax)

{
  
  while (param_2 != param_1) {
    *(undefined4 *)((int)regEax + -0x12) = *(undefined4 *)((int)param_1 + -0x12);
    *(undefined4 *)((int)regEax + -0xe) = *(undefined4 *)((int)param_1 + -0xe);
    *(undefined4 *)((int)regEax + -10) = *(undefined4 *)((int)param_1 + -10);
    *(undefined4 *)((int)regEax + -6) = *(undefined4 *)((int)param_1 + -6);
    *(undefined2 *)((int)regEax + -2) = *(undefined2 *)((int)param_1 + -2);
    param_1 = (undefined4 *)((int)param_1 + -0x12);
    regEax = (undefined4 *)((int)regEax + -0x12);
  }
  return;
}

