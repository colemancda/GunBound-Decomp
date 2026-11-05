/* LocalizedStrings_DestructThunk - 0x0040d170 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040d170 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: the one-
 * instruction jmp thunk at 0x40d170 (jmp 0x4154e0) that the atexit stub at
 * 0x5432e0 (mov eax,0x796eec / jmp 0x40d170) reaches. Ghidra duplicated
 * the target body into this file as thunk_FUN_004154e0; the binary
 * function is only the jump, so it is named after its target,
 * LocalizedStrings_Destruct, with the same Thunk suffix the tree uses for
 * CString_DestructThunk.
 */
#include "ghidra_types.h"


void LocalizedStrings_DestructThunk(void)

{
  int in_EAX;
  
  LocalizedStrings_Clear((int *)in_EAX);
  if (*(void **)(in_EAX + 0x14) != (void *)0x0) {
    _free(*(void **)(in_EAX + 0x14));
  }
  return;
}

