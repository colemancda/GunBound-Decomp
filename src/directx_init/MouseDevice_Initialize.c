/* MouseDevice_Initialize - 0x004ee270 in the original binary.
 * (FUN_004edd70 below is KeyboardDevice_Initialize.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body, read from the binary at 0x4ee270): the same
 * CreateDevice / SetDataFormat / SetCooperativeLevel(6) /
 * SetProperty(buffer size 0x40) / Acquire sequence as
 * KeyboardDevice_Initialize, but with 0x54b438, a DIDATAFORMAT of 16-byte
 * objects, 7 of them, 16 bytes of data (c_dfDIMouse). It sits in slot 1 of
 * the mouse vtable 0x557484, and InitGame calls it on the mouse singleton
 * 0xe53698 (0x40ecbb).
 *
 * Calling convention (0x40ecba..0x40ecc0): `push ebp` (hWnd), `mov ecx,
 * 0xe53698`, `call 0x4ee270`; the function ends `ret 4` (0x4ee2f6). ECX =
 * the singleton, hWnd on the stack: __fastcall with a dummy EDX slot.
 *
 * The port body is a bring-up stub returning 0; see the workaround comment
 * below.
 */
#include "ghidra_types.h"


undefined4 __fastcall MouseDevice_Initialize(void *thisPtr,int dummyEdx,undefined4 hWnd)

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

