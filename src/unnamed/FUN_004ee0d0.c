/* FUN_004ee0d0 - 0x004ee0d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT: GameTick.c's call site (0x41334f) called
 * this with zero args, and include/functions.h declared it as
 * `void __fastcall FUN_004ee0d0();` - but this function reads a real
 * ECX-passed argument (param_1, a struct base pointer decremented at
 * offsets -0x4/0/0x4/0x8 relative to +0x25c). The original disassembly
 * at 0x41334a-0x41334f shows `mov ecx, 0xe52810` immediately before the
 * `call 0x4ee0d0` - a fixed global struct address, same one used by
 * FUN_004edd70's ECX (see that file's header comment). Fixed the
 * prototype and GameTick.c's call site to pass it explicitly. */
#include "ghidra_types.h"


void __fastcall FUN_004ee0d0(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + 0x25c);
  iVar2 = 0x40;
  do {
    if (piVar1[-1] != 0) {
      piVar1[-1] = piVar1[-1] + -1;
    }
    if (*piVar1 != 0) {
      *piVar1 = *piVar1 + -1;
    }
    if (piVar1[1] != 0) {
      piVar1[1] = piVar1[1] + -1;
    }
    if (piVar1[2] != 0) {
      piVar1[2] = piVar1[2] + -1;
    }
    piVar1 = piVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}

