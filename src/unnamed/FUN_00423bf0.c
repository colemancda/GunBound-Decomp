/* FUN_00423bf0 - 0x00423bf0 in the original binary.
 *
 * The avatar part-table counter: opens each per-gender/category part
 * table in avatar.xfs ({f,m}{b,h,g}.dat + mf.dat), reads its leading u32
 * part count, and encodes each count into the per-category CValueGuard
 * count-cell array at ctx+0x5f3774 (stride 0x224, 8 elements - the cells
 * the avatar-store catalog loader FUN_00449540 Peeks as its loop bounds).
 * Called from State07_AvatarStore_OnEnter (orig 0x447c6e).
 *
 * DROPPED-ARGUMENT FIX (2026-07-29): all OpenXFSEntryStream(0) calls were
 * stale pre-migration calls; the entry names are literal string addresses
 * read from the original .data section.
 *
 * CELL-BASE + SIGNATURE + MISSING-BLOCK FIX (2026-08-11), superseding the
 * 2026-07-15 cell note that resolved the encode targets as the absolute
 * global &DAT_005f3774 ("ebx resolves to 0"): EBX does NOT resolve to 0 -
 * it is this function's own inbound parameter. The sole call site loads
 * `mov ebx,[0x5b3484]` (g_clientContext) before `call 0x423bf0`, entry
 * does `lea esi,[ebx+0xf6e8]` (the avatar archive), and EBX is never
 * written inside the function (verified 0x423bf0-0x423e15), so every
 * `lea edi/eax,[ebx+0x5f3xxx]` cell is CTX-RELATIVE - matching the
 * reader side (FUN_00449540 Peeks ctx+cat*0x224+0x5f3774/+0x5f4004).
 * Signature changed from (archiveBase) to (ctx) to match the original's
 * actual inbound register; the archive is derived inside as ctx+0xf6e8.
 * Also recovered here:
 *   - the four QueueOutgoingPacketField cells (0x40a470 takes its cell
 *     in EAX; the port's 1-arg calls had dropped it): fg->ctx+0x5f3bbc
 *     (elem 2), mb->ctx+0x5f4004 (elem 4), mh->ctx+0x5f4228 (elem 5),
 *     mg->ctx+0x5f444c (elem 6), per `lea eax,[ebx+...]` at
 *     0x423cd7/0x423d3d/0x423d7a/0x423db7;
 *   - the ReadXFSEntryByte counts (`mov eax,4` before every 0x4f06c0);
 *   - an ENTIRE MISSING BLOCK: the original opens a 7th table "mf.dat"
 *     (0x552c84, the male flag table) at 0x423dcd-0x423e15 and encodes
 *     its count into ctx+0x5f4670 (elem 7); the raw decompile dropped
 *     the whole block and returned after mg.dat.
 * Elements 0 (fb, 0x5f3774), 1 (fh, 0x5f3998) and 3 (0x5f3de0, encoded
 * with the constant 0 - the female flag slot, fb/fh/fg share mf's flags)
 * go through the open-coded lock+EncodeOutgoingPacketField form, exactly
 * as the original open-codes those three (0x423c3a/0x423c91/0x423cfe). */
#include "ghidra_types.h"


undefined4 FUN_00423bf0(int ctx)

{
  int archiveBase;
  undefined4 uVar1;
  int iVar2;
  undefined4 local_4;

  archiveBase = ctx + 0xf6e8;
  iVar2 = OpenXFSEntryStream(archiveBase, "fb.dat", 1, 0);
  if (iVar2 != 0) {
    ReadXFSEntryByte(iVar2,&local_4,4);
    uVar1 = local_4;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(ctx + 0x5f3774), uVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    CloseSpriteReadState();
    iVar2 = OpenXFSEntryStream(archiveBase, "fh.dat", 1, 0);
    if (iVar2 != 0) {
      ReadXFSEntryByte(iVar2,&local_4,4);
      uVar1 = local_4;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(ctx + 0x5f3998), uVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      CloseSpriteReadState();
      iVar2 = OpenXFSEntryStream(archiveBase, "fg.dat", 1, 0);
      if (iVar2 != 0) {
        ReadXFSEntryByte(iVar2,&local_4,4);
        QueueOutgoingPacketField((void *)(ctx + 0x5f3bbc), local_4);
        CloseSpriteReadState();
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        EncodeOutgoingPacketField((void *)(ctx + 0x5f3de0), 0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
        iVar2 = OpenXFSEntryStream(archiveBase, "mb.dat", 1, 0);
        if (iVar2 != 0) {
          ReadXFSEntryByte(iVar2,&local_4,4);
          QueueOutgoingPacketField((void *)(ctx + 0x5f4004), local_4);
          CloseSpriteReadState();
          iVar2 = OpenXFSEntryStream(archiveBase, "mh.dat", 1, 0);
          if (iVar2 != 0) {
            ReadXFSEntryByte(iVar2,&local_4,4);
            QueueOutgoingPacketField((void *)(ctx + 0x5f4228), local_4);
            CloseSpriteReadState();
            iVar2 = OpenXFSEntryStream(archiveBase, "mg.dat", 1, 0);
            if (iVar2 != 0) {
              ReadXFSEntryByte(iVar2,&local_4,4);
              QueueOutgoingPacketField((void *)(ctx + 0x5f444c), local_4);
              CloseSpriteReadState();
              /* the block the raw decompile dropped - see header */
              iVar2 = OpenXFSEntryStream(archiveBase, "mf.dat", 1, 0);
              if (iVar2 != 0) {
                ReadXFSEntryByte(iVar2,&local_4,4);
                QueueOutgoingPacketField((void *)(ctx + 0x5f4670), local_4);
                CloseSpriteReadState();
                return 1;
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
