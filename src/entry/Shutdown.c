/* Shutdown - 0x0040f400 in the original binary.
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


/* param_1 is `int`, not `char`: a K&R-declared (unspecified-args)
 * prior declaration in functions.h can't be defined with a
 * default-promoted parameter type (char/short/float) - char args are
 * promoted to int when passed anyway under cdecl, so this changes
 * nothing about the actual calling convention. */
void Shutdown(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  void *pvVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  void *_Memory;
  bool bVar9;
  
  DAT_00e9c9d0 = 0;
  SetEvent(DAT_00e9c9cc);
  if (DAT_00e9c9c8 != (HANDLE)0x0) {
    WaitForSingleObject(DAT_00e9c9c8,1000);
  }
  if (param_1 != '\0') {
    FUN_0040d760();
    SetEvent(DAT_00e55ce8);
    DAT_00e9c344 = 0;
    SetEvent(DAT_00e9c33c);
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x20))();
    g_currentGameState = 0;
    uVar6 = 600;
    iVar7 = 10;
    do {
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar6 - 100;
      if (uVar2 <= uVar1) {
LAB_0040f492:
        if (uVar2 != uVar1) goto code_r0x0040f494;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_0040f4bc:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar1 = puVar8[1];
      if (uVar1 <= uVar6) {
LAB_0040f4cb:
        if (uVar1 != uVar6) goto code_r0x0040f4cd;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_0040f4f5:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar6 + 100;
      if (uVar2 <= uVar1) {
LAB_0040f507:
        if (uVar2 != uVar1) goto code_r0x0040f509;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_0040f535:
      puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
      uVar2 = puVar8[1];
      uVar1 = uVar6 + 0x6e;
      if (uVar2 <= uVar1) {
LAB_0040f547:
        if (uVar2 != uVar1) goto code_r0x0040f549;
        puVar3 = (undefined4 *)puVar8[4];
        while (puVar3 != puVar8) {
          puVar4 = (undefined4 *)*puVar3;
          puVar3 = (undefined4 *)puVar3[4];
          (*(code *)*puVar4)(1);
        }
        puVar8[3] = puVar8;
        puVar8[4] = puVar8;
      }
LAB_0040f575:
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    bVar9 = true;
    if (puVar8[1] == 0) {
LAB_0040f58c:
      if (!bVar9) goto code_r0x0040f58e;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f5b6:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 2) {
LAB_0040f5c6:
      if (uVar6 != 1) goto code_r0x0040f5c8;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f5f5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 3) {
LAB_0040f605:
      if (uVar6 != 2) goto code_r0x0040f607;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f635:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 4) {
LAB_0040f645:
      if (uVar6 != 3) goto code_r0x0040f647;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f675:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x33) {
LAB_0040f685:
      if (uVar6 != 0x32) goto code_r0x0040f687;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f6b5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x34) {
LAB_0040f6c5:
      if (uVar6 != 0x33) goto code_r0x0040f6c7;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f6f5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x35) {
LAB_0040f705:
      if (uVar6 != 0x34) goto code_r0x0040f707;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f735:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x65) {
LAB_0040f745:
      if (uVar6 != 100) goto code_r0x0040f747;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f775:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x66) {
LAB_0040f785:
      if (uVar6 != 0x65) goto code_r0x0040f787;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f7b5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x6f) {
LAB_0040f7c5:
      if (uVar6 != 0x6e) goto code_r0x0040f7c7;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f7f5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xc9) {
LAB_0040f807:
      if (uVar6 != 200) goto code_r0x0040f809;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f835:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xca) {
LAB_0040f847:
      if (uVar6 != 0xc9) goto code_r0x0040f849;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f875:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xcb) {
LAB_0040f887:
      if (uVar6 != 0xca) goto code_r0x0040f889;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f8b5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xcc) {
LAB_0040f8c7:
      if (uVar6 != 0xcb) goto code_r0x0040f8c9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f8f5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xcd) {
LAB_0040f907:
      if (uVar6 != 0xcc) goto code_r0x0040f909;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f935:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xce) {
LAB_0040f947:
      if (uVar6 != 0xcd) goto code_r0x0040f949;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f975:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xcf) {
LAB_0040f987:
      if (uVar6 != 0xce) goto code_r0x0040f989;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f9b5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x12d) {
LAB_0040f9c7:
      if (uVar6 != 300) goto code_r0x0040f9c9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040f9f5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x191) {
LAB_0040fa07:
      if (uVar6 != 400) goto code_r0x0040fa09;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fa35:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0xf4241) {
LAB_0040fa47:
      if (uVar6 != 1000000) goto code_r0x0040fa49;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fa75:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8481) {
LAB_0040fa87:
      if (uVar6 != 2000000) goto code_r0x0040fa89;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fab5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8482) {
LAB_0040fac7:
      if (uVar6 != 0x1e8481) goto code_r0x0040fac9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040faf5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8483) {
LAB_0040fb07:
      if (uVar6 != 0x1e8482) goto code_r0x0040fb09;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fb35:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8484) {
LAB_0040fb47:
      if (uVar6 != 0x1e8483) goto code_r0x0040fb49;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fb75:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8485) {
LAB_0040fb87:
      if (uVar6 != 0x1e8484) goto code_r0x0040fb89;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fbb5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x1e8486) {
LAB_0040fbc7:
      if (uVar6 != 0x1e8485) goto code_r0x0040fbc9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fbf5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x10c8e1) {
LAB_0040fc07:
      if (uVar6 != 1100000) goto code_r0x0040fc09;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fc35:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x200b22) {
LAB_0040fc47:
      if (uVar6 != 0x200b21) goto code_r0x0040fc49;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fc75:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x200b23) {
LAB_0040fc87:
      if (uVar6 != 0x200b22) goto code_r0x0040fc89;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fcb5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x200b24) {
LAB_0040fcc7:
      if (uVar6 != 0x200b23) goto code_r0x0040fcc9;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fcf5:
    puVar8 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar8[1];
    if (uVar6 < 0x200b25) {
LAB_0040fd07:
      if (uVar6 != 0x200b24) goto code_r0x0040fd09;
      puVar3 = (undefined4 *)puVar8[4];
      while (puVar3 != puVar8) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar8[3] = puVar8;
      puVar8[4] = puVar8;
    }
LAB_0040fd35:
    pvVar5 = DAT_007934e4;
    if (DAT_007934e4 != (void *)0x0) {
      SetWindowLongA(*(HWND *)((int)DAT_007934e4 + 4),-4,*(LONG *)((int)DAT_007934e4 + 0xc));
      _free(pvVar5);
    }
    if (g_gameStateVTableArray[0] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[0])(1);
    }
    if (g_gameStateVTableArray[1] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[1])(1);
    }
    if (g_gameStateVTableArray[2] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[2])(1);
    }
    if (g_gameStateVTableArray[3] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[3])(1);
    }
    if (g_gameStateVTableArray[5] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[5])(1);
    }
    if (g_gameStateVTableArray[6] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[6])(1);
    }
    if (g_gameStateVTableArray[7] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[7])(1);
    }
    if (g_gameStateVTableArray[9] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[9])(1);
    }
    if (g_gameStateVTableArray[10] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[10])(1);
    }
    if (g_gameStateVTableArray[0xb] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[0xb])(1);
    }
    if (g_gameStateVTableArray[0xf] != (undefined *)0x0) {
      (*(code *)**(undefined4 **)g_gameStateVTableArray[0xf])(1);
    }
    if (DAT_00e52814 != (int *)0x0) {
      (**(code **)(*DAT_00e52814 + 0x20))(DAT_00e52814);
      DAT_00e52864 = 0;
      (**(code **)(*DAT_00e52814 + 8))(DAT_00e52814);
      DAT_00e52814 = (int *)0x0;
    }
    if (DAT_00e5369c != (int *)0x0) {
      (**(code **)(*DAT_00e5369c + 0x20))(DAT_00e5369c);
      DAT_00e536ec = 0;
      (**(code **)(*DAT_00e5369c + 8))(DAT_00e5369c);
      DAT_00e5369c = (int *)0x0;
    }
    pvVar5 = DAT_007934f4;
    if (DAT_007934f4 != (void *)0x0) {
      iVar7 = *(int *)((int)DAT_007934f4 + 0x2004);
      *(undefined4 *)(iVar7 + 0x22c) = 1;
      _Memory = pvVar5;
      if (*(SOCKET *)(iVar7 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar7 + 0x24));
        _Memory = DAT_007934f4;
      }
      *(undefined4 *)(iVar7 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar7 + 0x22a) = 0;
      *(undefined1 *)((int)pvVar5 + 0x2009) = 0;
      if (_Memory != (void *)0x0) {
        FUN_00405930();
        _free(_Memory);
      }
    }
    pvVar5 = DAT_005b2b58;
    iVar7 = *(int *)((int)DAT_005b2b58 + 0x84e0);
    DAT_007934f4 = (void *)0x0;
    DAT_007934e8 = 0;
    if (iVar7 != 0) {
      *(undefined4 *)(iVar7 + 0x22c) = 1;
      if (*(SOCKET *)(iVar7 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar7 + 0x24));
      }
      *(undefined4 *)(iVar7 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar7 + 0x22a) = 0;
      *(undefined1 *)((int)pvVar5 + 0x84e5) = 0;
    }
    pvVar5 = DAT_005b2b5c;
    iVar7 = *(int *)((int)DAT_005b2b5c + 0x84e0);
    if (iVar7 != 0) {
      *(undefined4 *)(iVar7 + 0x22c) = 1;
      if (*(SOCKET *)(iVar7 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar7 + 0x24));
      }
      *(undefined4 *)(iVar7 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar7 + 0x22a) = 0;
      *(undefined1 *)((int)pvVar5 + 0x84e5) = 0;
    }
    pvVar5 = DAT_005b2b60;
    iVar7 = *(int *)((int)DAT_005b2b60 + 0x84e0);
    if (iVar7 != 0) {
      *(undefined4 *)(iVar7 + 0x22c) = 1;
      if (*(SOCKET *)(iVar7 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar7 + 0x24));
      }
      *(undefined4 *)(iVar7 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar7 + 0x22a) = 0;
      *(undefined1 *)((int)pvVar5 + 0x84e5) = 0;
    }
    pvVar5 = DAT_005b2b58;
    if (DAT_005b2b58 != (void *)0x0) {
      FUN_004d22d0(DAT_005b2b58);
      _free(pvVar5);
    }
    pvVar5 = DAT_005b2b5c;
    DAT_005b2b58 = (void *)0x0;
    if (DAT_005b2b5c != (void *)0x0) {
      FUN_004d22d0(DAT_005b2b5c);
      _free(pvVar5);
    }
    pvVar5 = DAT_005b2b60;
    DAT_005b2b5c = (void *)0x0;
    if (DAT_005b2b60 != (void *)0x0) {
      FUN_004d22d0(DAT_005b2b60);
      _free(pvVar5);
    }
    DAT_005b2b60 = (void *)0x0;
    if (((char)DAT_00793228 == '\x01') && ((char)((ushort)DAT_00793228 >> 8) == '\x01')) {
      WSACleanup();
    }
    if (DAT_00674f68 != (int *)0x0) {
      (**(code **)(*DAT_00674f68 + 8))(DAT_00674f68);
      DAT_00674f68 = (int *)0x0;
    }
    FreeLibrary(DAT_00793544);
    FUN_004ee850();
  }
  ShutdownDirectDraw();
                    /* WARNING: Could not recover jumptable at 0x00410039. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CoUninitialize();
  return;
code_r0x0040f494:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_0040f4bc;
  goto LAB_0040f492;
code_r0x0040f4cd:
  puVar8 = (undefined4 *)puVar8[7];
  uVar1 = puVar8[1];
  if (uVar6 < uVar1) goto LAB_0040f4f5;
  goto LAB_0040f4cb;
code_r0x0040f509:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_0040f535;
  goto LAB_0040f507;
code_r0x0040f549:
  puVar8 = (undefined4 *)puVar8[7];
  uVar2 = puVar8[1];
  if (uVar1 < uVar2) goto LAB_0040f575;
  goto LAB_0040f547;
code_r0x0040f58e:
  puVar8 = (undefined4 *)puVar8[7];
  bVar9 = puVar8[1] == 0;
  if (!bVar9) goto LAB_0040f5b6;
  goto LAB_0040f58c;
code_r0x0040f5c8:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (1 < uVar6) goto LAB_0040f5f5;
  goto LAB_0040f5c6;
code_r0x0040f607:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (2 < uVar6) goto LAB_0040f635;
  goto LAB_0040f605;
code_r0x0040f647:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (3 < uVar6) goto LAB_0040f675;
  goto LAB_0040f645;
code_r0x0040f687:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x32 < uVar6) goto LAB_0040f6b5;
  goto LAB_0040f685;
code_r0x0040f6c7:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x33 < uVar6) goto LAB_0040f6f5;
  goto LAB_0040f6c5;
code_r0x0040f707:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x34 < uVar6) goto LAB_0040f735;
  goto LAB_0040f705;
code_r0x0040f747:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (100 < uVar6) goto LAB_0040f775;
  goto LAB_0040f745;
code_r0x0040f787:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x65 < uVar6) goto LAB_0040f7b5;
  goto LAB_0040f785;
code_r0x0040f7c7:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x6e < uVar6) goto LAB_0040f7f5;
  goto LAB_0040f7c5;
code_r0x0040f809:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (200 < uVar6) goto LAB_0040f835;
  goto LAB_0040f807;
code_r0x0040f849:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xc9 < uVar6) goto LAB_0040f875;
  goto LAB_0040f847;
code_r0x0040f889:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xca < uVar6) goto LAB_0040f8b5;
  goto LAB_0040f887;
code_r0x0040f8c9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xcb < uVar6) goto LAB_0040f8f5;
  goto LAB_0040f8c7;
code_r0x0040f909:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xcc < uVar6) goto LAB_0040f935;
  goto LAB_0040f907;
code_r0x0040f949:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xcd < uVar6) goto LAB_0040f975;
  goto LAB_0040f947;
code_r0x0040f989:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0xce < uVar6) goto LAB_0040f9b5;
  goto LAB_0040f987;
code_r0x0040f9c9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (300 < uVar6) goto LAB_0040f9f5;
  goto LAB_0040f9c7;
code_r0x0040fa09:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (400 < uVar6) goto LAB_0040fa35;
  goto LAB_0040fa07;
code_r0x0040fa49:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (1000000 < uVar6) goto LAB_0040fa75;
  goto LAB_0040fa47;
code_r0x0040fa89:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (2000000 < uVar6) goto LAB_0040fab5;
  goto LAB_0040fa87;
code_r0x0040fac9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x1e8481 < uVar6) goto LAB_0040faf5;
  goto LAB_0040fac7;
code_r0x0040fb09:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x1e8482 < uVar6) goto LAB_0040fb35;
  goto LAB_0040fb07;
code_r0x0040fb49:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x1e8483 < uVar6) goto LAB_0040fb75;
  goto LAB_0040fb47;
code_r0x0040fb89:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x1e8484 < uVar6) goto LAB_0040fbb5;
  goto LAB_0040fb87;
code_r0x0040fbc9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x1e8485 < uVar6) goto LAB_0040fbf5;
  goto LAB_0040fbc7;
code_r0x0040fc09:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (1100000 < uVar6) goto LAB_0040fc35;
  goto LAB_0040fc07;
code_r0x0040fc49:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x200b21 < uVar6) goto LAB_0040fc75;
  goto LAB_0040fc47;
code_r0x0040fc89:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x200b22 < uVar6) goto LAB_0040fcb5;
  goto LAB_0040fc87;
code_r0x0040fcc9:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x200b23 < uVar6) goto LAB_0040fcf5;
  goto LAB_0040fcc7;
code_r0x0040fd09:
  puVar8 = (undefined4 *)puVar8[7];
  uVar6 = puVar8[1];
  if (0x200b24 < uVar6) goto LAB_0040fd35;
  goto LAB_0040fd07;
}

