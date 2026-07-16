/* FUN_004a6920 - 0x004a6920 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_004a6920(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537d93;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 0x1f7;
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
  *param_1 = &PTR_FUN_00556510;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a6980
   * (`lea edi,[esi + 0x38]`, esi = this file's own param_1): cell is
   * param_1+0x38; tableHandle(+0x14)=param_1+0x4c (== param_1[0x13],
   * `undefined4 *` scales by 4) is zeroed just above. `param_1` is
   * `undefined4 *`, so byte offsets use `(int)param_1 + N`. Matches the
   * identical constructor idiom in InitTornadoHazard.c/FUN_00481fb0.c. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4a699a
   * (`lea edi,[esi + 0x25c]`, esi = param_1): cell is param_1+0x25c;
   * tableHandle(+0x14)=param_1+0x270 (== param_1[0x9c]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  param_1[0x120] = 0;
  param_1[0x121] = 0xff;
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

