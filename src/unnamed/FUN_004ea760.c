/* FUN_004ea760 - 0x004ea760 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004ea760(uint *param_1,uint param_2,uint param_3,uint param_4)

{
  byte bVar1;
  uint *puVar2;
  int iVar3;
  int extraout_EDX;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  
  puVar2 = param_1;
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x3db4));
  param_1[0x3dae] = param_3;
  param_1[0x3daf] = param_2;
  param_1[0x3db0] = param_4;
  param_1[0x3db1] = 0;
  param_1[0x3db2] = 0;
  InitLZHUFTree();
  puVar6 = param_1 + 0x2415;
  for (iVar3 = 0x100; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0x1000;
    puVar6 = puVar6 + 1;
  }
  puVar6 = param_1 + 0x2515;
  for (iVar3 = 0x1000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0x1000;
    puVar6 = puVar6 + 1;
  }
  puVar6 = param_1 + 2;
  for (iVar3 = 0x3f1; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = 0x20202020;
    puVar6 = puVar6 + 1;
  }
  uVar7 = 0;
  param_3 = 0xfc4;
  do {
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) break;
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) break;
    *(byte *)(uVar7 + 0xfcc + (int)param_1) = bVar1;
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) {
LAB_004ea914:
      uVar7 = uVar7 + 1;
      break;
    }
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) goto LAB_004ea914;
    *(byte *)(uVar7 + 0xfcd + (int)param_1) = bVar1;
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) {
LAB_004ea91b:
      uVar7 = uVar7 + 2;
      break;
    }
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) goto LAB_004ea91b;
    *(byte *)(uVar7 + 0xfce + (int)param_1) = bVar1;
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) {
LAB_004ea924:
      uVar7 = uVar7 + 3;
      break;
    }
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) goto LAB_004ea924;
    *(byte *)(uVar7 + 0xfcf + (int)param_1) = bVar1;
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) {
LAB_004ea92d:
      uVar7 = uVar7 + 4;
      break;
    }
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) goto LAB_004ea92d;
    *(byte *)(uVar7 + 0xfd0 + (int)param_1) = bVar1;
    uVar5 = param_1[0x3db1];
    if (param_1[0x3db0] == uVar5) {
LAB_004ea936:
      uVar7 = uVar7 + 5;
      break;
    }
    bVar1 = *(byte *)(uVar5 + param_1[0x3dae]);
    param_1[0x3db1] = uVar5 + 1;
    if (bVar1 == 0xffffffff) goto LAB_004ea936;
    *(byte *)(uVar7 + 0xfd1 + (int)param_1) = bVar1;
    uVar7 = uVar7 + 6;
  } while ((int)uVar7 < 0x3c);
  *param_1 = uVar7;
  iVar3 = 0xfc3;
  do {
    FUN_004e9e90();
    iVar3 = iVar3 + -1;
  } while (0xf87 < iVar3);
  FUN_004e9e90();
  param_1 = (uint *)uVar7;
  do {
    if (param_1 < puVar2[0x412]) {
      puVar2[0x412] = (uint)param_1;
    }
    uVar7 = puVar2[0x412];
    uVar5 = 0;
    if (uVar7 < 3) {
      puVar2[0x412] = 1;
      uVar4 = (uint)*(byte *)(param_3 + 8 + (int)puVar2);
      uVar7 = puVar2[uVar4 + 0x39ff];
      uVar8 = 0;
      do {
        uVar5 = uVar5 >> 1;
        if ((uVar7 & 1) != 0) {
          uVar5 = uVar5 + 0x8000;
        }
        uVar7 = puVar2[uVar7 + 0x378c];
        uVar8 = uVar8 + 1;
      } while (uVar7 != 0x272);
      FUN_004ea230();
      puVar2[0x3516] = uVar5;
      puVar2[0x3517] = uVar8;
      FUN_004ea580(uVar4);
    }
    else {
      uVar4 = puVar2[uVar7 + 0x3afc];
      uVar8 = 0;
      do {
        uVar5 = uVar5 >> 1;
        if ((uVar4 & 1) != 0) {
          uVar5 = uVar5 + 0x8000;
        }
        uVar4 = puVar2[uVar4 + 0x378c];
        uVar8 = uVar8 + 1;
      } while (uVar4 != 0x272);
      FUN_004ea230();
      puVar2[0x3516] = uVar5;
      puVar2[0x3517] = uVar8;
      FUN_004ea580(uVar7 + 0xfd);
      FUN_004ea230();
      FUN_004ea230();
    }
    uVar7 = puVar2[0x412];
    iVar3 = 0;
    if (0 < (int)uVar7) {
      do {
        uVar5 = puVar2[0x3db1];
        if (puVar2[0x3db0] == uVar5) break;
        bVar1 = *(byte *)(uVar5 + puVar2[0x3dae]);
        puVar2[0x3db1] = uVar5 + 1;
        if (bVar1 == 0xffffffff) break;
        FUN_004ea010();
        *(byte *)(extraout_EDX + 8 + (int)puVar2) = bVar1;
        if (extraout_EDX < 0x3b) {
          *(byte *)(extraout_EDX + 0x1008 + (int)puVar2) = bVar1;
        }
        param_3 = param_3 + 1 & 0xfff;
        FUN_004e9e90();
        iVar3 = iVar3 + 1;
      } while (iVar3 < (int)uVar7);
    }
    *puVar2 = *puVar2 + iVar3;
    if (iVar3 < (int)uVar7) {
      iVar3 = uVar7 - iVar3;
      do {
        FUN_004ea010();
        param_3 = param_3 + 1 & 0xfff;
        param_1 = (uint *)((int)param_1 - 1);
        if (param_1 != (uint *)0x0) {
          FUN_004e9e90();
        }
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if ((int)param_1 < 1) {
      if (*(char *)((int)puVar2 + 0xf6b6) != '\0') {
        *(undefined1 *)(puVar2[0x3daf] + puVar2[0x3db2]) = *(undefined1 *)((int)puVar2 + 0xf6b5);
        puVar2[0x3db2] = puVar2[0x3db2] + 1;
        puVar2[1] = puVar2[1] + 1;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(puVar2 + 0x3db4));
      return puVar2[1];
    }
  } while( true );
}

