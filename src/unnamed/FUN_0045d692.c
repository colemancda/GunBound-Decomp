/* FUN_0045d692 - 0x0045d692 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARG FIX (2026-08-11): all 6 argless PeekChecksumStateUnderLock()
 * calls now pass their guarded-cell pointer, recovered from
 * tools/underlock_push_sites.json + per-site disasm (0x45d8e2/0x45d9f1/
 * 0x45da16/0x45da41/0x45da61/0x45da9e). The first passes the return of
 * the immediately preceding EncodeChecksumDeltaAdd (its `push eax` at
 * 0x45d8d9; the return was discarded, now captured in uVar4). The
 * broadcast-event block passes unaff_EDI cells: byte offsets 0x1a2c/
 * 0x62f8/0x90c/0x8984 (`lea` right before each push) plus 0xb30 for the
 * `push ebp` site - ebp was re-loaded with `lea ebp,[edi+0xb30]` at
 * 0x45d88d (NOT its entry value edi+0xd54 from 0x45d69f), with no other
 * ebp write before the call.
 */
#include "ghidra_types.h"


int FUN_0045d692(void)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint3 uVar5;
  uint3 extraout_var;
  uint3 extraout_var_00;
  uint3 extraout_var_01;
  uint3 extraout_var_02;
  int *unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  char cStack00000007;
  int in_stack_00000024;
  int in_stack_00000248;
  int in_stack_0000046c;
  undefined4 in_stack_00000ac4;
  int in_stack_00000ad4;
  int in_stack_00000ad8;
  
  EncodeChecksumDeltaDiv();
  EncodeChecksumPairDiff();
  FUN_0045f300();
  /* chained-return cell (2026-08-11): orig 0x45d6e2 `call 0x40a5f0; mov
   * ebx,eax` then 0x45d6fc `mov eax,ebx` - the Peek cell is DeltaAdd's
   * returned cell pointer, which this decompile discarded. (DeltaAdd's
   * own 3 dropped args are the helper-family sweep's scope, not this
   * site's.) */
  iVar3 = EncodeChecksumDeltaAdd();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState((void *)iVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cStack00000007 = in_stack_00000ad4 < iVar3;
  if (in_stack_00000024 != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound();
  }
  if (in_stack_0000046c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound();
  }
  uVar4 = 0;
  if (in_stack_00000248 != 0) {
    ScrambleChecksumGuardBytes();
    uVar4 = TreeLowerBound();
  }
  uVar5 = (uint3)((uint)uVar4 >> 8);
  if (cStack00000007 == '\0') {
    EncodeChecksumDeltaDiv();
    EncodeChecksumPairSum();
    FUN_0045f300();
    EncodeChecksumDeltaAdd();
    cVar1 = PacketChecksumLessThan();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    ScrubChecksumGuard();
    uVar5 = extraout_var;
    if (cVar1 == '\0') {
      EncodeChecksumPairDiff();
      EncodeChecksumPairDiff();
      FUN_0045f5d0();
      uVar4 = EncodeChecksumDeltaAdd();
      iVar3 = PeekChecksumStateUnderLock(uVar4);
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      ScrubChecksumGuard();
      uVar5 = extraout_var_00;
      if (iVar3 <= in_stack_00000ad8) {
        EncodeChecksumPairDiff();
        FUN_0045f5d0();
        EncodeChecksumDeltaAdd();
        cVar1 = PacketChecksumLessThan();
        ScrubChecksumGuard();
        ScrubChecksumGuard();
        uVar5 = extraout_var_01;
        if (cVar1 == '\0') {
          if (DAT_0079352a != '\0') {
            QueueBroadcastEvent();
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)unaff_EDI[2];
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            uVar2 = PeekChecksumStateUnderLock(unaff_EDI + 0x68b);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar2;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            uVar4 = PeekChecksumStateUnderLock(unaff_EDI + 0x18be);
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = PeekChecksumStateUnderLock(unaff_EDI + 0x243);
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = PeekChecksumStateUnderLock(unaff_EDI + 0x2cc);
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = (**(code **)(*unaff_EDI + 0x14))();
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = PeekChecksumStateUnderLock(unaff_EDI + 0x2261);
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = FUN_0045f300();
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            uVar4 = FUN_0045f5d0();
            *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar4;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
            BroadcastQueuedEvent();
            uVar5 = extraout_var_02;
          }
          iVar3 = CONCAT31(uVar5,1);
          goto LAB_0045dafa;
        }
      }
    }
  }
  iVar3 = (uint)uVar5 << 8;
LAB_0045dafa:
  *unaff_FS_OFFSET = in_stack_00000ac4;
  return iVar3;
}

