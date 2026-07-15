/* FUN_004ac5a0 - 0x004ac5a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004ac5a0(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537d41;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 500;
  param_1[2] = 0xffffffff;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 0;
  param_1[6] = 0xffffffff;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[9] = 0xffffffff;
  local_4 = 0;
  *param_1 = &PTR_FUN_005565e4;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac600
   * (`lea edi,[esi + 0x38]`, esi = this file's own param_1): the cell is
   * param_1+0x38; tableHandle(+0x14)=param_1+0x4c (== param_1[0x13],
   * `undefined4 *` scales by 4) is zeroed immediately above. `param_1` is
   * `undefined4 *`, so byte offsets use `(int)param_1 + N`. Matches the
   * identical constructor idiom in FUN_00471320.c. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac61a
   * (`lea edi,[esi + 0x25c]`, esi = param_1): cell is param_1+0x25c;
   * tableHandle(+0x14)=param_1+0x270 (== param_1[0x9c]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  *(undefined1 *)(param_1 + 0x1a9) = 0;
  param_1[0x126] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac634
   * (`lea edi,[esi + 0x484]`, esi = param_1): cell is param_1+0x484;
   * tableHandle(+0x14)=param_1+0x498 (== param_1[0x126]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x484, 0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

