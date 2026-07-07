/* FUN_004ee540 - 0x004ee540 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_004ee540(int param_1)

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

