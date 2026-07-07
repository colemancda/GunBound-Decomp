/* FUN_0044b720 - 0x0044b720 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044b720(undefined4 param_1)

{
  CreateButtonWidget(&DAT_00e9be90,0,0,1000,s_b_store_exit_00555778,0x232,0x226,0x6b,0x2d,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,1,0x3e9,s_b_store_buddygame_00555764,0x2a8,0x226,0x6b,0x2d,1,0)
  ;
  CreateButtonWidget(&DAT_00e9be90,0,10,0x44c,s_b_store_cap_00555758,0x23,0x22c,0x2a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xb,0x44d,s_b_store_cloth_00555748,0x58,0x22c,0x2a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xc,0x44e,s_b_store_glasse_00555738,0x8d,0x22c,0x2a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xd,0x44f,s_b_store_flag_00555728,0xc2,0x22c,0x2a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0xf,0x451,s_b_store_puton_00555708,0x167,0x22c,0x4a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0x10,0x452,s_b_store_buy_005556fc,0x1c0,0x22c,0x4a,0x1a,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0x11,0x453,s_b_store_up_005556f0,0x205,0x50,0x10,0x30,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0x12,0x454,s_b_store_down_005556e0,0x205,0x1e8,0x10,0x30,1,0);
  CreateButtonWidget(&DAT_00e9be90,0,0x3d,0x455,s_b_store_cashcharge_005556cc,0x1e5,7,0x37,0x2e,1,0)
  ;
  FUN_00449250(param_1,1,0);
  return;
}

