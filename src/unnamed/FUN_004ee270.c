/* FUN_004ee270 - 0x004ee270 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_004ee270(int param_1)

{
  /* BRING-UP WORKAROUND: skip DirectInput mouse-device acquisition.
   *
   * Same situation as FUN_004edd70 (the keyboard counterpart, called right
   * before this in InitGame) - Ghidra gave the real caller's fixed global
   * struct address (0xe53698, per orig 0x40ecbb) the same "param_1" name as
   * InitGame's own window-handle parameter, and the struct's field layout
   * (REFGUID at +8, populated by a separate runtime constructor) isn't
   * recovered yet. Not required to reach the logo/menu states; see
   * FUN_004edd70.c for the full writeup. */
  return 0;
}

