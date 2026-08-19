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
 * ABI CAVEAT: the object pointer is the SECOND parameter (EDX); ECX is
 * param_1 and EAX is a third register argument (`in_EAX`, stored to +0x4).
 * Both call sites pass only the 6 stack arguments, so today param_2 receives
 * a caller value rather than the new object - see the fastcall-decls audit.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 * __fastcall
InitTextBoxWidget(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_EAX;
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
  param_2[1] = in_EAX;
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

