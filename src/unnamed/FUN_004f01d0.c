/* FUN_004f01d0 - 0x004f01d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004f01d0(void)

{
  int in_EAX;
  
  if (DAT_00793614 != in_EAX) {
    _DAT_00792194 = in_EAX;
    DAT_00793614 = in_EAX;
    if ((in_EAX == 0) || (in_EAX == 1)) {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,6);
    }
    else if (in_EAX == 2) {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x13,5);
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x14,2);
      return;
    }
  }
  return;
}

