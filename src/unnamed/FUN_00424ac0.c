/* FUN_00424ac0 - 0x00424ac0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00424ac0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_181c;
  int local_1810 [1536];
  undefined4 uStack_10;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped (local_c/
   * puStack_8/unaff_FS_OFFSET) - handler body (LAB_0053d8bb) wasn't
   * included in this function's own decompile. Same rationale as
   * entry/InitGame.c - see src/README.md. */
  uStack_10 = 0x424adf;
  FUN_00425350();
  local_4 = 0;
  FUN_00423e20(param_1,0);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x424b37..
   * 0x424c49 (`0x424b35: mov edi,esi` / `0x424b4e..0x424c0c: lea
   * edi,[esi+N]` / `0x424c32: add esi,0xefc` then `0x424c47: mov
   * edi,esi`). esi is loaded from `[esp+0x1838]` == param_3 (confirmed by
   * the State09_ReadyRoom_ProcessPacket.c caller, which passes
   * `index*0x1120 + base` as this arg - 0x1120 == 8*0x224 ==
   * 8*sizeof(CValueGuard)): param_3 is the base of an 8-element
   * CValueGuard cell array, walked cell-by-cell (0, 0x224, 0x448, 0x66c,
   * 0x890, 0xab4, 0xcd8, 0xefc) across these 8 calls. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3,uVar1); /* cell0 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x224,uVar1); /* cell1 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x448,uVar1); /* cell2 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x66c,uVar1); /* cell3 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x890,uVar1); /* cell4 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xab4,uVar1); /* cell5 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xcd8,uVar1); /* cell6 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xefc,uVar1); /* cell7 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00423e20(param_1,1);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x424c9b..
   * 0x424e18, same param_3 cell-array pattern as the block above (esi
   * reloaded from param_3 at 0x424c7a, then lea/add-walked through the
   * same 0/0x224/0x448/0x66c/0x890/0xab4/0xcd8/0xefc offsets). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3,iVar3 + iVar2); /* cell0 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x224,iVar3 + iVar2); /* cell1 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x448,iVar3 + iVar2); /* cell2 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x66c,iVar3 + iVar2); /* cell3 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x890,iVar3 + iVar2); /* cell4 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xab4,iVar3 + iVar2); /* cell5 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xcd8,iVar3 + iVar2); /* cell6 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xefc,iVar3 + iVar2); /* cell7 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00423e20(param_1,2);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x424ea1..
   * 0x424fe7, same param_3 cell-array pattern as the two blocks above
   * (esi reloaded from param_3 at 0x424e49, then lea/add-walked through
   * the same 0/0x224/0x448/0x66c/0x890/0xab4/0xcd8/0xefc offsets). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3,iVar3 + iVar2); /* cell0 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x224,iVar3 + iVar2); /* cell1 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x448,iVar3 + iVar2); /* cell2 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x66c,iVar3 + iVar2); /* cell3 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x890,iVar3 + iVar2); /* cell4 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xab4,iVar3 + iVar2); /* cell5 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xcd8,iVar3 + iVar2); /* cell6 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xefc,iVar3 + iVar2); /* cell7 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00423e20(param_1,3);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x425039..
   * 0x4251ba, same param_3 cell-array pattern as the blocks above (esi
   * reloaded from param_3 at 0x425018; this block's final cell7 write
   * uses a plain `lea edi,[esi+0xefc]` at 0x425196 rather than the
   * `add esi,0xefc` trick the earlier blocks use, but resolves to the
   * identical param_3+0xefc address). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3,iVar3 + iVar2); /* cell0 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x224,iVar3 + iVar2); /* cell1 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x448,iVar3 + iVar2); /* cell2 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x66c,iVar3 + iVar2); /* cell3 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0x890,iVar3 + iVar2); /* cell4 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xab4,iVar3 + iVar2); /* cell5 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xcd8,iVar3 + iVar2); /* cell6 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(param_3 + 0xefc,iVar3 + iVar2); /* cell7 */
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_1810[0] = 0x32;
  local_1810[1] = 0x32;
  local_1810[2] = 0x32;
  local_1810[3] = 0x32;
  local_1810[4] = 0x32;
  local_1810[5] = 0x32;
  local_1810[6] = 0x32;
  local_1810[7] = 0x32;
  local_181c = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = local_1810[local_181c];
    iVar3 = iVar2;
    if (iVar4 <= iVar2) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar4 = -iVar2;
    if (-iVar3 == iVar2 || -iVar2 < iVar3) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = iVar2;
      if (iVar3 <= iVar2) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
    }
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42529b
     * (`0x4251f3: mov edi,esi`, esi == param_3, resolved once for the
     * first loop iteration). Unlike the unrolled blocks above, this is a
     * REAL do-while loop (single static call address, executed 8x at
     * runtime): the disassembly shows `add edi,0x224` right after the
     * call, once per iteration, in lockstep with this same loop's
     * `local_181c = local_181c + 1` counter increment - so edi actually
     * walks the same param_3 8-cell array (cell0..cell7) one cell per
     * iteration, keyed by local_181c (used here BEFORE its increment).
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3 + local_181c * 0x224,iVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_181c = local_181c + 1;
  } while (local_181c < 8);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (((uVar5 & 0x10) == 0) && (param_4 == '\x01')) {
    iVar2 = 7;
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x425309
     * (`0x4252f3: mov edi,esi`, esi == param_3, resolved once for the
     * first loop iteration; note esi/edi get repurposed as a countdown
     * register pair right after - `mov esi,7` then `dec esi` - unrelated
     * to the param_3 cell walk). Same real-loop pattern as the loop
     * above: `add edi,0x224` runs once per iteration right after the
     * call, walking cell0..cell6 across these 7 iterations (iVar2 counts
     * DOWN from 7 to 1, so the cell index actually used each iteration,
     * BEFORE that iteration's `iVar2 = iVar2 + -1`, is `7 - iVar2`). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(param_3 + (7 - iVar2) * 0x224,0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  local_4 = 0xffffffff;
  FUN_004254a0();
  return;
}

