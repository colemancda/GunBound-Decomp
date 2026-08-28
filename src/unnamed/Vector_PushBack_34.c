/* Vector_PushBack_34 - 0x00502800 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-25): `lea eax,[esp+0xa0]` at 0x5019e1 in
 * FUN_00501770, no push pending.  That caller's frame constant is -0x4990,
 * pinned by three independent slots (esp+0x18 -> local_4978, esp+0x38 ->
 * local_4958, esp+0xa0 -> local_48f0), so EAX is the address of local_48f0,
 * the 0x34-byte element being appended.  ECX (param_1) is the vector.
 *
 * NAMED (2026-08-28): std::vector<T>::push_back for the 0x34-byte
 * element, out of VC7.1's <vector>. The whole body is that member
 * verbatim - `if (size() < capacity()) { _Uninit_fill_n(_Last, 1, _X,
 * allocator); ++_Last; } else insert(end(), _X);` - and the disassembly
 * carries each half in the open:
 *
 *   0x502813-0x502845  the two (_Last - _First)/0x34 and
 *                      (_End - _First)/0x34 divisions and the `cmp/jae`
 *                      between them, i.e. size() against capacity()
 *   0x50284f-0x502856  `mov eax,1` / `mov ecx,esi` (esi = _Last) into
 *                      Vector_UninitFillN_34: fill ONE element at the end
 *   0x50285e           `add esi,0x34` / `mov [edi+8],esi`, i.e. ++_Last
 *   0x502869-0x50286d  the else arm, `push ebx; push [edi+8]` into
 *                      Vector_Insert_34 - insert(end(), _X)
 *
 * The container is the standard three-pointer vector: _First at +4, _Last
 * at +8, _End at +0xc, which is the layout Vector_Insert_34 and
 * Vector_InsertN_34 walk as well.
 */
#include "ghidra_types.h"


void __fastcall Vector_PushBack_34(int param_1,undefined4 regEax)

{
  int iVar1;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x34) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x34))) {
    iVar1 = *(int *)(param_1 + 8);
    /* DROPPED-REG FIX 2026-08-28: this call was mis-slotted, not just
       short. The original puts the vector's END pointer in ECX
       (`mov ecx,esi` with esi = *(param_1+8) at 0x502854) and pushes
       param_1 as the never-read stack word; the port had param_1 in ECX.
       Count = 1 (`mov eax,1` at 0x50284f); the element is EBX, captured
       from the incoming EAX by `mov ebx,eax` at 0x50280b. */
    Vector_UninitFillN_34(iVar1,0,param_1,1,(undefined4 *)regEax);
    *(int *)(param_1 + 8) = iVar1 + 0x34;
    return;
  }
  Vector_Insert_34(&local_4,*(undefined4 *)(param_1 + 8),regEax);
  return;
}

