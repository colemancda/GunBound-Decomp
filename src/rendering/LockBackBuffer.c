/* LockBackBuffer - 0x004f02c0 in the original binary.
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


undefined4 LockBackBuffer(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uStack_8c;
  undefined4 local_88 [4];
  undefined4 uStack_78;
  
  puVar2 = local_88;
  for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_88[0] = 0x7c;
  iVar1 = (**(code **)(*g_pBackBufferSurface + 100))(g_pBackBufferSurface,0,local_88,0,0);
  if (iVar1 < 0) {
    return 0;
  }
  *param_1 = uStack_78;
  *param_2 = uStack_8c;
  return 1;
}

