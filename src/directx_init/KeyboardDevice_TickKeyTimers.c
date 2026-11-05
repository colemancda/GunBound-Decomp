/* KeyboardDevice_TickKeyTimers - 0x004ee0d0 in the original binary.
 * (FUN_004ee0d0 below is KeyboardDevice_TickKeyTimers.)
 * (FUN_004edd70 below is KeyboardDevice_Initialize.)
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): slot 9 of the keyboard vtable 0x55745c,
 * called once per elapsed tick from GameTick on the keyboard singleton
 * 0xe52810 (the mouse singleton gets MouseDevice_TickButtonTimers in the
 * same slot of its own vtable). The 256 dwords from obj+0x258 are the same
 * zero-filled 0x100-dword array KeyboardDevice_Construct clears (rep stosd
 * at 0x4edd50..0x4edd68), one per DIK scancode. LIKELY, not certain: that
 * these are per-key held-time counters rather than some other per-key
 * state is inferred from the decrement-to-zero shape and the array size,
 * not from a named reader.
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


void __fastcall KeyboardDevice_TickKeyTimers(int param_1)

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

