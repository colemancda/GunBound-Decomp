/* State10_Loading_OnExit - 0x0043eff0 in the original binary.
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


void State10_Loading_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  if (uVar1 < 0x2711) {
LAB_0043f004:
    if (uVar1 != 10000) goto code_r0x0043f006;
    puVar2 = (undefined4 *)puVar5[4];
    while (puVar2 != puVar5) {
      puVar3 = (undefined4 *)*puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(code *)*puVar3)(1);
    }
    puVar5[3] = puVar5;
    puVar5[4] = puVar5;
  }
LAB_0043f035:
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (0x2711 < uVar1) goto LAB_0043f075;
    if (uVar1 == 0x2711) break;
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
LAB_0043f075:
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (0x2712 < uVar1) {
      *(undefined4 *)(DAT_005b3484 + 0x621e4) = 0;
      return;
    }
    if (uVar1 == 0x2712) break;
    puVar5 = (undefined4 *)puVar5[7];
    uVar1 = puVar5[1];
  }
  puVar2 = (undefined4 *)puVar5[4];
  iVar4 = DAT_005b3484;
  while (DAT_005b3484 = iVar4, puVar2 != puVar5) {
    puVar3 = (undefined4 *)*puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(code *)*puVar3)(1);
    iVar4 = DAT_005b3484;
  }
  puVar5[3] = puVar5;
  puVar5[4] = puVar5;
  *(undefined4 *)(iVar4 + 0x621e4) = 0;
  return;
code_r0x0043f006:
  puVar5 = (undefined4 *)puVar5[7];
  uVar1 = puVar5[1];
  if (10000 < uVar1) goto LAB_0043f035;
  goto LAB_0043f004;
}

