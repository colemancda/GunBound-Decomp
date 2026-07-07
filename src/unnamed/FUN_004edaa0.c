/* FUN_004edaa0 - 0x004edaa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004edaa0(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 in_EAX;
  
  DAT_00ea0e28 = (float)param_1 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e2c = (float)param_2 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e4c = (float)param_3 * _DAT_00557fc0 * _DAT_00588f50;
  _DAT_00ea0e50 = (float)param_4 * _DAT_00557fbc * _DAT_00588f54;
  DAT_00ea0e70 = (float)param_5 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e74 = (float)param_6 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e38 = in_EAX;
  _DAT_00ea0e5c = in_EAX;
  _DAT_00ea0e80 = in_EAX;
  (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,6,0x244,&DAT_00ea0e28,3,1);
  return;
}

