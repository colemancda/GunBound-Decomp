/* FUN_00523fc0 - 0x00523fc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00523fc0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  undefined4 *puVar4;
  DWORD local_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  int iStack_78;
  undefined4 *puStack_74;
  undefined4 auStack_70 [28];
  
  if (DAT_0056adf0 == (HANDLE)0xffffffff) {
    return 0;
  }
  DAT_005b1618 = param_1;
  DAT_005b1620 = param_2;
  DAT_005b161c = DAT_005b162c;
  DAT_005b1624 = param_3;
  if (param_2 == 0x613) {
    iVar1 = lstrlen(param_3);
    uStack_80 = DAT_005b1618;
    DAT_005b1624 = (undefined4 *)(iVar1 + 1);
    iStack_78 = DAT_005b1620;
    uStack_7c = DAT_005b161c;
    puVar4 = auStack_70;
    for (uVar3 = (uint)DAT_005b1624 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = *param_3;
      param_3 = param_3 + 1;
      puVar4 = puVar4 + 1;
    }
    for (uVar3 = (uint)DAT_005b1624 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar4 = *(undefined1 *)param_3;
      param_3 = (undefined4 *)((int)param_3 + 1);
      puVar4 = (undefined4 *)((int)puVar4 + 1);
    }
    puStack_74 = DAT_005b1624;
    iVar1 = WriteFile(DAT_0056adf0,&uStack_80,iVar1 + 0x11,&local_84,(LPOVERLAPPED)0x0);
  }
  else {
    iVar1 = WriteFile(DAT_0056adf0,&DAT_005b1618,0x10,&local_84,(LPOVERLAPPED)0x0);
  }
  if (iVar1 == 0) {
    DVar2 = GetLastError();
    if (((DVar2 == 0x6d) || (DVar2 == 0xe8)) || (DVar2 == 6)) {
      return 0;
    }
  }
  return 1;
}

