/* FUN_004f18c0 - 0x004f18c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "xfs.h"
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

/* Promoted like LoadSpriteSet: `imgName` was in EAX; the read cursor is
 * pvVar2 (operator_new 0x1024); handle/LZHUF state live in
 * g_graphicsArchive at +0x1040 / +0x1048. */
int FUN_004f18c0(undefined4 param_1,undefined4 param_2,int param_3,char *imgName)

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
        FUN_004f16c0();
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
      FUN_004f0530();
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

