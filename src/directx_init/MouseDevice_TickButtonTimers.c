/* MouseDevice_TickButtonTimers - 0x004ee540 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): slot 9 of the mouse vtable 0x557484, called
 * once per elapsed tick from GameTick on the mouse singleton 0xe53698
 * (keyboard singleton: KeyboardDevice_TickKeyTimers, same slot of its own
 * vtable). The eight dwords at obj+0x68..+0x84 are the per-button words
 * MouseDevice_Poll reads and writes (obj + 0x68 + button * 4, where button
 * = buffered object offset - 0xc, range 0..7). LIKELY, not certain: that
 * these are click or hold timers is inferred from MouseDevice_Poll's use
 * of the same words and the decrement-to-zero shape, not from a named
 * reader.
 */
#include "ghidra_types.h"


void __fastcall MouseDevice_TickButtonTimers(int param_1)

{
  if (*(int *)(param_1 + 0x68) != 0) {
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + -1;
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + -1;
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + -1;
  }
  if (*(int *)(param_1 + 0x74) != 0) {
    *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + -1;
  }
  if (*(int *)(param_1 + 0x78) != 0) {
    *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + -1;
  }
  if (*(int *)(param_1 + 0x7c) != 0) {
    *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + -1;
  }
  if (*(int *)(param_1 + 0x80) != 0) {
    *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + -1;
  }
  if (*(int *)(param_1 + 0x84) != 0) {
    *(int *)(param_1 + 0x84) = *(int *)(param_1 + 0x84) + -1;
  }
  return;
}

