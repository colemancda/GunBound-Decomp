/* FUN_0050cdb0 - 0x0050cdb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): maps a point to a ROW INDEX in a
 * 14-row list: param_1 is the widget (x window at +0x28+0x14..+0xc3,
 * first row top at +0x2c+0x68, 0x11 pixels per row), param_2 the X, and
 * ESI - now regEsi - the Y; returns 0..13 or -1. Both call sites are
 * C++ ports carrying their own file-local K&R externs, both fixed:
 * FUN_0050a1b0 passes its own (x,y) mouse args, and FUN_0050a320 asks
 * which row sits at an in-bounds probe X of widget-left + 0x14 and the
 * incoming y (`mov edx,[ebp+0x28] / add edx,0x14` at 0x50a360, ebp =
 * this via `mov ebp,ecx` at 0x50a33d, ECX unwritten to the call).
 */
#include "ghidra_types.h"


int __fastcall FUN_0050cdb0(int param_1,int param_2,int regEsi)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI = regEsi;
  
  iVar2 = *(int *)(param_1 + 0x2c) + 0x68;
  if ((*(int *)(param_1 + 0x28) + 0x13 < param_2) && (param_2 < *(int *)(param_1 + 0x28) + 0xc3)) {
    iVar1 = 0;
    iVar3 = *(int *)(param_1 + 0x2c) + 0x79;
    do {
      if ((iVar2 < unaff_ESI) && (unaff_ESI < iVar3)) {
        return iVar1;
      }
      iVar2 = iVar2 + 0x11;
      iVar3 = iVar3 + 0x11;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0xe);
  }
  return -1;
}

