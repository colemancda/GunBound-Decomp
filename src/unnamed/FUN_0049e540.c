/* FUN_0049e540 - 0x0049e540 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_0049e540(undefined4 *param_1)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053c03a) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  InitProjectile(param_1,0x186a2);
  local_4 = 0;
  *param_1 = &PTR_FUN_0055649c;
  *(undefined1 *)(param_1 + 0x1071) = 0;
  param_1[0xfee] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x49e56d
   * (`lea edi,[esi+0x3fa4]`, esi = this file's own param_1) a CValueGuard
   * cell at param_1+0x3fa4; tableHandle(+0x14) = param_1+0x3fb8 =
   * param_1[0xfee] (undefined4 units), matching the zero-write above. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x3fa4, 0);
  *(undefined1 *)(param_1 + 0xfe8) = 0;
  param_1[0xfe7] = 0xffffffff;
  return param_1;
}

