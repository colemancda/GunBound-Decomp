/* ChangePlayerMobile - 0x004d0fd0 in the original binary.
 *
 * RENAMED (2026-08-13, from FUN_004d0fd0). The mobile-change handler:
 * sole caller is State11_InBattle_ProcessBattleAction's `case 0xf009`,
 * passing (slot, newTypeByte) from the packet.  It unlinks the old
 * player record from its list, calls CreateMobile with the new type and
 * the old record's position/state fields, re-resolves the record and -
 * when the slot equals the current-slot cell at g_clientContext+0x3b49c
 * - re-points the local-player record at g_clientContext+0x621e0.  The
 * guarded-state migration that follows (see the DROPPED-CELL note
 * below) copies old-record cells into the new record at the same
 * offsets.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 8 argless PeekPacketChecksumState() calls (8 C : 8 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x4d0fd0-0x4d1430.
 *
 * The function migrates a player's guarded state from the OLD record
 * (iVar1, the first GetPlayerRecordBySlot return) into the NEW one
 * (iVar4, the second): each Peek reads iVar1+N and the Encode beside it
 * writes iVar4+N at the SAME offset (0x8bc4 / 0x1c54 / 0xc080) - the
 * two-object-copier shape, where mixing the bases up would not look
 * wrong.  The plain-copy block below the guard sites does the same for
 * a dozen unguarded fields, corroborating the direction.
 *
 * One cell is PATH-DEPENDENT and was folded away entirely by Ghidra:
 * at 0x4d128c the source for the +0x853c copy is chosen by
 * CompareChecksumPair(iVar4+0x8318, iVar1+0x853c) - taken branch reads
 * iVar4+0x8318, fall-through reads iVar1+0x853c - but the C discarded
 * the compare's result.  Now captured (cVar6) and the cell written as
 * the ternary the disasm actually implements.  One more cell is the
 * chained return of FUN_0040aea0 (captured in uVar7), and the
 * +0x3b49c read is the current-slot index cell spilled one push deep
 * at 0x4d10e6.
 */
#include "ghidra_types.h"


void ChangePlayerMobile(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  char cVar6;
  undefined4 uVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_8a4 [8];
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [548];
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  iVar1 = g_clientContext;
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053dfcc;
  *unaff_FS_OFFSET = &local_c;
  iVar1 = GetPlayerRecordBySlot(iVar1);
  if (iVar1 != 0) {
    *(undefined4 *)(*(int *)(iVar1 + 0xc) + 0x10) = *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(*(int *)(iVar1 + 0x10) + 0xc) = *(undefined4 *)(iVar1 + 0xc);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(iVar1 + 0xb30));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(iVar1 + 0x90c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    CreateMobile((uint)param_1,param_2,uVar3,uVar2,*(undefined4 *)(iVar1 + 0xae2c),
                 *(undefined4 *)(iVar1 + 0xae38),*(undefined4 *)(iVar1 + 0xae3c),iVar1 + 0xae15,
                 iVar1 + 0xae22,*(undefined4 *)(iVar1 + 0xae30),*(undefined4 *)(iVar1 + 0xae34),1);
    iVar4 = GetPlayerRecordBySlot(g_clientContext);
    if (iVar4 != 0) {
      *(int *)(g_clientContext + 0x621e4) = iVar4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar5 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (param_1 == uVar5) {
        *(int *)(g_clientContext + 0x621e0) = iVar4;
      }
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      RescrambleGuardedBool();
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4d123e (`lea edi,[ebx+0x8bc4]` at 0x4d122a, ebx = this file's
       * own iVar4 per `mov ebx,eax` right after the second
       * GetPlayerRecordBySlot call above) the cell is iVar4+0x8bc4. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(iVar1 + 0x8bc4));
      EncodeOutgoingPacketField(iVar4 + 0x8bc4, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4d1267 (`lea edi,[ebx+0x1c54]` at 0x4d1253) the cell is
       * iVar4+0x1c54. See tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(iVar1 + 0x1c54));
      EncodeOutgoingPacketField(iVar4 + 0x1c54, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar6 = CompareChecksumPair(iVar4 + 0x8318,iVar1 + 0x853c);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4d12b5 (`lea edi,[ebx+0x853c]` at 0x4d12a3, AFTER the
       * CompareChecksumPair call above reuses ebx/edi for its own
       * ternary - the final `lea edi,[ebx+0x853c]` right before this
       * call is what feeds it) the cell is iVar4+0x853c. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(cVar6 != 0 ? iVar4 + 0x8318 : iVar1 + 0x853c));
      EncodeOutgoingPacketField(iVar4 + 0x853c, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      RescrambleGuardedBool();
      *(undefined2 *)(iVar4 + 0xbfbc) = *(undefined2 *)(iVar1 + 0xbfbc);
      *(undefined1 *)(iVar4 + 0xae68) = *(undefined1 *)(iVar1 + 0xae68);
      *(undefined4 *)(iVar4 + 0xb094) = *(undefined4 *)(iVar1 + 0xb094);
      *(undefined4 *)(iVar4 + 0xb098) = *(undefined4 *)(iVar1 + 0xb098);
      *(undefined4 *)(iVar4 + 0xb09c) = *(undefined4 *)(iVar1 + 0xb09c);
      *(undefined4 *)(iVar4 + 0xb0a0) = *(undefined4 *)(iVar1 + 0xb0a0);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4d1339 (`lea edi,[ebx+0xc080]` at 0x4d1325) the cell is
       * iVar4+0xc080. See tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(iVar1 + 0xc080));
      EncodeOutgoingPacketField(iVar4 + 0xc080, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined4 *)(iVar1 + 0xbfe4) = 200;
      *(undefined4 *)(iVar4 + 0xbfe0) = 200;
      uVar2 = EncodeChecksumPairSum(iVar1 + 0x6744,local_230,iVar1 + 0x6db0);
      local_4 = 0;
      uVar3 = EncodeChecksumPairSum(iVar1 + 0x6968,local_678,iVar1 + 0x6fd4);
      SUBFIELD(local_4,0,undefined1) = 1;
      uVar3 = InitGuardedChecksumSlot(iVar4 + 0x6744,local_454,uVar3);
      SUBFIELD(local_4,0,undefined1) = 2;
      uVar7 = FUN_0040aea0(uVar3,local_89c,uVar2);
      SUBFIELD(local_4,0,undefined1) = 3;
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4d13ef (`mov edi,ebx`, ebx was bumped from iVar4 to
       * iVar4+0x6968 via `add ebx,0x6968` at 0x4d13dd, right after the
       * FUN_0040aea0 call above) the cell is iVar4+0x6968 - not
       * expressed as a named variable in the existing C, so written
       * directly. See tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)uVar7);
      EncodeOutgoingPacketField(iVar4 + 0x6968, uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      SUBFIELD(local_4,0,undefined1) = 2;
      if (local_888 != 0) {
        ScrambleChecksumGuardBytes(local_888,&g_valueGuardKeyTable);
        TreeLowerBound(local_8a4,&g_valueGuardMap);
      }
      SUBFIELD(local_4,0,undefined1) = 1;
      if (local_440 != 0) {
        ScrambleChecksumGuardBytes(local_440,&g_valueGuardKeyTable);
        TreeLowerBound(local_8a4,&g_valueGuardMap);
      }
      local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
      if ((*(int *)(local_678 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_678 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_8a4,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if ((*(int *)(local_230 + 0x14)) != 0) {
        ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&g_valueGuardKeyTable);
        TreeLowerBound(local_8a4,&g_valueGuardMap);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

