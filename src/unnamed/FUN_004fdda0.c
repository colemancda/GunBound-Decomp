/* FUN_004fdda0 - 0x004fdda0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004fdda0(void)

{
  int iVar1;
  int unaff_ESI;
  
  if ((*(SOCKET *)(unaff_ESI + 8) != 0xffffffff) &&
     (iVar1 = shutdown(*(SOCKET *)(unaff_ESI + 8),2), iVar1 != -1)) {
    return 1;
  }
  FUN_004fe6a0();
  return 1;
}

