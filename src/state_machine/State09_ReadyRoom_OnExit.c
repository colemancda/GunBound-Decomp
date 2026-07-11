/* State09_ReadyRoom_OnExit - 0x004d7630 in the original binary.
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


void __fastcall State09_ReadyRoom_OnExit(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  
  FUN_0050ef10(&g_uiPanelManager);
  FUN_00509700();
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2711) {
LAB_004d7665:
    if (uVar5 != 10000) goto code_r0x004d7667;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7695:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2712) {
LAB_004d76a7:
    if (uVar5 != 0x2711) goto code_r0x004d76a9;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d76d5:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2713) {
LAB_004d76e7:
    if (uVar5 != 0x2712) goto code_r0x004d76e9;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7715:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2714) {
LAB_004d7727:
    if (uVar5 != 0x2713) goto code_r0x004d7729;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7755:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2715) {
LAB_004d7767:
    if (uVar5 != 0x2714) goto code_r0x004d7769;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7795:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2716) {
LAB_004d77a7:
    if (uVar5 != 0x2715) goto code_r0x004d77a9;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d77d5:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2717) {
LAB_004d77e7:
    if (uVar5 != 0x2716) goto code_r0x004d77e9;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7815:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2718) {
LAB_004d7827:
    if (uVar5 != 0x2717) goto code_r0x004d7829;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7855:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x2719) {
LAB_004d7867:
    if (uVar5 != 0x2718) goto code_r0x004d7869;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d7895:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x271b) {
LAB_004d78a7:
    if (uVar5 != 0x271a) goto code_r0x004d78a9;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_004d78d5:
  if (g_bBattleSessionActive == '\0') {
    uVar5 = 1000;
    do {
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar1 = puVar8[1];
      if (uVar1 <= uVar5) {
LAB_004d78ff:
        if (uVar1 != uVar5) goto code_r0x004d7901;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_004d7929:
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < 0x5dd);
    uVar5 = 300000;
    iVar7 = 0x14;
    do {
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar5 - 100000;
      if (uVar2 <= uVar1) {
LAB_004d7955:
        if (uVar2 != uVar1) goto code_r0x004d7957;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_004d7985:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar1 = puVar8[1];
      if (uVar1 <= uVar5) {
LAB_004d7994:
        if (uVar1 != uVar5) goto code_r0x004d7996;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_004d79c5:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar5 - 0x48058;
      if (uVar2 <= uVar1) {
LAB_004d79da:
        if (uVar2 != uVar1) goto code_r0x004d79dc;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_004d7a05:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar5 - 0x47ff4;
      if (uVar2 <= uVar1) {
LAB_004d7a1a:
        if (uVar2 != uVar1) goto code_r0x004d7a1c;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_004d7a45:
      uVar5 = uVar5 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar5 = puVar8[1];
    if (uVar5 < 0x14b5) {
LAB_004d7a60:
      if (uVar5 != 0x14b4) goto code_r0x004d7a62;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_004d7a8d:
    iVar7 = g_clientContext;
    piVar6 = (int *)(&DAT_0067ec70 + g_clientContext);
    iVar9 = 0;
    if (0 < *(int *)(&DAT_0067ec70 + g_clientContext)) {
      do {
        FUN_00401650();
        iVar9 = iVar9 + 1;
      } while (iVar9 < *piVar6);
    }
    *piVar6 = 0;
    puVar8 = (undefined4 *)(&DAT_0067ec74 + iVar7);
    for (iVar9 = 0x8000; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
    puVar8 = (undefined4 *)(&DAT_0069ec74 + iVar7);
    for (iVar9 = 0x1800; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
    }
  }
  piVar6 = (int *)(param_1 + 0x700);
  g_bBattleSessionActive = 0;
  iVar7 = 8;
  do {
    if ((undefined4 *)piVar6[-1] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)piVar6[-1])(1);
    }
    if ((undefined4 *)*piVar6 != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)*piVar6)(1);
    }
    piVar6[-1] = 0;
    *piVar6 = 0;
    piVar6 = piVar6 + 2;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
code_r0x004d7667:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (10000 < uVar5) goto LAB_004d7695;
  goto LAB_004d7665;
code_r0x004d76a9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2711 < uVar5) goto LAB_004d76d5;
  goto LAB_004d76a7;
code_r0x004d76e9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2712 < uVar5) goto LAB_004d7715;
  goto LAB_004d76e7;
code_r0x004d7729:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2713 < uVar5) goto LAB_004d7755;
  goto LAB_004d7727;
code_r0x004d7769:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2714 < uVar5) goto LAB_004d7795;
  goto LAB_004d7767;
code_r0x004d77a9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2715 < uVar5) goto LAB_004d77d5;
  goto LAB_004d77a7;
code_r0x004d77e9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2716 < uVar5) goto LAB_004d7815;
  goto LAB_004d77e7;
code_r0x004d7829:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2717 < uVar5) goto LAB_004d7855;
  goto LAB_004d7827;
code_r0x004d7869:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x2718 < uVar5) goto LAB_004d7895;
  goto LAB_004d7867;
code_r0x004d78a9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x271a < uVar5) goto LAB_004d78d5;
  goto LAB_004d78a7;
code_r0x004d7901:
  puVar8 = (undefined4 *)puVar8[7];
  uVar1 = puVar8[1];
  if (uVar5 < uVar1) goto LAB_004d7929;
  goto LAB_004d78ff;
code_r0x004d7957:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_004d7985;
  goto LAB_004d7955;
code_r0x004d7996:
  puVar8 = (undefined4 *)puVar8[7];
  uVar1 = puVar8[1];
  if (uVar5 < uVar1) goto LAB_004d79c5;
  goto LAB_004d7994;
code_r0x004d79dc:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_004d7a05;
  goto LAB_004d79da;
code_r0x004d7a1c:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_004d7a45;
  goto LAB_004d7a1a;
code_r0x004d7a62:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (0x14b4 < uVar5) goto LAB_004d7a8d;
  goto LAB_004d7a60;
}

