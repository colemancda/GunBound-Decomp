/* FUN_00423bf0 - 0x00423bf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-07-29): all 6 OpenXFSEntryStream(0) calls were
 * stale pre-migration calls (see functions.h's "K&R-empty deliberately"
 * note) - Ghidra also dropped the function's own inbound EBX archive base.
 * Confirmed via objdump: entry `lea esi,[ebx+0xf6e8]` (0x423bf4) computes
 * the archive from an unaff_EBX the port never declared, and the sole call
 * site (State07_AvatarStore_OnEnter.c, orig 0x447c6e) loads
 * `mov ebx,[0x5b3484]` (= g_clientContext) immediately before `call
 * 0x423bf0` - so archive = g_clientContext + 0xf6e8 (a second, per-session
 * XFS archive distinct from g_graphicsArchive; likely avatar.xfs, given
 * orig/avatar.xfs and this function's 6 entry names below). Promoted to an
 * explicit parameter.
 *
 * The 6 entry names were literal string addresses (0x552cb4/ac/a4/9c/94/8c)
 * read directly from the original .data section: "fb.dat", "fh.dat",
 * "fg.dat", "mb.dat", "mh.dat", "mg.dat" (female/male body/head/gun avatar
 * part data), each opened with findExisting=1, insertFlag=0.
 */
#include "ghidra_types.h"


undefined4 FUN_00423bf0(int archiveBase)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_4;

  iVar2 = OpenXFSEntryStream(archiveBase, "fb.dat", 1, 0);
  if (iVar2 != 0) {
    ReadXFSEntryByte(iVar2,&local_4);
    uVar1 = local_4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x423c3a
     * (`lea edi,[ebx + 0x5f3774]`, ebx resolves to 0 here so the address
     * is the literal constant): this is exactly &DAT_005f3774, the base
     * of the global 8-element/0x224-stride ValueGuard array also seen in
     * FUN_00415d40.c/FUN_00418dc0.c's
     * `_eh_vector_constructor_iterator_(&DAT_005f3774+param_1,0x224,8,...)`.
     * See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField((int)&DAT_005f3774, uVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    CloseSpriteReadState();
    iVar2 = OpenXFSEntryStream(archiveBase, "fh.dat", 1, 0);
    if (iVar2 != 0) {
      ReadXFSEntryByte(iVar2,&local_4);
      uVar1 = local_4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x423c91 (`lea edi,[ebx + 0x5f3998]`, ebx=0): 0x5f3998 -
       * 0x5f3774 = 0x224, i.e. element #1 of the same DAT_005f3774
       * array (one stride further). See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField((int)&DAT_005f3774 + 0x224, uVar1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      CloseSpriteReadState();
      iVar2 = OpenXFSEntryStream(archiveBase, "fg.dat", 1, 0);
      if (iVar2 != 0) {
        ReadXFSEntryByte(iVar2,&local_4);
        QueueOutgoingPacketField(local_4);
        CloseSpriteReadState();
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
         * 0x423cfe (`lea edi,[ebx + 0x5f3de0]`, ebx=0): 0x5f3de0 -
         * 0x5f3774 = 0x66c = 3*0x224, i.e. element #3 of the same
         * DAT_005f3774 array. See
         * tools/encodeoutgoingpacketfield_sites.json. */
        EncodeOutgoingPacketField((int)&DAT_005f3774 + 0x66c, 0);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = OpenXFSEntryStream(archiveBase, "mb.dat", 1, 0);
        if (iVar2 != 0) {
          ReadXFSEntryByte(iVar2,&local_4);
          QueueOutgoingPacketField(local_4);
          CloseSpriteReadState();
          iVar2 = OpenXFSEntryStream(archiveBase, "mh.dat", 1, 0);
          if (iVar2 != 0) {
            ReadXFSEntryByte(iVar2,&local_4);
            QueueOutgoingPacketField(local_4);
            CloseSpriteReadState();
            iVar2 = OpenXFSEntryStream(archiveBase, "mg.dat", 1, 0);
            if (iVar2 != 0) {
              ReadXFSEntryByte(iVar2,&local_4);
              QueueOutgoingPacketField(local_4);
              CloseSpriteReadState();
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

