/* BuildSystemInfoBlob - 0x0040d260 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BuildSystemInfoBlob(undefined4 *param_1)

{
  undefined4 *unaff_ESI;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c [8];
  undefined1 local_20c [520];
  undefined1 local_4;
  
  local_4 = 0;
  FUN_004f48b0(2);
  FUN_004f5e10(&local_24c,local_20c);
  FUN_004f5e10(&local_23c,local_20c);
  FUN_004f5e10(local_22c,local_20c);
  *param_1 = local_24c;
  param_1[1] = local_248;
  param_1[2] = local_244;
  param_1[3] = local_240;
  *(undefined1 *)(param_1 + 4) = 0;
  *unaff_ESI = local_23c;
  unaff_ESI[1] = local_238;
  unaff_ESI[2] = local_234;
  unaff_ESI[3] = local_230;
  unaff_ESI[4] = local_22c[0];
  *(undefined1 *)(unaff_ESI + 5) = 0;
  return;
}

