/* FUN_0042aeb0 - 0x0042aeb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined2 * FUN_0042aeb0(undefined2 *param_1,undefined2 *param_2)

{
  undefined4 uVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005380ab) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = *param_2;
  *(undefined1 *)(param_1 + 1) = *(undefined1 *)(param_2 + 1);
  *(undefined4 *)(param_1 + 2) = *(undefined4 *)(param_2 + 2);
  *(undefined1 *)(param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  uVar1 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42aefe
   * (`lea edi,[esi + 8]`, esi = this file's own param_1): cell is
   * param_1+8; tableHandle(+0x14)=param_1+0x1c (== `param_1 + 0xe` above,
   * `undefined2 *` scales by 2) is zeroed just above. `param_1` is
   * `undefined2 *`, so byte offsets use `(int)param_1 + N`. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 8, uVar1);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x226) = 0;
  *(undefined4 *)(param_1 + 0x120) = 0;
  uVar1 = PeekPacketChecksumState();
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42af22
   * (`lea edi,[esi + 0x22c]`, esi = param_1): cell is param_1+0x22c;
   * tableHandle(+0x14)=param_1+0x240 (== `param_1 + 0x120` above) is
   * zeroed just above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x22c, uVar1);
  return param_1;
}

