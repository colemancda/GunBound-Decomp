/* Vector_Erase_12 - 0x005027d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_005027d0).  VC7.1's one-element
 * vector<T>::erase(iterator _Where) for the 0x12-byte element:
 *   0x5027dd-0x5027e2  copy(_Where + 1, end(), _Where) via Vector_Copy_12
 *   0x5027e7           `add [esi+8],-0x12`, --_Mylast (no _Destroy call:
 *                      the element has no destructor)
 *   0x5027ee-0x5027f3  *sret = _Where, return sret, `ret 4`
 * ESI is the vector (_Mylast at +8, the layout the 0x12 family uses),
 * the one stack word is _Where and EBX the hidden return slot.
 *
 * Its one caller confirms the use: CommP2POwner_ProcessPacket's 0x3003
 * arm walks [this+0x17b0, this+0x17b4) - _Myfirst/_Mylast of the vector
 * at this+0x17ac, the one Vector_PushBack_12 appends to - in 0x12 steps,
 * compares each record's first 0x10 bytes with the packet's id
 * (__strnicmp),
 * and on a match calls this at 0x502278 with `lea esi,[edi+0x17ac]` and
 * the matching element pushed, then leaves the loop. Find-then-erase.
 *
 * CORRECTION to the 2026-08-25 note below: EBX does not report "the removed key";
 * it receives the returned iterator, i.e. _Where, which after the shift
 * points at the element that followed the erased one. The caller
 * discards it.
 *
 * EBX and ESI RECOVERED (2026-08-25) from the single site 0x502278 in
 * CommP2POwner_ProcessPacket: `lea ebx,[esp+0x1c]` with one push pending = frame -0x4978 =
 * &local_4978, and `lea esi,[edi+0x17ac]` where EDI is that function's
 * param_1.  So this erases one 0x12-byte entry from the vector at
 * param_1 + 0x17ac and reports the removed key through EBX.
 */
#include "ghidra_types.h"


void Vector_Erase_12(undefined4 param_1,undefined4 *regEbx,int regEsi)

{
  
  Vector_Copy_12((undefined4 *)((int)param_1 + 0x12),*(undefined4 **)(regEsi + 8),(undefined4 *)param_1);
  *(int *)(regEsi + 8) = *(int *)(regEsi + 8) + -0x12;
  *regEbx = param_1;
  return;
}

