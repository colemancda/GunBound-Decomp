/* FUN_00543300 - 0x00543300 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * MAP ARGUMENT RECOVERED (2026-10-30): this is the atexit destructor that
 * FUN_00540f20 registers (`push 0x543300; call _atexit`, 0x540f2a) for
 * the global it has just constructed.  The body is `mov eax,0xe9bea8;
 * jmp 0x40d1b0` (0x543300/0x543305): EAX = &DAT_00e9bea8 (the 0x30-byte
 * ChooseEvent map, sized in globals_sized.c) handed to
 * thunk_FUN_00415600, which jumps to the map's RemoveAll.  The call
 * previously passed nothing, so the RemoveAll ran on an uninitialised
 * EAX at exit.
 */
#include "ghidra_types.h"


void FUN_00543300(void)

{
  thunk_FUN_00415600((int *)&DAT_00e9bea8);
  return;
}

