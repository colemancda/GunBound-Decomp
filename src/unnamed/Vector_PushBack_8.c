/* Vector_PushBack_8 - 0x00502890 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00502890).  std::vector<T>::push_back
 * for the 8-byte {CStringA, CStringA} pair vector, between
 * Vector_PushBack_34 (0x502800) and Vector_PushBack_1e (0x502920) in the
 * binary and the same member at stride 8:
 *   0x50289d-0x5028b3  size() vs capacity(), both `sar 3`, `cmp/jae`
 *   0x5028b5-0x5028ce  Vector_UninitFillN_8 of ONE element at _Mylast
 *                      (`mov edx,1`), then `add edi,8 / mov [esi+8],edi`
 *   0x5028d4-0x5028db  else Vector_InsertN_8(vector, _Mylast, 1) - the
 *                      insert(end(), _X) fallback, here with the
 *                      one-element insert inlined into a direct _Insert_n
 * The callees are the already-named members of the 8-byte family, which
 * Vector_InsertN_8's header calls this function's push-back wrapper.
 * The one caller, CommP2POwner_ProcessPacket at 0x501e22, builds the
 * element as two CString handles (local_4978 and the next dword, both
 * filled by AssignStringFromText just before) - the pair the family's
 * refcounted copy and fill handle.
 *
 * DROPPED ARGUMENTS (2026-10-30). Fixed: the Vector_UninitFillN_8 call
 * had the destination in the element slot and no count. That function
 * takes ECX = element (`mov edi,ecx` at 0x5041b4), EDX = count, stack =
 * destination ([ebp+8] at 0x5041ad); this function leaves its incoming
 * ECX untouched, pushes _Mylast (`push edi` at 0x5028bd) and sets
 * `mov edx,1` - so the call is (param_1, 1, _Mylast). NOT fixed: on the
 * fallback the element also stays in ECX for Vector_InsertN_8, which
 * copies it at entry (`mov edi,ecx` at 0x50315b into
 * Vector_CopyElement_8); ECX is not written on the path from entry to
 * the call at 0x5028db.  Vector_InsertN_8 now takes it as its trailing
 * regEcx (2026-10-30) and the fallback passes param_1.
 *
 * ESI RECOVERED (2026-08-25): `lea esi,[esp+0x38]` at 0x501e1e in
 * CommP2POwner_ProcessPacket = &local_4958 under that function's -0x4990 frame constant.
 * ESI is the vector; ECX (param_1) is the 8-byte element pushed onto it.
 */
#include "ghidra_types.h"


void __fastcall Vector_PushBack_8(undefined4 param_1,int regEsi)

{
  int iVar1;
  
  iVar1 = *(int *)(regEsi + 4);
  if ((iVar1 != 0) &&
     ((uint)(*(int *)(regEsi + 8) - iVar1 >> 3) < (uint)(*(int *)(regEsi + 0xc) - iVar1 >> 3))
     ) {
    iVar1 = *(int *)(regEsi + 8);
    Vector_UninitFillN_8(param_1,1,(int *)iVar1);
    *(int *)(regEsi + 8) = iVar1 + 8;
    return;
  }
  Vector_InsertN_8(regEsi,*(undefined4 *)(regEsi + 8),1,param_1);
  return;
}

