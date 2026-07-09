/* LoadSpriteSet - 0x004f1790 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int LoadSpriteSet(undefined4 param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int iVar1;
  void *pvVar2;
  undefined4 *puVar3;
  int iVar4;
  int local_c;
  int local_8;
  int local_4;
  
  /* ReadXFSEntry is void-returning (see its own definition) - the
   * return-value use in the comma-expression below is a Ghidra
   * per-call-site decompilation inconsistency, same class as
   * entry/WinMain.c's FUN_004058c0 fix. iVar1 keeps whatever value it
   * already held (from FindXFSEntry) instead of being reassigned. */
  iVar1 = FindXFSEntry(&DAT_00f11dd0,in_EAX);
  if ((((iVar1 == 0) || (pvVar2 = operator_new(0x1024), pvVar2 == (void *)0x0)) ||
      (ReadXFSEntry(iVar1,&DAT_00f12e18), iVar1 == 0)) ||
     (local_8 = iVar1, ReadXFSEntryByte(iVar1,&local_4), local_4 != 0)) {
    return 0;
  }
  ReadXFSEntryByte(iVar1,&local_c);
  iVar1 = 0;
  if (0 < local_c) {
    do {
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
      iVar4 = FUN_004f1520();
      if (iVar4 == -1) {
        if (puVar3 != (undefined4 *)0x0) {
          (**(code **)*puVar3)(1);
        }
        return -1;
      }
      RegisterActiveObject();
      iVar1 = iVar1 + 1;
    } while (iVar1 < local_c);
  }
  FUN_004f1460();
  return local_c;
}

