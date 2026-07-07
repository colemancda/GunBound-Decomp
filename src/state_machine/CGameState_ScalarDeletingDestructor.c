/* CGameState_ScalarDeletingDestructor - 0x004e5320 in the original binary.
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


void * __thiscall CGameState_ScalarDeletingDestructor(void *param_1,byte param_2)

{
  CGameState_BaseDestructor();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

