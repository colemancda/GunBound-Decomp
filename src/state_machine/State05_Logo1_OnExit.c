/* State05_Logo1_OnExit - 0x00443430 in the original binary.
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


void State05_Logo1_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (10000 < uVar1) goto LAB_00443475;
    if (uVar1 == 10000) break;
    puVar5 = (undefined4 *)puVar5[7];
    uVar1 = puVar5[1];
  }
  puVar2 = (undefined4 *)puVar5[4];
  while (puVar2 != puVar5) {
    puVar3 = (undefined4 *)*puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(code *)*puVar3)(1);
  }
  puVar5[3] = puVar5;
  puVar5[4] = puVar5;
LAB_00443475:
  FUN_0040d260(&uStack_2c);
  puVar4 = DAT_007934f4;
  if (DAT_007934f4 != (undefined2 *)0x0) {
    /* DAT_007934f4[1] in the original: rewritten through puVar4 (same
     * value, cast to undefined2* two lines up) since the global itself
     * is declared uint32_t - it's used as a plain integer/address in
     * ~30 other files, so retyping it as a pointer isn't worth the
     * cross-file risk for this one subscript. */
    puVar4[1] = 0xa000;
    *(undefined4 *)(puVar4 + 0x1000) = 4;
    *(undefined4 *)(puVar4 + 2) = 1;
    iVar6 = *(int *)(puVar4 + 0x1000);
    *(int *)(puVar4 + 0x1000) = iVar6 + 4;
    puVar5 = (undefined4 *)(iVar6 + 4 + (int)puVar4);
    *puVar5 = uStack_2c;
    puVar5[1] = uStack_28;
    puVar5[2] = uStack_24;
    puVar5[3] = uStack_20;
    iVar6 = *(int *)(puVar4 + 0x1000);
    *(int *)(puVar4 + 0x1000) = iVar6 + 0x10;
    puVar5 = (undefined4 *)(iVar6 + 0x10 + (int)puVar4);
    *puVar5 = uStack_18;
    puVar5[1] = uStack_14;
    puVar5[2] = uStack_10;
    puVar5[3] = uStack_c;
    puVar5[4] = uStack_8;
    iVar6 = *(int *)(puVar4 + 0x1000) + 0x14;
    *(int *)(puVar4 + 0x1000) = iVar6;
    *puVar4 = (short)iVar6;
    FUN_004e5ac0(*(undefined4 *)(puVar4 + 0x1002),iVar6);
  }
  return;
}

