/* KeyboardDevice_Initialize - 0x004edd70 in the original binary.
 * (FUN_004edd70 below is KeyboardDevice_Initialize.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body, read from the binary at 0x4edd70):
 * IDirectInput8 (global 0x674f68) vtbl+0xc CreateDevice with the GUID at
 * obj+8 and the device pointer stored at obj+4; device vtbl+0x2c
 * SetDataFormat with 0x54b420, a DIDATAFORMAT whose dwNumObjs is 256 and
 * dwDataSize 0x100 (c_dfDIKeyboard); vtbl+0x34 SetCooperativeLevel(hwnd, 6
 * = NONEXCLUSIVE|FOREGROUND); vtbl+0x18 SetProperty(DIPROP_BUFFERSIZE,
 * 0x40); vtbl+0x1c Acquire; then the flag at obj+0x54 is set. It occupies
 * slot 1 of the keyboard vtable 0x55745c (the mouse vtable 0x557484 has
 * MouseDevice_Initialize there), and InitGame calls it with ECX = 0xe52810
 * (0x40ecb0).
 *
 * Calling convention (0x40ecae..0x40ecb5): `push ebp` (the window handle,
 * InitGame's param_1), `mov ecx,0xe52810`, `call 0x4edd70`; the function ends
 * `ret 4`. So ECX = the singleton, hWnd is the one stack argument; written
 * __fastcall with a dummy EDX slot, the idiom for genuine C++ callees.
 *
 * The port body is a bring-up stub returning 0; see the workaround comment
 * below.
 */
#include "ghidra_types.h"


undefined4 __fastcall KeyboardDevice_Initialize(void *thisPtr,int dummyEdx,undefined4 hWnd)

{
  /* BRING-UP WORKAROUND: skip DirectInput keyboard-device acquisition.
   *
   * Ghidra's decompile at THIS call site is unusable as-is: InitGame.c calls
   * FUN_004edd70(param_1) passing its OWN param_1 (the window handle), but
   * the original disassembly (0x40ecb0-0x40ecb5) shows the real caller
   * loads ECX with a FIXED GLOBAL STRUCT ADDRESS (0xe52810) instead - Ghidra
   * gave both unrelated values the same "param_1" name. That struct's field
   * at +8 holds a REFGUID (recovered as an argument to
   * IDirectInput8::CreateDevice at vtbl+0xc, per 0x4edd7e-0x4edd89) that in
   * turn needs its own runtime constructor (FUN_004edce0 called from
   * WinMain-level startup, 0x4100ab/0x4100b0) to populate correctly, and the
   * whole thing chains into more vtable calls (SetCooperativeLevel-style at
   * +0x2c, SetDataFormat-style at +0x34, SetProperty-style at +0x18) whose
   * struct layouts aren't recovered yet either.
   *
   * None of this blocks reaching the logo/menu states (they're 2-D sprite
   * blits; DirectInput device binding only matters once real keyboard/mouse
   * input needs processing), so skip it for bring-up. Revisit once the
   * 0xe52810 struct's real field layout is understood. */
  return 0;
}

