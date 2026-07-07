/* FUN_004f0100 - 0x004f0100 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004f0100(void)

{
  char in_AL;
  
  if (DAT_00588f64 != in_AL) {
    DAT_00588f64 = in_AL;
    if (in_AL != '\0') {
      (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x28,1);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x10,5);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x11,3);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x10,5);
      (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x11,3);
      return;
    }
    (**(code **)(*g_pD3DDevice7 + 0x50))(g_pD3DDevice7,0x28,0);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x10,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,0,0x11,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x10,1);
    (**(code **)(*g_pD3DDevice7 + 0x94))(g_pD3DDevice7,1,0x11,1);
  }
  return;
}

