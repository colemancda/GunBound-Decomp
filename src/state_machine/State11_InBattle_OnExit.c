/* State11_InBattle_OnExit - 0x004bcd00 in the original binary.
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

void __fastcall State11_InBattle_OnExit(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  int iStack_8;
  
  DAT_007a768c = 0;
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x1b59) {
LAB_004bcd24:
    if (uVar8 != 7000) goto code_r0x004bcd26;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcd55:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x1b5a) {
LAB_004bcd67:
    if (uVar8 != 0x1b59) goto code_r0x004bcd69;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcd95:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x1b5b) {
LAB_004bcda7:
    if (uVar8 != 0x1b5a) goto code_r0x004bcda9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcdd5:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x1bbd) {
LAB_004bcde7:
    if (uVar8 != 0x1bbc) goto code_r0x004bcde9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bce15:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2329) {
LAB_004bce27:
    if (uVar8 != 9000) goto code_r0x004bce29;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bce55:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x232a) {
LAB_004bce67:
    if (uVar8 != 0x2329) goto code_r0x004bce69;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bce95:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x1901) {
LAB_004bcea7:
    if (uVar8 != 0x1900) goto code_r0x004bcea9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bced5:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2711) {
LAB_004bcee7:
    if (uVar8 != 10000) goto code_r0x004bcee9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcf15:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2712) {
LAB_004bcf27:
    if (uVar8 != 0x2711) goto code_r0x004bcf29;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcf55:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2713) {
LAB_004bcf67:
    if (uVar8 != 0x2712) goto code_r0x004bcf69;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcf95:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2714) {
LAB_004bcfa7:
    if (uVar8 != 0x2713) goto code_r0x004bcfa9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bcfd5:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2715) {
LAB_004bcfe7:
    if (uVar8 != 0x2714) goto code_r0x004bcfe9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bd015:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2716) {
LAB_004bd027:
    if (uVar8 != 0x2715) goto code_r0x004bd029;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bd055:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x2717) {
LAB_004bd067:
    if (uVar8 != 0x2716) goto code_r0x004bd069;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bd095:
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  if (uVar8 < 0x271a) {
LAB_004bd0a7:
    if (uVar8 != 0x2719) goto code_r0x004bd0a9;
    puVar3 = (undefined4 *)puVar10[4];
    while (puVar3 != puVar10) {
      puVar4 = (undefined4 *)*puVar3;
      puVar3 = (undefined4 *)puVar3[4];
      (*(code *)*puVar4)(1);
    }
    puVar10[3] = puVar10;
    puVar10[4] = puVar10;
  }
LAB_004bd0d5:
  if (g_cursorFreeMode != '\x01') {
    g_cursorFreeMode = '\x01';
  }
  uVar8 = 1000;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd0ff:
      if (uVar2 != uVar8) goto code_r0x004bd101;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd129:
    uVar8 = uVar8 + 1;
  } while ((int)uVar8 < 0x5dd);
  uVar8 = 0x13ec;
  iStack_8 = 0x20;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 - 100;
    if (uVar6 <= uVar2) {
LAB_004bd152:
      if (uVar6 != uVar2) goto code_r0x004bd154;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd17c:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd18b:
      if (uVar2 != uVar8) goto code_r0x004bd18d;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd1b5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 200;
    if (uVar6 <= uVar2) {
LAB_004bd1ca:
      if (uVar6 != uVar2) goto code_r0x004bd1cc;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd1f5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 0xb54;
    if (uVar6 <= uVar2) {
LAB_004bd20a:
      if (uVar6 != uVar2) goto code_r0x004bd20c;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd235:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 0x640;
    if (uVar6 <= uVar2) {
LAB_004bd24a:
      if (uVar6 != uVar2) goto code_r0x004bd24c;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd275:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 0xc1c;
    if (uVar6 <= uVar2) {
LAB_004bd28a:
      if (uVar6 != uVar2) goto code_r0x004bd28c;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd2b5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 0xc80;
    if (uVar6 <= uVar2) {
LAB_004bd2ca:
      if (uVar6 != uVar2) goto code_r0x004bd2cc;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd2f5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    uVar6 = 0x17d3 - (uVar8 - 0x13ec);
    if (uVar2 <= uVar6) {
LAB_004bd312:
      if (uVar2 != uVar6) goto code_r0x004bd314;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd33c:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    uVar6 = 0x1a8f - (uVar8 - 0x13ec);
    if (uVar2 <= uVar6) {
LAB_004bd353:
      if (uVar2 != uVar6) goto code_r0x004bd355;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd37d:
    uVar8 = uVar8 + 1;
    iStack_8 = iStack_8 + -1;
  } while (iStack_8 != 0);
  uVar8 = 0x17d4;
  iVar7 = 0x40;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 - 100;
    if (uVar6 <= uVar2) {
LAB_004bd3b2:
      if (uVar6 != uVar2) goto code_r0x004bd3b4;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd3dc:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd3eb:
      if (uVar2 != uVar8) goto code_r0x004bd3ed;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd415:
    uVar8 = uVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  uVar8 = 0xc1c;
  iVar7 = 4;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 - 100;
    if (uVar6 <= uVar2) {
LAB_004bd435:
      if (uVar6 != uVar2) goto code_r0x004bd437;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd465:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd474:
      if (uVar2 != uVar8) goto code_r0x004bd476;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd4a5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 100;
    if (uVar6 <= uVar2) {
LAB_004bd4b7:
      if (uVar6 != uVar2) goto code_r0x004bd4b9;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd4e5:
    uVar8 = uVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  uVar8 = 0x189c;
  iVar7 = 5;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 - 100;
    if (uVar6 <= uVar2) {
LAB_004bd512:
      if (uVar6 != uVar2) goto code_r0x004bd514;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd53c:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd54b:
      if (uVar2 != uVar8) goto code_r0x004bd54d;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd575:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 100;
    if (uVar6 <= uVar2) {
LAB_004bd587:
      if (uVar6 != uVar2) goto code_r0x004bd589;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd5b5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 200;
    if (uVar6 <= uVar2) {
LAB_004bd5ca:
      if (uVar6 != uVar2) goto code_r0x004bd5cc;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd5f5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 0x708;
    if (uVar6 <= uVar2) {
LAB_004bd60a:
      if (uVar6 != uVar2) goto code_r0x004bd60c;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd635:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 + 300;
    if (uVar6 <= uVar2) {
LAB_004bd64a:
      if (uVar6 != uVar2) goto code_r0x004bd64c;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd675:
    uVar8 = uVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  uVar8 = 300000;
  iVar7 = 8;
  do {
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar6 = puVar10[1];
    uVar2 = uVar8 - 100000;
    if (uVar6 <= uVar2) {
LAB_004bd6a5:
      if (uVar6 != uVar2) goto code_r0x004bd6a7;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd6d5:
    puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar2 = puVar10[1];
    if (uVar2 <= uVar8) {
LAB_004bd6e4:
      if (uVar2 != uVar8) goto code_r0x004bd6e6;
      puVar3 = (undefined4 *)puVar10[4];
      while (puVar3 != puVar10) {
        puVar4 = (undefined4 *)*puVar3;
        puVar3 = (undefined4 *)puVar3[4];
        (*(code *)*puVar4)(1);
      }
      puVar10[3] = puVar10;
      puVar10[4] = puVar10;
    }
LAB_004bd715:
    uVar8 = uVar8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  puVar10 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar8 = puVar10[1];
  while( true ) {
    if (0x1e14 < uVar8) goto LAB_004bd75c;
    if (uVar8 == 0x1e14) break;
    puVar10 = (undefined4 *)puVar10[7];
    uVar8 = puVar10[1];
  }
  puVar3 = (undefined4 *)puVar10[4];
  while (puVar3 != puVar10) {
    puVar4 = (undefined4 *)*puVar3;
    puVar3 = (undefined4 *)puVar3[4];
    (*(code *)*puVar4)(1);
  }
  puVar10[3] = puVar10;
  puVar10[4] = puVar10;
LAB_004bd75c:
  iVar7 = g_clientContext;
  piVar9 = (int *)(&DAT_0067ec70 + g_clientContext);
  iVar11 = 0;
  if (0 < *(int *)(&DAT_0067ec70 + g_clientContext)) {
    do {
      FUN_00401650((int *)((char *)piVar9 + 0x20004 + iVar11 * 0x18));
      iVar11 = iVar11 + 1;
    } while (iVar11 < *piVar9);
  }
  *piVar9 = 0;
  puVar10 = (undefined4 *)(&DAT_0067ec74 + iVar7);
  for (iVar11 = 0x8000; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  puVar10 = (undefined4 *)(&DAT_0069ec74 + iVar7);
  for (iVar11 = 0x1800; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  FUN_004e4220(&DAT_006a7708 + g_clientContext);
  FUN_004f3060(&DAT_006a7f88 + g_clientContext);
  _DAT_00e98abc = timeGetTime();
  iVar7 = g_clientContext;
  DAT_00e98ab8 = 0;
  puVar10 = &DAT_00e98ac0;
  for (iVar11 = 0x400; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  iVar7 = *(int *)(&DAT_006a64b4 + iVar7);
  if (iVar7 != -1) {
    if ((DAT_00793549 != '\0') &&
       ((**(code **)(**(int **)(DAT_00793554 + iVar7 * 4) + 0xc))(), iVar7 == 0)) {
      DAT_00793568 = 0;
    }
    *(undefined4 *)(&DAT_006a64b4 + g_clientContext) = 0xffffffff;
  }
  DAT_00e9b80a = 0;
  *(undefined1 *)(param_1 + 0x11d0) = 0;
  *(undefined4 *)(param_1 + 0x11d4) = 0xffffffff;
  cVar1 = *(char *)((int)*(int **)(DAT_00e9af14 + 4) + 0xf);
  DAT_00793634 = 0;
  piVar9 = *(int **)(DAT_00e9af14 + 4);
  while (cVar1 == '\0') {
    FUN_004e8ad0(piVar9[2]);
    piVar5 = (int *)*piVar9;
    _free(piVar9);
    piVar9 = piVar5;
    cVar1 = *(char *)((int)piVar5 + 0xf);
  }
  *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
  _DAT_00e9af18 = 0;
  *(int *)DAT_00e9af14 = DAT_00e9af14;
  *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
  return;
code_r0x004bcd26:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (7000 < uVar8) goto LAB_004bcd55;
  goto LAB_004bcd24;
code_r0x004bcd69:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x1b59 < uVar8) goto LAB_004bcd95;
  goto LAB_004bcd67;
code_r0x004bcda9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x1b5a < uVar8) goto LAB_004bcdd5;
  goto LAB_004bcda7;
code_r0x004bcde9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x1bbc < uVar8) goto LAB_004bce15;
  goto LAB_004bcde7;
code_r0x004bce29:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (9000 < uVar8) goto LAB_004bce55;
  goto LAB_004bce27;
code_r0x004bce69:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2329 < uVar8) goto LAB_004bce95;
  goto LAB_004bce67;
code_r0x004bcea9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x1900 < uVar8) goto LAB_004bced5;
  goto LAB_004bcea7;
code_r0x004bcee9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (10000 < uVar8) goto LAB_004bcf15;
  goto LAB_004bcee7;
code_r0x004bcf29:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2711 < uVar8) goto LAB_004bcf55;
  goto LAB_004bcf27;
code_r0x004bcf69:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2712 < uVar8) goto LAB_004bcf95;
  goto LAB_004bcf67;
code_r0x004bcfa9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2713 < uVar8) goto LAB_004bcfd5;
  goto LAB_004bcfa7;
code_r0x004bcfe9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2714 < uVar8) goto LAB_004bd015;
  goto LAB_004bcfe7;
code_r0x004bd029:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2715 < uVar8) goto LAB_004bd055;
  goto LAB_004bd027;
code_r0x004bd069:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2716 < uVar8) goto LAB_004bd095;
  goto LAB_004bd067;
code_r0x004bd0a9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar8 = puVar10[1];
  if (0x2719 < uVar8) goto LAB_004bd0d5;
  goto LAB_004bd0a7;
code_r0x004bd101:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd129;
  goto LAB_004bd0ff;
code_r0x004bd154:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd17c;
  goto LAB_004bd152;
code_r0x004bd18d:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd1b5;
  goto LAB_004bd18b;
code_r0x004bd1cc:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd1f5;
  goto LAB_004bd1ca;
code_r0x004bd20c:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd235;
  goto LAB_004bd20a;
code_r0x004bd24c:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd275;
  goto LAB_004bd24a;
code_r0x004bd28c:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd2b5;
  goto LAB_004bd28a;
code_r0x004bd2cc:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd2f5;
  goto LAB_004bd2ca;
code_r0x004bd314:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar6 < uVar2) goto LAB_004bd33c;
  goto LAB_004bd312;
code_r0x004bd355:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar6 < uVar2) goto LAB_004bd37d;
  goto LAB_004bd353;
code_r0x004bd3b4:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd3dc;
  goto LAB_004bd3b2;
code_r0x004bd3ed:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd415;
  goto LAB_004bd3eb;
code_r0x004bd437:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd465;
  goto LAB_004bd435;
code_r0x004bd476:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd4a5;
  goto LAB_004bd474;
code_r0x004bd4b9:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd4e5;
  goto LAB_004bd4b7;
code_r0x004bd514:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd53c;
  goto LAB_004bd512;
code_r0x004bd54d:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd575;
  goto LAB_004bd54b;
code_r0x004bd589:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd5b5;
  goto LAB_004bd587;
code_r0x004bd5cc:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd5f5;
  goto LAB_004bd5ca;
code_r0x004bd60c:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd635;
  goto LAB_004bd60a;
code_r0x004bd64c:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd675;
  goto LAB_004bd64a;
code_r0x004bd6a7:
  puVar10 = (undefined4 *)puVar10[7];
  uVar6 = puVar10[1];
  if (uVar2 < uVar6) goto LAB_004bd6d5;
  goto LAB_004bd6a5;
code_r0x004bd6e6:
  puVar10 = (undefined4 *)puVar10[7];
  uVar2 = puVar10[1];
  if (uVar8 < uVar2) goto LAB_004bd715;
  goto LAB_004bd6e4;
}

