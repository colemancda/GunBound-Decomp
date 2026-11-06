/* AppendChecksumStateRecordList - 0x0043d6d0 in the original binary.
 *
 * NAMED (batch 36), LIKELY - structural. Serialises the record array of the
 * object at ctx+0x6a7f70 (EAX = that object; array at +8, count at +0xc)
 * onto the end of the broadcast event buffer: g_abBroadcastEventBuffer at
 * the cursor g_dwBroadcastEventCursor gets one count byte, then per record
 * a 5-byte entry: u8 at record +0, u16 at +2, u16 at +4. Each element read
 * is bounds-checked against the count and throws E_INVALIDARG
 * (0x80070057) on overrun, the ATL operator[] check.
 *
 * Why "ChecksumStateRecord" and not a fire-specific noun: the 6-byte
 * element {u8, pad, u16, u16} is exactly what InsertChecksumStateRecord
 * (0x43d5d0) stores into the same object (`this` = ctx+0x6a7f70, from
 * SyncOutgoingChecksumField) and what GrowChecksumStateArray sizes by 6, so
 * the tree already names this container's element. The wire inverse is
 * ParseChecksumStateRecordList (0x43d780).
 *
 * Callers all build a fire event: HandleFireInput (two sites, plus their
 * C++ twin in Mobile.cpp) and HandleMouseInput (the 0x8403 / 0xc400 event)
 * fill the event buffer field by field, call this last, then
 * BroadcastQueuedEvent. The same list therefore rides at the end of the
 * 0x8403 Fire payload (Protocol.h: +0x3d, trailing data) - that is the
 * only fire-related evidence; what the records mean is not established.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AppendChecksumStateRecordList(int regEax)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(regEax + 0xc);
  g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
  uVar3 = 0;
  if (*(int *)(regEax + 0xc) != 0) {
    iVar4 = 0;
    iVar2 = g_dwBroadcastEventCursor;
    if (*(int *)(regEax + 0xc) == 0) {
LAB_0043d766:
      g_dwBroadcastEventCursor = iVar2;
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = *(undefined1 *)(iVar4 + *(int *)(regEax + 8));
      iVar2 = g_dwBroadcastEventCursor + 1;
      if (*(uint *)(regEax + 0xc) <= uVar3) goto LAB_0043d766;
      puVar1 = (undefined2 *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      *puVar1 = *(undefined2 *)(iVar4 + 2 + *(int *)(regEax + 8));
      iVar2 = g_dwBroadcastEventCursor + 2;
      if (*(uint *)(regEax + 0xc) <= uVar3) goto LAB_0043d766;
      puVar1 = (undefined2 *)(&DAT_00e9aace + g_dwBroadcastEventCursor);
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      *puVar1 = *(undefined2 *)(*(int *)(regEax + 8) + 4 + iVar4);
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 6;
    } while (uVar3 < *(uint *)(regEax + 0xc));
  }
  return;
}

