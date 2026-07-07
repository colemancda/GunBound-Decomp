/* FUN_004edb50 - 0x004edb50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004edb50(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 in_EAX;
  
  DAT_00ea0e28 = (float)param_3 * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e2c = (float)param_4 * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e4c = (float)(param_3 + param_2) * _DAT_00557fc0 * _DAT_00588f50;
  DAT_00ea0e74 = (float)(param_4 + param_5) * _DAT_00557fbc * _DAT_00588f54;
  _DAT_00ea0e38 = in_EAX;
  _DAT_00ea0e50 = DAT_00ea0e2c;
  _DAT_00ea0e5c = in_EAX;
  DAT_00ea0e70 = _DAT_00ea0e4c;
  _DAT_00ea0e80 = in_EAX;
  _DAT_00ea0e94 = DAT_00ea0e28;
  _DAT_00ea0e98 = DAT_00ea0e74;
  _DAT_00ea0ea4 = in_EAX;
  (**(code **)(*g_pD3DDevice7 + 100))(g_pD3DDevice7,6,0x244,&DAT_00ea0e28,4,1);
  return;
}

