/* FUN_004e5a20 - 0x004e5a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e5a20(void)

{
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x22c) = 1;
  if (*(SOCKET *)(unaff_ESI + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(unaff_ESI + 0x24));
  }
  *(undefined4 *)(unaff_ESI + 0x24) = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x22a) = 0;
  return;
}

