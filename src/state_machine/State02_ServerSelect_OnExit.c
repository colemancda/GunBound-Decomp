/* State02_ServerSelect_OnExit - 0x004e17f0 in the original binary.
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


void State02_ServerSelect_OnExit(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined4 *puVar9;
  
  uVar6 = 1000;
  iVar7 = 3;
  do {
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 9000;
    if (uVar2 <= uVar1) {
LAB_004e1815:
      if (uVar2 != uVar1) break;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_004e1845:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar9[1];
    if (uVar1 <= uVar6) {
LAB_004e1854:
      if (uVar1 != uVar6) goto code_r0x004e1856;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_004e1885:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 100;
    if (uVar2 <= uVar1) {
LAB_004e1897:
      if (uVar2 != uVar1) goto code_r0x004e1899;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_004e18c5:
    iVar5 = DAT_005b3484;
    uVar6 = uVar6 + 1;
    iVar7 = iVar7 + -1;
    if (iVar7 == 0) {
      piVar8 = (int *)(&DAT_0067ec70 + DAT_005b3484);
      iVar7 = 0;
      if (0 < *(int *)(&DAT_0067ec70 + DAT_005b3484)) {
        do {
          FUN_00401650();
          iVar7 = iVar7 + 1;
        } while (iVar7 < *piVar8);
      }
      *piVar8 = 0;
      puVar9 = (undefined4 *)(&DAT_0067ec74 + iVar5);
      for (iVar7 = 0x8000; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      puVar9 = (undefined4 *)(&DAT_0069ec74 + iVar5);
      for (iVar7 = 0x1800; iVar5 = DAT_007934f0, iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      iVar7 = *(int *)(DAT_007934f0 + 0x84e0);
      if (iVar7 != 0) {
        *(undefined4 *)(iVar7 + 0x22c) = 1;
        if (*(SOCKET *)(iVar7 + 0x24) != 0xffffffff) {
          closesocket(*(SOCKET *)(iVar7 + 0x24));
        }
        *(undefined4 *)(iVar7 + 0x24) = 0xffffffff;
        *(undefined1 *)(iVar7 + 0x22a) = 0;
        *(undefined1 *)(iVar5 + 0x84e5) = 0;
      }
      return;
    }
  } while( true );
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_004e1845;
  goto LAB_004e1815;
code_r0x004e1856:
  puVar9 = (undefined4 *)puVar9[7];
  uVar1 = puVar9[1];
  if (uVar6 < uVar1) goto LAB_004e1885;
  goto LAB_004e1854;
code_r0x004e1899:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_004e18c5;
  goto LAB_004e1897;
}

