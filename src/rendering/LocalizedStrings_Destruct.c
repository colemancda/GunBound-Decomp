/* LocalizedStrings_Destruct - 0x004154e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004154e0 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: the destructor
 * registered with _atexit for g_localizedStringTable: the CRT stub at
 * 0x540ee0 pushes 0x5432e0, which loads EAX = 0x796eec and jumps to the
 * thunk at 0x40d170, which jumps here. It clears the tree through
 * LocalizedStrings_Clear and frees the nil sentinel at map+0x14, the exact
 * counterpart of what LocalizedStrings_BuyNode allocates.
 */
#include "ghidra_types.h"


void LocalizedStrings_Destruct(void)

{
  int in_EAX;
  
  LocalizedStrings_Clear((int *)in_EAX);
  if (*(void **)(in_EAX + 0x14) != (void *)0x0) {
    _free(*(void **)(in_EAX + 0x14));
  }
  return;
}

