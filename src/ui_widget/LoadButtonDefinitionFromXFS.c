/* LoadButtonDefinitionFromXFS - 0x00401440 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void LoadButtonDefinitionFromXFS(void)

{
  void *_Memory;
  void *pvVar1;
  int iVar2;
  int iVar3;
  uint *unaff_EBX;
  int iVar4;
  int local_4;
  
  _Memory = (void *)FUN_004f1390(0);
  if (_Memory != (void *)0x0) {
    ReadXFSEntryByte(_Memory,unaff_EBX);
    pvVar1 = operator_new(*unaff_EBX << 2);
    unaff_EBX[1] = (uint)pvVar1;
    pvVar1 = operator_new(*unaff_EBX);
    unaff_EBX[2] = (uint)pvVar1;
    pvVar1 = operator_new(*unaff_EBX << 2);
    unaff_EBX[3] = (uint)pvVar1;
    pvVar1 = operator_new(*unaff_EBX << 2);
    unaff_EBX[4] = (uint)pvVar1;
    pvVar1 = operator_new(*unaff_EBX << 2);
    unaff_EBX[5] = (uint)pvVar1;
    iVar4 = 0;
    if (0 < (int)*unaff_EBX) {
      while (iVar2 = ReadXFSEntryByte(_Memory,&local_4), iVar2 != -1) {
        pvVar1 = operator_new(local_4 + 1);
        iVar2 = iVar4 * 4;
        *(void **)(iVar2 + unaff_EBX[1]) = pvVar1;
        iVar3 = ReadXFSEntryByte(_Memory,*(undefined4 *)(iVar2 + unaff_EBX[1]));
        if (iVar3 == -1) break;
        *(undefined1 *)(local_4 + *(int *)(iVar2 + unaff_EBX[1])) = 0;
        iVar3 = ReadXFSEntryByte(_Memory,unaff_EBX[2] + iVar4);
        if ((iVar3 == -1) || (iVar3 = ReadXFSEntryByte(_Memory,unaff_EBX[3] + iVar2), iVar3 == -1))
        break;
        pvVar1 = operator_new(*(int *)(iVar2 + unaff_EBX[3]) << 2);
        *(void **)(iVar2 + unaff_EBX[4]) = pvVar1;
        pvVar1 = operator_new(*(int *)(iVar2 + unaff_EBX[3]) << 2);
        *(void **)(iVar2 + unaff_EBX[5]) = pvVar1;
        iVar3 = ReadXFSEntryByte(_Memory,*(undefined4 *)(unaff_EBX[4] + iVar2));
        if ((iVar3 == -1) ||
           ((iVar2 = ReadXFSEntryByte(_Memory,*(undefined4 *)(iVar2 + unaff_EBX[5])), iVar2 == -1 ||
            (iVar4 = iVar4 + 1, (int)*unaff_EBX <= iVar4)))) break;
      }
    }
    if (*(char *)((int)_Memory + 0x1018) == '\0') {
      if ((*(int *)((int)_Memory + 0x100c) != 0) &&
         (*(int *)(*(int *)((int)_Memory + 0x1004) + 0x70) == 0)) {
        FUN_004f0530();
      }
      iVar4 = *(int *)((int)_Memory + 0x1004);
      if (*(int *)(iVar4 + 0x70) == 1) {
        iVar4 = *(int *)(iVar4 + 0x78);
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x7c);
      }
      _DAT_00f11de0 = _DAT_00f11de0 + iVar4;
      DAT_00f12e14 = 0;
    }
    _free(_Memory);
  }
  return;
}

