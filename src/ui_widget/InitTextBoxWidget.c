/* InitTextBoxWidget - 0x0040c980 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_0040c980).  Constructor for the multi-line TEXT
 * BOX active object.  Evidence:
 *   - it installs vtable 0x55208c (the flat 5-slot active-object ABI:
 *     DeletePoisonedBaseObject / ResolveNamedState / NoOpMethod / draw /
 *     NoOpMethod) and zeroes a 0x100-dword = 0x400-byte buffer at +0x48.
 *   - its draw slot (0x40ca20) reads +0x38/+0x3c as the origin and
 *     +0x40/+0x44 as the extents (x2 = +0x40 + +0x38, y2 = +0x44 + +0x3c),
 *     then walks the NUL-terminated string at +0x48 counting characters and
 *     splitting it into lines - a word-wrapping text renderer.
 *   - both call sites (FUN_00445450) do operator_new(0x458), call this, then
 *     RegisterActiveObject, immediately after the store window's
 *     "b_storewindow_cancel"/"b_storewindow_confirm" buttons - and pass the
 *     same x (0xf2) those buttons use.
 * So the object is: +0x38 x, +0x3c y, +0x40 w, +0x44 h, +0x48 text[0x400].
 *
 * ABI, and the 2026-08-19 fix.  The original takes THREE register arguments:
 * ECX (param_1, stored to +0x8), EDX (param_2, the object itself) and EAX
 * (stored to +0x4 - the layer key, 10000 at both call sites), plus ret 0x18
 * = 6 stack arguments.  Both callers passed only the 6, so param_2 - the
 * object every field write goes through - held whatever was left in EDX:
 * `param_2[2] = param_1` was a wild store, on the avatar-store window path.
 * ECX and EDX are expressible under MSVC __fastcall and are now passed
 * normally.  EAX is NOT expressible, so Ghidra's `in_EAX` has been promoted
 * to a real trailing parameter (param_9) and the callers pass 10000 there:
 * the rebuild is self-consistent (it becomes ret 0x1c) at the cost of that
 * one argument no longer sitting where the original put it.  Recovered from
 * orig 0x446489-0x4464b4 and 0x4464cf-0x446500:
 *     push 0x458 / call operator_new / mov edx,eax   <- EDX = the object
 *     push 0 / 0xc / 0xc / 0x49 / 0x112 / 0xf2       <- params 8..3
 *     xor ecx,ecx  (site 2: mov ecx,1)               <- ECX = param_1
 *     mov eax,0x2710                                 <- EAX = the layer key
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 * __fastcall
InitTextBoxWidget(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
            undefined4 param_9)

{
  int iVar1;
  undefined4 *puVar2;
  
  param_2[2] = param_1;
  param_2[6] = 0xffffffff;
  param_2[9] = 0xffffffff;
  param_2[0xe] = param_3;
  param_2[0xf] = param_4;
  param_2[0x10] = param_5;
  param_2[0x11] = param_6;
  param_2[0x113] = param_7;
  param_2[1] = param_9;
  param_2[0x114] = param_8;
  param_2[3] = 0;
  param_2[4] = 0;
  *(undefined1 *)(param_2 + 5) = 0;
  *(undefined1 *)((int)param_2 + 0x15) = 0;
  param_2[7] = 0;
  *(undefined1 *)(param_2 + 8) = 0;
  param_2[10] = 0;
  param_2[0xb] = 0;
  param_2[0x112] = 0;
  param_2[0x115] = 0;
  *param_2 = &PTR_FUN_0055208c;
  puVar2 = param_2 + 0x12;
  for (iVar1 = 0x100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return param_2;
}

