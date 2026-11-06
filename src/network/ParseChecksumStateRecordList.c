/* ParseChecksumStateRecordList - 0x0043d780 in the original binary.
 *
 * NAMED (batch 36), LIKELY - structural. The inverse of
 * AppendChecksumStateRecordList (0x43d6d0): reads a count byte and then
 * that many 5-byte entries (u8, u16, u16) from the wire pointer on the
 * stack into the record array of the object in EAX (array +8, count +0xc,
 * capacity +0x10), freeing and emptying the previous array first. Each
 * entry is stored as the 6-byte element {u8, pad, u16, u16}, growing the
 * array through GrowChecksumStateArray (0x43d840, which sizes by 6) and
 * throwing E_OUTOFMEMORY (0x8007000e) if growth fails. It returns the
 * number of wire bytes consumed.
 *
 * Evidence for the object: all three callers are in
 * State11_InBattle_ProcessBattleAction and pass ctx+0x6a7f70 - the object
 * InsertChecksumStateRecord and the Append function use - with the wire
 * pointer `param_2 + 0x3d`, the end of the 0x8403 Fire payload documented in
 * src/cxx/Protocol.h (GbFirePayload: +0x3c is the last fixed field, "+0x3d:
 * trailing data"). Each call comes straight after the SetGuardedBool of the
 * +0x3c flag byte, the last fixed field.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int ParseChecksumStateRecordList(byte *param_1,int regEax)

{
  byte *pbVar1;
  undefined4 *puVar2;
  byte bVar3;
  undefined2 uVar4;
  uint uVar5;
  char cVar6;
  byte *pbVar7;
  int local_10;
  undefined4 local_8;
  
  bVar3 = *param_1;
  pbVar7 = param_1 + 1;
  if (*(void **)(regEax + 8) != (void *)0x0) {
    _free(*(void **)(regEax + 8));
    *(int *)(regEax + 8) = 0;
  }
  *(undefined4 *)(regEax + 0xc) = 0;
  *(undefined4 *)(regEax + 0x10) = 0;
  local_10 = 0;
  if (bVar3 != 0) {
    do {
      pbVar1 = pbVar7 + 1;
      uVar5 = *(uint *)(regEax + 0xc);
      uVar4 = *(undefined2 *)(pbVar7 + 3);
      local_8 = *pbVar7;
      pbVar7 = pbVar7 + 5;
      local_8 = CONCAT22(*(undefined2 *)pbVar1,(undefined2)local_8);
      if ((*(uint *)(regEax + 0x10) <= uVar5) && (cVar6 = GrowChecksumStateArray(uVar5 + 1,(int *)(regEax + 8)), cVar6 == '\0')) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
      puVar2 = (undefined4 *)(*(int *)(regEax + 8) + uVar5 * 6);
      if (puVar2 != (undefined4 *)0x0) {
        *puVar2 = local_8;
        *(undefined2 *)(puVar2 + 1) = uVar4;
      }
      local_10 = local_10 + 1;
      *(int *)(regEax + 0xc) = *(int *)(regEax + 0xc) + 1;
    } while (local_10 < (int)(uint)bVar3);
  }
  return (int)pbVar7 - (int)param_1;
}

