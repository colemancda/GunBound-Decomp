/* FUN_004e9520 - 0x004e9520 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e9520(void)

{
  int unaff_ESI;
  
  if (*(void **)(unaff_ESI + 0x10c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x10c));
  }
  *(undefined4 *)(unaff_ESI + 0x10c) = 0;
  if (*(void **)(unaff_ESI + 0x110) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x110));
  }
  *(undefined4 *)(unaff_ESI + 0x110) = 0;
  if (*(void **)(unaff_ESI + 0x118) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x118));
  }
  *(undefined4 *)(unaff_ESI + 0x118) = 0;
  if (*(void **)(unaff_ESI + 0x11c) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x11c));
  }
  *(undefined4 *)(unaff_ESI + 0x11c) = 0;
  if (*(void **)(unaff_ESI + 0x124) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x124));
  }
  *(undefined4 *)(unaff_ESI + 0x124) = 0;
  if (*(void **)(unaff_ESI + 0x128) != (void *)0x0) {
    _free(*(void **)(unaff_ESI + 0x128));
  }
  *(undefined4 *)(unaff_ESI + 0x128) = 0;
  return;
}

