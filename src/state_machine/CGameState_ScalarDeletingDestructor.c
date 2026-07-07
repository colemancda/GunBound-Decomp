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


/* param_2 is `int`, not `byte`: a K&R-declared (unspecified-args)
 * prior declaration in functions.h can't be defined with a
 * default-promoted parameter type (byte/short/float) - byte args are
 * promoted to int when passed anyway under cdecl/thiscall, so this
 * changes nothing about the actual calling convention. */
void * __thiscall CGameState_ScalarDeletingDestructor(void *param_1,int param_2)

{
  CGameState_BaseDestructor();
  if ((param_2 & 1) != 0) {
    _free(param_1);
  }
  return param_1;
}

