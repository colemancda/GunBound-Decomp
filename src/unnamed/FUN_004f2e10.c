/* FUN_004f2e10 - 0x004f2e10 in the original binary.
 *
 * Base-destructor-shaped: matches the exact idiom already named in
 * CGameState_BaseDestructor.c (poisons `this`'s vtable pointer, no
 * other cleanup). No confirmed owning class - see FUN_004f2e20.c
 * (its ScalarDeletingDestructor-shaped caller) for the investigation
 * that ruled out identifying it via vtable neighbors.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004f2e10(undefined4 *param_1)

{
  *param_1 = &PTR_LAB_0055752c;
  return;
}

