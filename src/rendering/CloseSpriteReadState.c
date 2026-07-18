/* CloseSpriteReadState - 0x004f1460 in the original binary.
 *
 * PROMOTED (2026-07-14): releases an XFS sprite-set read cursor
 * (`readState`, LoadSpriteSet's own operator_new(0x1024) scratch object)
 * back to the owning archive (`archive`) - if the cursor's "page changed"
 * flag (+0x1018) is clear, folds its unread/leftover byte count back into
 * the archive's own accounting field (+0x10, chosen from +0x78/+0x7c
 * depending on the session object's mode flag at +0x70) and clears the
 * session's "busy" flag (+0x1044), then frees `readState` itself.
 *
 * DOUBLE DROPPED-ARGUMENT FIX: Ghidra read both `readState` (as
 * unaff_EAX/in_EAX) and `archive` (as unaff_EDI) as uninitialized locals -
 * neither was ever a real parameter in this raw port, so every call site
 * (LoadSpriteSet.c and ~13 others) invoked it with zero arguments,
 * reading garbage for both. Recovered from LoadSpriteSet's own call site
 * (orig 0x4f188a-0x4f1891: `mov eax,esi` where esi is `readState`,
 * `mov edi,0xf11dd0` - the literal &g_graphicsArchive - immediately
 * before `call 0x4f1460`).
 *
 * NOT FIXED HERE: this function has ~13 other call sites (PreloadTexture.c,
 * FUN_00415900.c, FUN_00423e20.c, FUN_004ef5b0.c, FUN_004e3c50.c,
 * FUN_004e3500.c, FUN_004240c0.c, FUN_00423bf0.c, FUN_004eef00.c,
 * LoadChooseEventConfig.c, LoadLocalizedStrings.c), each in its own
 * not-yet-verified caller with its own distinct readState/archive
 * sources - those still use the old 0-arg form and need the same
 * per-site disassembly treatment (same partial-fix precedent as
 * RegisterActiveObject.c/CreateActiveObjectLayer.c). The conditionally-
 * called FlushXFSWriteBlock() (its own dropped-arg helper, invoked when the
 * session object's +0x100c count is nonzero and +0x70 accounting field
 * is still zero) is also untouched - out of scope here, unreached on the
 * bring-up path since that combination doesn't occur while the archive's
 * per-session accounting field stays at its freshly-allocated zero.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-
 * verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 CloseSpriteReadState(void *readState, int archive)

{
  int iVar1;

  if (readState != (void *)0x0) {
    if (*(char *)((int)readState + 0x1018) == '\0') {
      if ((*(int *)((int)readState + 0x100c) != 0) &&
         (*(int *)(*(int *)((int)readState + 0x1004) + 0x70) == 0)) {
        FlushXFSWriteBlock();
      }
      iVar1 = *(int *)((int)readState + 0x1004);
      if (*(int *)(iVar1 + 0x70) == 1) {
        iVar1 = *(int *)(iVar1 + 0x78);
      }
      else {
        iVar1 = *(int *)(iVar1 + 0x7c);
      }
      *(int *)(archive + 0x10) = *(int *)(archive + 0x10) + iVar1;
      *(undefined1 *)(archive + 0x1044) = 0;
    }
    _free(readState);
  }
  return 0;
}
