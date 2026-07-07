/* State01_Title_OnExit - 0x004e53b0 in the original binary.
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


void State01_Title_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar4[1];
  if (uVar1 < 0x2711) {
    while (uVar1 != 10000) {
      puVar4 = (undefined4 *)puVar4[7];
      uVar1 = puVar4[1];
      if (10000 < uVar1) {
        return;
      }
    }
    puVar2 = (undefined4 *)puVar4[4];
    while (puVar2 != puVar4) {
      puVar3 = (undefined4 *)*puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(code *)*puVar3)(1);
    }
    puVar4[3] = puVar4;
    puVar4[4] = puVar4;
  }
  return;
}

