/* CArray_Add_206 - 0x004e8f70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * The same CArray::Add shape as CArray_Add_1750 (reserve one more element
 * through the matching CArray_Grow_206, copy the caller's record into the
 * new slot, bump the count, return the index), just inlined as a raw copy
 * loop instead of a CArray_CopyElement_206 call and at the 0x206-byte
 * stride (0x81 dwords + 1 word) that this tree already names
 * CArray_Grow_206 - all 3 call sites below grow/index that same stride.
 *
 * DROPPED REGISTER ARGUMENT RECOVERED (2026-10-26).  The array object
 * arrived in EBX, which Ghidra modelled as `unaff_EBX`: the very first
 * instruction, 0x4e8f70 `mov eax,[ebx+8]`, reads EBX before anything in
 * this function writes it. All 3 call sites were disassembled: EBX is
 * `lea ebx,[ctx+0x454a4]` (ProcessUdpProbeDatagram, FUN_004e84c0's first
 * call) or `lea ebx,[ctx+0x454b4]` (FUN_004e84c0's second call) - two
 * distinct CArray headers hanging off the same probe context, both
 * promoted to a real parameter rather than guessed from one site.
 */
#include "ghidra_types.h"


uint CArray_Add_206(undefined4 *param_1,int *regEbx)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;

  uVar1 = regEbx[1];
  if ((uint)regEbx[2] <= uVar1) {
    cVar2 = CArray_Grow_206(uVar1 + 1,regEbx);
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  puVar4 = (undefined4 *)(uVar1 * 0x206 + *regEbx);
  if (puVar4 != (undefined4 *)0x0) {
    for (iVar3 = 0x81; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *param_1;
      param_1 = param_1 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined2 *)puVar4 = *(undefined2 *)param_1;
  }
  regEbx[1] = regEbx[1] + 1;
  return uVar1;
}

