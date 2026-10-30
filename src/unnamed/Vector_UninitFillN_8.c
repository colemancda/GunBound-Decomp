/* Vector_UninitFillN_8 - 0x00504190 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the uninitialised-fill member of the 8-byte
 * {CStringA, CStringA} pair vector - copy-construct n copies of the
 * value pair into raw storage, with the EH state ladder (0/1/2 per
 * member) that unwinds partially-constructed elements, exactly the
 * Vector_UninitFillN_34 / _1e shape at stride 8; it sits between those
 * two in the binary (0x504160 / 0x504270). Serves the same slot in
 * Vector_InsertN_8's realloc and append arms that the _34 member
 * serves in Vector_InsertN_34's, plus the push-back wrapper
 * Vector_PushBack_8.
 *
 * FIXED (2026-10-30): each clone passes FUN_0043de10 its EAX source
 * header, the value's handle - 0x10 (`mov eax,[edi] / sub eax,0x10` at
 * 0x5041d5 and `mov eax,[edi+4] / sub eax,0x10` at 0x5041e8, with EDI =
 * the incoming ECX value pointer, param_1). The SEH-prologue artifact
 * (push -1 / push 0x537abd / mov fs:[0],esp at 0x504193-0x5041a1, the
 * try-state byte at [ebp-4]) is stripped; its catch block at 0x504206 is
 * not part of this decompile.
 */
#include "ghidra_types.h"


void __fastcall Vector_UninitFillN_8(undefined4 param_1,int param_2,int *param_3)

{
  int iVar1;

  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_3 != (int *)0x0) {
      /* 0x5041d5-0x5041da / 0x5041e8-0x5041ee: EAX = value handle - 0x10 */
      iVar1 = FUN_0043de10((int *)(*(int *)param_1 + -0x10));
      *param_3 = iVar1 + 0x10;
      iVar1 = FUN_0043de10((int *)(*(int *)(param_1 + 4) + -0x10));
      param_3[1] = iVar1 + 0x10;
    }
    param_3 = param_3 + 2;
  }
  return;
}
