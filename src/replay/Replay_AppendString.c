/* Replay_AppendString - 0x004e6db0 in the original binary.
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


void __fastcall Replay_AppendString(undefined4 param_1,uint param_2,undefined4 *param_3)

{
  int in_EAX;
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar1 = ((int)param_2 < 0) - 1 & param_2;
  puVar3 = (undefined4 *)(*(int *)(in_EAX + 0x44fec) + 0x44dec + in_EAX);
  for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar3 = *param_3;
    param_3 = param_3 + 1;
    puVar3 = puVar3 + 1;
  }
  for (uVar1 = uVar1 & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined1 *)puVar3 = *(undefined1 *)param_3;
    param_3 = (undefined4 *)((int)param_3 + 1);
    puVar3 = (undefined4 *)((int)puVar3 + 1);
  }
  *(uint *)(in_EAX + 0x44fec) = *(int *)(in_EAX + 0x44fec) + param_2;
  return;
}

