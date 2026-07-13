/* State03_GameRoomList_OnExit - 0x00429480 in the original binary.
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


void State03_GameRoomList_OnExit(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  
  uVar6 = 1000;
  iVar8 = 10;
  do {
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 9000;
    if (uVar2 <= uVar1) {
LAB_004294a5:
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
LAB_004294d5:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar9[1];
    if (uVar1 <= uVar6) {
LAB_004294e4:
      if (uVar1 != uVar6) goto code_r0x004294e6;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429515:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 100;
    if (uVar2 <= uVar1) {
LAB_00429527:
      if (uVar2 != uVar1) goto code_r0x00429529;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429555:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 200;
    if (uVar2 <= uVar1) {
LAB_0042956a:
      if (uVar2 != uVar1) goto code_r0x0042956c;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429595:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 300;
    if (uVar2 <= uVar1) {
LAB_004295aa:
      if (uVar2 != uVar1) goto code_r0x004295ac;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_004295d5:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 400;
    if (uVar2 <= uVar1) {
LAB_004295ea:
      if (uVar2 != uVar1) goto code_r0x004295ec;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429615:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 500;
    if (uVar2 <= uVar1) {
LAB_0042962a:
      if (uVar2 != uVar1) goto code_r0x0042962c;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429655:
    puVar9 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar9[1];
    uVar1 = uVar6 + 600;
    if (uVar2 <= uVar1) {
LAB_0042966a:
      if (uVar2 != uVar1) goto code_r0x0042966c;
      puVar3 = (undefined4 *)puVar9[4];
      while (puVar3 != puVar9) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar9[3] = puVar9;
      puVar9[4] = puVar9;
    }
LAB_00429695:
    iVar5 = g_clientContext;
    uVar6 = uVar6 + 1;
    iVar8 = iVar8 + -1;
    if (iVar8 == 0) {
      piVar7 = (int *)(&DAT_0067ec70 + g_clientContext);
      iVar8 = 0;
      if (0 < *(int *)(&DAT_0067ec70 + g_clientContext)) {
        do {
          FUN_00401650((int *)((char *)piVar7 + 0x20004 + iVar8 * 0x18));
          iVar8 = iVar8 + 1;
        } while (iVar8 < *piVar7);
      }
      *piVar7 = 0;
      puVar9 = (undefined4 *)(&DAT_0067ec74 + iVar5);
      for (iVar8 = 0x8000; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      puVar9 = (undefined4 *)(&DAT_0069ec74 + iVar5);
      for (iVar8 = 0x1800; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
      piVar7 = DAT_00e53c44;
      if (DAT_00e53c44 != (int *)0x0) {
        while( true ) {
          iVar8 = piVar7[2];
          piVar7 = (int *)*piVar7;
          if ((*(int *)(iVar8 + 0x20) == 0) && (*(int *)(iVar8 + 0x24) == 20000)) break;
          if (piVar7 == (int *)0x0) {
            return;
          }
        }
        *(undefined1 *)(iVar8 + 0x1d) = 1;
      }
      return;
    }
  } while( true );
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_004294d5;
  goto LAB_004294a5;
code_r0x004294e6:
  puVar9 = (undefined4 *)puVar9[7];
  uVar1 = puVar9[1];
  if (uVar6 < uVar1) goto LAB_00429515;
  goto LAB_004294e4;
code_r0x00429529:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_00429555;
  goto LAB_00429527;
code_r0x0042956c:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_00429595;
  goto LAB_0042956a;
code_r0x004295ac:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_004295d5;
  goto LAB_004295aa;
code_r0x004295ec:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_00429615;
  goto LAB_004295ea;
code_r0x0042962c:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_00429655;
  goto LAB_0042962a;
code_r0x0042966c:
  puVar9 = (undefined4 *)puVar9[7];
  uVar2 = puVar9[1];
  if (uVar1 < uVar2) goto LAB_00429695;
  goto LAB_0042966a;
}

