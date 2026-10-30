/* Vector_UninitCopy_8 - 0x005045d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the uninitialised-copy member of the 8-byte
 * {CStringA, CStringA} pair vector - copy-construct [first, last) into
 * raw storage stepping 8, cloning both CString handles per element via
 * the 0x43de10 addref/clone, with the same EH state ladder as
 * Vector_UninitCopy_34 / _1e, between which it sits in the binary
 * (0x5045a0 / 0x5046b0). Vector_InsertN_8 calls it in all three of the
 * arms where Vector_InsertN_34 calls Vector_UninitCopy_34: realloc head
 * and tail, append-overlap tail, and the shift arm.
 *
 * FIXED (2026-10-30): each clone passes FUN_0043de10 its EAX source
 * header, the source handle - 0x10 (`mov eax,[edi] / sub eax,0x10` at
 * 0x504614 and `mov eax,[edi+4] / sub eax,0x10` at 0x504627, EDI being
 * the incoming ECX source iterator, param_1). The SEH-prologue artifact
 * (push -1 / push 0x537b7d / mov fs:[0],esp at 0x5045d3-0x5045e1, the
 * try-state byte at [ebp-4]) is stripped; its catch block at 0x504646,
 * which destroys the partly built range and rethrows, is not part of this
 * decompile, and the stray fs writes went through an uninitialised
 * pointer on every call.
 */
#include "ghidra_types.h"


int * __thiscall Vector_UninitCopy_8(int param_1,int param_2,int *param_3)

{
  int iVar1;

  for (; param_1 != param_2; param_1 = param_1 + 8) {
    if (param_3 != (int *)0x0) {
      /* 0x504614-0x504619 / 0x504627-0x50462d: EAX = source handle - 0x10 */
      iVar1 = FUN_0043de10((int *)(*(int *)param_1 + -0x10));
      *param_3 = iVar1 + 0x10;
      iVar1 = FUN_0043de10((int *)(*(int *)(param_1 + 4) + -0x10));
      param_3[1] = iVar1 + 0x10;
    }
    param_3 = param_3 + 2;
  }
  return param_3;
}
