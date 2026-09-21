/* LoadSpriteSetFrame - 0x004f18c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NAMED (2026-09-21). Near-identical XFS-archive loader to LoadSpriteSet
 * (same imgName-in-EAX idiom, same g_spriteRegistry/g_graphicsArchive
 * machinery, same per-entry 0x50-byte object) - confirmed by its own
 * callers' imgNames ("loadstage.img" in State10_Loading_OnEnter.c,
 * "event<N>1800.img" in LoadStageDecorationSet.c, both ordinary sprite-
 * set archives). The difference from LoadSpriteSet is the `if (iVar1 ==
 * param_3)` gate: only the ONE archive entry whose index matches
 * `param_3` is decoded and RegisterActiveObject'd - every other entry
 * in the set is skipped (FUN_004f16c0 + scalar-deleting-destructor
 * call) rather than registered. All 5 call sites pass an explicit
 * index/variant selector as `param_3` (0/1 for a stage-decoration
 * variant, or a byte-derived index for the two loadstage.img calls),
 * i.e. this loads and registers a single selected frame out of a
 * multi-frame set, not the whole set.
 */
#include "xfs.h"
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* Promoted like LoadSpriteSet: `imgName` was in EAX; the read cursor is
 * pvVar2 (operator_new 0x1024); handle/LZHUF state live in
 * g_graphicsArchive at +0x1040 / +0x1048.
 *
 * DROPPED-ARGUMENT FIX (2026-09-21): `imgName` was already a real,
 * correctly-typed trailing parameter here, but functions.h had no
 * prototype for this function (K&R-empty), so all 5 call sites in the
 * tree silently compiled passing only param_1/param_2/param_3 and
 * dropped imgName entirely. Each site's string reconstructed from its
 * own disasm - see src/rendering/LoadStageDecorationSet.c (x3) and
 * src/state_machine/State10_Loading_OnEnter.c (x2). Matches the
 * project's established convention (see LoadSpriteSet.c) of modelling
 * this original-EAX value as a normal trailing C parameter rather than
 * a real register arg, since callee and caller are rebuilt together. */
int LoadSpriteSetFrame(undefined4 param_1,undefined4 param_2,int param_3,char *imgName)

{
  int iVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int local_10;
  int local_c;
  void *local_8;
  int local_4;
  HANDLE gh = *(HANDLE *)(g_graphicsArchive.bytes + 0x1040);
  void  *lz = g_graphicsArchive.bytes + 0x1048;

  iVar1 = FindXFSEntry(&g_graphicsArchive,imgName);
  if ((iVar1 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) {
    return 0;
  }
  pvVar2 = (void *)ReadXFSEntry(pvVar2,gh,1,iVar1,lz);
  if (pvVar2 == (void *)0x0) {
    return 0;
  }
  local_8 = pvVar2;
  ReadXFSEntryByte(pvVar2,(undefined4 *)&local_4,4);
  if (local_4 != 0) {
    return 0;
  }
  ReadXFSEntryByte(pvVar2,(undefined4 *)&local_10,4);
  local_c = 0;
  if (0 < local_10) {
    do {
      iVar1 = local_c;
      puVar3 = operator_new(0x50);
      if (puVar3 == (undefined4 *)0x0) {
        puVar3 = (undefined4 *)0x0;
      }
      else {
        puVar3[1] = param_2;
        puVar3[2] = iVar1;
        puVar3[3] = 0;
        puVar3[4] = 0;
        *(undefined1 *)(puVar3 + 5) = 0;
        *(undefined1 *)((int)puVar3 + 0x15) = 0;
        *puVar3 = &PTR_FUN_00557524;
        *(undefined1 *)((int)puVar3 + 0x1b) = 0xff;
        *(undefined1 *)((int)puVar3 + 0x1a) = 0;
        *(undefined1 *)((int)puVar3 + 0x19) = 0xff;
        puVar3[8] = 0;
        puVar3[9] = 0;
        puVar3[0xb] = 0;
        puVar3[10] = 0;
        *(undefined1 *)(puVar3 + 0xc) = 0;
        puVar3[0xd] = 0;
        puVar3[0xe] = 0;
      }
      if (iVar1 == param_3) {
        iVar1 = FUN_004f1520();
        pvVar2 = local_8;
        if (iVar1 == -1) break;
        RegisterActiveObject(0, 0, (undefined4 *)0);
        pvVar2 = local_8;
        iVar1 = local_c;
      }
      else {
        /* FIXED (2026-08-11): dropped stream (ESI) - at the orig call
         * 0x4f19c9 ESI still holds the open read stream (set for the
         * ReadXFSEntryByte calls above; only the taken-match branch at
         * 0x4f19a6 clobbers it and restores from [esp+0x18] right
         * after). local_8 is that stream. */
        FUN_004f16c0((int)local_8);
        if (puVar3 != (undefined4 *)0x0) {
          (**(code **)*puVar3)(1);
        }
      }
      local_c = iVar1 + 1;
    } while (local_c < local_10);
  }
  if (*(char *)((int)pvVar2 + 0x1018) == '\0') {
    if ((*(int *)((int)pvVar2 + 0x100c) != 0) &&
       (*(int *)(*(int *)((int)pvVar2 + 0x1004) + 0x70) == 0)) {
      FlushXFSWriteBlock();
    }
    iVar1 = *(int *)((int)pvVar2 + 0x1004);
    if (*(int *)(iVar1 + 0x70) == 1) {
      iVar1 = *(int *)(iVar1 + 0x78);
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x7c);
    }
    _DAT_00f11de0 = _DAT_00f11de0 + iVar1;
    DAT_00f12e14 = 0;
  }
  _free(pvVar2);
  return local_10;
}

