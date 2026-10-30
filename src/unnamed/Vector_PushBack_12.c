/* Vector_PushBack_12 - 0x00502750 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_00502750).  std::vector<T>::push_back
 * for the 0x12-byte element, instruction for instruction the twin of
 * Vector_PushBack_34 (0x502800, directly after it in the binary) with
 * the divide constant changed from 0x4ec4ec4f/sar 4 (/0x34) to
 * 0x38e38e39/sar 2 (/0x12):
 *   0x502763-0x502795  size() against capacity(), `cmp/jae`
 *   0x50279f-0x5027a6  Vector_UninitFillN_12 of ONE element at _Mylast
 *   0x5027ae-0x5027b1  `add esi,0x12 / mov [edi+8],esi`, ++_Mylast
 *   0x5027b9-0x5027c3  else insert(end(), _X) via Vector_Insert_12
 * ECX is the vector, EAX the element (captured `mov ebx,eax` at
 * 0x50275b).
 *
 * Both callers are in CommP2POwner_ProcessPacket and push onto the
 * vector at this+0x17ac (0x501a05 and 0x5020f3). The 0x501a05 element,
 * local_48f0, is first filled by CopyNameField_12 - the 18-byte counted
 * name record whose length byte at +0x11 the 0x12 helpers copy by.
 *
 * DROPPED REGISTERS (2026-10-30): the fast-path fill and the insert call
 * were passing one wrong value and a short list respectively; both now
 * carry what the disassembly loads (see the call-site comments). EDI
 * into Vector_Insert_12 is the same vector ECX brings in.
 */
#include "ghidra_types.h"


void __fastcall Vector_PushBack_12(int param_1,undefined4 regEax)

{
  int iVar1;
  int local_4;
  
  iVar1 = *(int *)(param_1 + 4);
  local_4 = param_1;
  if ((iVar1 != 0) &&
     ((uint)((*(int *)(param_1 + 8) - iVar1) / 0x12) <
      (uint)((*(int *)(param_1 + 0xc) - iVar1) / 0x12))) {
    iVar1 = *(int *)(param_1 + 8);
    /* Count 1 in ECX (`mov ecx,1` at 0x50279f), destination = the old
     * _Mylast in EAX (`mov eax,esi` at 0x5027a4), element in EBX, which
     * holds the incoming EAX (`mov ebx,eax` at 0x50275b); the pushed
     * word is local_4 and is never read.  The port passed only param_1. */
    Vector_UninitFillN_12(1,0,param_1,(undefined4 *)iVar1,(undefined4 *)regEax);
    *(int *)(param_1 + 8) = iVar1 + 0x12;
    return;
  }
  /* EDI = the vector (`mov edi,ecx` at 0x502754), read by insert at
   * 0x5029bb; EBX = the element, pushed third at 0x5027bc. */
  Vector_Insert_12(&local_4,*(int *)(param_1 + 8),(undefined4 *)regEax,param_1);
  return;
}

