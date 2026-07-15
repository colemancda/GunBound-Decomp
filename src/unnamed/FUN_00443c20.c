/* FUN_00443c20 - 0x00443c20 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * FUN_00443c20(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053add9;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  *param_1 = &vtable_State07_AvatarStore;
  *(undefined1 *)(param_1 + 0x89) = 0;
  param_1[6] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x443c55
   * (`lea edi,[esi+4]` at 0x443c42, esi = this file's own param_1) the
   * cell is (int)param_1+4; tableHandle(+0x14)=param_1+0x18=param_1[6],
   * activeFlag(+0x220)=param_1 byte 0x224=*(undefined1*)(param_1+0x89) -
   * both match the zero-writes immediately above. `param_1` is
   * `undefined4 *` (scales by 4), so the byte offset is taken via `(int)
   * param_1 + N`. Same evidence pattern for all 6 cells below. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 4, 0);
  local_4 = 1;
  *(undefined1 *)(param_1 + 0x112) = 0;
  param_1[0x8f] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443c6f
   * (`lea edi,[esi+0x228]`); tableHandle=param_1[0x8f],
   * activeFlag=*(undefined1*)(param_1+0x112), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x228, 0);
  local_4 = 2;
  _eh_vector_constructor_iterator_(param_1 + 0x116,0x17e4,9,FUN_00425350,FUN_004254a0);
  local_4 = 3;
  _eh_vector_constructor_iterator_(param_1 + 0x36d7,0x17e4,0x15,FUN_00425350,FUN_004254a0);
  local_4 = 4;
  *(undefined1 *)(param_1 + 0xc1db) = 0;
  param_1[0xc158] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443ccd
   * (`lea edi,[esi+0x3054c]`); tableHandle=param_1[0xc158],
   * activeFlag=*(undefined1*)(param_1+0xc1db), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x3054c, 0);
  local_4 = 5;
  *(undefined1 *)(param_1 + 0xc264) = 0;
  param_1[0xc1e1] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443ce7
   * (`lea edi,[esi+0x30770]`); tableHandle=param_1[0xc1e1],
   * activeFlag=*(undefined1*)(param_1+0xc264), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x30770, 0);
  local_4 = 6;
  *(undefined1 *)(param_1 + 0xc2ed) = 0;
  param_1[0xc26a] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443d01
   * (`lea edi,[esi+0x30994]`); tableHandle=param_1[0xc26a],
   * activeFlag=*(undefined1*)(param_1+0xc2ed), matching above. */
  EncodeOutgoingPacketField((int)param_1 + 0x30994, 0);
  local_4 = 7;
  FUN_0044fb40(param_1 + 0xc2ef);
  local_4 = 8;
  _eh_vector_constructor_iterator_(param_1 + 0xc522,0x224,8,InitGuardSlot,ScrubChecksumGuard);
  local_4 = 9;
  *(undefined1 *)(param_1 + 0xc9f4) = 0;
  param_1[0xc971] = 0;
  /* FIXED (2026-07-15): angr-confirmed at 0x443d4e
   * (`lea edi,[esi+0x325b0]`); tableHandle=param_1[0xc971],
   * activeFlag=*(undefined1*)(param_1+0xc9f4), matching above. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x325b0, 0);
  local_4 = 10;
  InitGuardedBool();
  InitGuardedBool();
  InitGuardedBool();
  FUN_00425350();
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

