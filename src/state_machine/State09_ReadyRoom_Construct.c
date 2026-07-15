/* State09_ReadyRoom_Construct - 0x004d3770 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * State09_ReadyRoom_Construct(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537c93;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  *param_1 = &vtable_State09_ReadyRoom;
  *(undefined1 *)(param_1 + 0x8b) = 0;
  param_1[8] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4d3792
   * (`lea edi,[esi+0xc]`, esi = this file's own param_1) the cell is
   * param_1+0xc (a CValueGuard cell - its own activeFlag(+0x220)/
   * tableHandle(+0x14) zero-init immediately precedes this call). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0xc, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
  *(undefined1 *)(param_1 + 0x123) = 0;
  param_1[0xa0] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4d37aa
   * (`lea edi,[esi+0x26c]`) a second CValueGuard cell at param_1+0x26c,
   * same evidence as above. */
  EncodeOutgoingPacketField((int)param_1 + 0x26c, 0);
  puVar2 = param_1 + 0x1bf;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

