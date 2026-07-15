/* FUN_00428550 - 0x00428550 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_00428550(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005380ab;
  *unaff_FS_OFFSET = &local_c;
  InitGuardedBool();
  *(undefined1 *)(param_1 + 0x228) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x428582
   * (`lea edi,[esi + 8]`, esi = this file's own param_1): cell is
   * param_1+8; tableHandle(+0x14)=param_1+0x1c is zeroed on the line
   * above. `param_1` is plain `int`, so byte offsets add directly. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 8, 0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x44c) = 0;
  *(undefined4 *)(param_1 + 0x240) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42859b
   * (`lea edi,[esi + 0x22c]`, esi = param_1): cell is param_1+0x22c;
   * tableHandle(+0x14)=param_1+0x240 is zeroed on the line above. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0x22c, 0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

