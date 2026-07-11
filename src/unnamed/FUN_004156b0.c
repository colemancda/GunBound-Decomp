/* FUN_004156b0 - 0x004156b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* __beginthread thread proc; receives the control-block pointer __beginthread
 * was given (see FUN_00415500.c) as its normal __cdecl argument and forwards
 * it to the wait loop. */
void FUN_004156b0(void *param_1)

{
  FUN_004157b0(param_1);
  return;
}

