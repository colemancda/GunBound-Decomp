/* FUN_004e1d50 - 0x004e1d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004e1d50(int param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005390bc;
  *unaff_FS_OFFSET = &local_c;
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4e1d7b
   * (`mov edi,esi`, esi = this file's own param_1) the cell is param_1
   * itself; activeFlag(+0x220)/tableHandle(+0x14) zero-write immediately
   * above confirms it. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1, 0);
  local_4 = 0;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x224),0x224,3,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 1;
  _eh_vector_constructor_iterator_((void *)(param_1 + 0x890),0x224,3,InitGuardSlot,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x1128) = 0;
  *(undefined4 *)(param_1 + 0xf1c) = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4e1dd8
   * (`lea edi,[esi+0xf08]`) the cell is param_1+0xf08;
   * activeFlag(+0x220)=param_1+0x1128/tableHandle(+0x14)=param_1+0xf1c
   * zero-write immediately above confirms it. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 0xf08, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
  *(undefined4 *)(param_1 + 0xefc) = 0xffffff9c;
  *(undefined4 *)(param_1 + 0xf04) = 1;
  iVar1 = _rand();
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x4e1e15/0x4e1e44/0x4e1e6d (`mov edi,ebp` with ebp =
   * `lea ebp,[esi+0x890]` at 0x4e1db2, then two bare `lea edi,[esi+N]`
   * at 0x4e1e3e/0x4e1e67) the cells are param_1+0x890, param_1+0xab4,
   * param_1+0xcd8 - the 3 consecutive 0x224-byte elements of the guard
   * array constructed at param_1+0x890 above
   * (_eh_vector_constructor_iterator_(..., 0x224, 3, ...)). See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_1 + 0x890, iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_1 + 0xab4, iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = _rand();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(param_1 + 0xcd8, iVar1 % 10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

