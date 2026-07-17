/* State07_AvatarStore_OnExit - 0x00448050 in the original binary.
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


void State07_AvatarStore_OnExit(void)

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
  
  uVar5 = 1000;
  iVar7 = 0x14;
  do {
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar8[1];
    uVar1 = uVar5 + 9000;
    if (uVar2 <= uVar1) {
LAB_00448075:
      if (uVar2 != uVar1) goto code_r0x00448077;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_004480a5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar8[1];
    if (uVar1 <= uVar5) {
LAB_004480b4:
      if (uVar1 != uVar5) goto code_r0x004480b6;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_004480e5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar8[1];
    uVar1 = uVar5 + 100;
    if (uVar2 <= uVar1) {
LAB_004480f7:
      if (uVar2 != uVar1) goto code_r0x004480f9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_00448125:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar8[1];
    uVar1 = uVar5 + 200;
    if (uVar2 <= uVar1) {
LAB_0044813a:
      if (uVar2 != uVar1) goto code_r0x0044813c;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_00448165:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar8[1];
    uVar1 = uVar5 + 300;
    if (uVar2 <= uVar1) {
LAB_0044817a:
      if (uVar2 != uVar1) goto code_r0x0044817c;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_004481a5:
    uVar5 = uVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  uVar5 = 20000;
  iVar7 = 10;
  do {
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar8[1];
    if (uVar1 <= uVar5) {
LAB_004481cf:
      if (uVar1 != uVar5) goto code_r0x004481d1;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_004481f9:
    uVar5 = uVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x7531) {
LAB_0044820f:
    if (uVar5 != 30000) goto code_r0x00448211;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_0044823c:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x9c41) {
LAB_0044824e:
    if (uVar5 != 40000) goto code_r0x00448250;
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
LAB_0044827b:
  iVar7 = g_clientContext;
  piVar6 = (int *)(&DAT_0067ec70 + g_clientContext);
  iVar9 = 0;
  if (0 < *(int *)(&DAT_0067ec70 + g_clientContext)) {
    do {
      FUN_00401650((int *)((char *)piVar6 + 0x20004 + iVar9 * 0x18));
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
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  while( true ) {
    if (200000 < uVar5) goto LAB_0044830d;
    if (uVar5 == 200000) break;
    puVar8 = (undefined4 *)puVar8[7];
    uVar5 = puVar8[1];
  }
  puVar3 = (undefined4 *)puVar8[4];
  while (puVar3 != puVar8) {
    puVar4 = (undefined4 *)*puVar3;
    puVar3 = (undefined4 *)puVar3[4];
    (*(code *)*puVar4)(1);
  }
  puVar8[3] = puVar8;
  puVar8[4] = puVar8;
LAB_0044830d:
  puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar8[1];
  if (uVar5 < 0x493e1) {
    while (uVar5 != 300000) {
      puVar8 = (undefined4 *)puVar8[7];
      uVar5 = puVar8[1];
      if (300000 < uVar5) {
        /* Container passed in EBX by the original (`mov ebx,0xeb1bd8`
         * immediately before the call) - see src/rendering/FlushTextureCache.c. */
        FlushTextureCache((int)&g_textureCache);
        return;
      }
    }
    puVar3 = (undefined4 *)puVar8[4];
    while (puVar3 != puVar8) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar8[3] = puVar8;
    puVar8[4] = puVar8;
  }
  /* Container passed in EBX by the original (`mov ebx,0xeb1bd8` immediately
   * before the call) - see src/rendering/FlushTextureCache.c's header. */
  FlushTextureCache((int)&g_textureCache);
  return;
code_r0x00448077:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_004480a5;
  goto LAB_00448075;
code_r0x004480b6:
  puVar8 = (undefined4 *)puVar8[7];
  uVar1 = puVar8[1];
  if (uVar5 < uVar1) goto LAB_004480e5;
  goto LAB_004480b4;
code_r0x004480f9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_00448125;
  goto LAB_004480f7;
code_r0x0044813c:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_00448165;
  goto LAB_0044813a;
code_r0x0044817c:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_004481a5;
  goto LAB_0044817a;
code_r0x004481d1:
  puVar8 = (undefined4 *)puVar8[7];
  uVar1 = puVar8[1];
  if (uVar5 < uVar1) goto LAB_004481f9;
  goto LAB_004481cf;
code_r0x00448211:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (30000 < uVar5) goto LAB_0044823c;
  goto LAB_0044820f;
code_r0x00448250:
  puVar8 = (undefined4 *)puVar8[7];
  uVar5 = puVar8[1];
  if (40000 < uVar5) goto LAB_0044827b;
  goto LAB_0044824e;
}

