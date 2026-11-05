/* AvatarPartWorkspace_Construct - 0x00425350 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00425350 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body:
 * State07_AvatarStore's constructor builds its two part-record arrays (9
 * and 0x15 elements, stride 0x17e4) with _eh_vector_constructor_iterator_
 * using this and FUN_004254a0 as ctor and dtor, and the avatar-store and
 * equip code (State07_AvatarStore_OnCommand, RenderInventoryItemDetail,
 * ApplyAvatarStatBonuses, LoadAvatarStoreCatalog) call it on stack buffers
 * they then hand to LoadAvatarPartRecordByIndex, whose output cells at +0,
 * +0x23c ... +0x1580 are exactly the 11 guard cells this initialises. The
 * 0x17e4 stride is those 11 cells (guard extent 0x17a4) plus the 0x40-byte
 * text field at +0x17a4.
 *
 * The 11-cell CValueGuard workspace constructor: zeroes each cell's
 * activeFlag/tableHandle pair and registers it via
 * EncodeOutgoingPacketField(cell, 0), for cells 0x23c apart at
 * +0/0x23c/.../0x1580 (object extent 0x17a4 bytes). `this` arrives in
 * ECX; sole callers are State07_AvatarStore_OnCommand's five `lea ecx,[esp+0x2d3c]` /
 * `call 0x425350` sites (the state-7 OnCommand's stack workspace - see
 * that file's guardWorkspace local).
 *
 * SEH-PROLOGUE ARTIFACT STRIPPED (2026-08-10): same class/fix as
 * FUN_0044fb40.c/FUN_00449540.c and this function's caller - Ghidra
 * emitted the original's fs:[0] exception-frame setup/teardown as
 * literal reads/writes through an uninitialised `unaff_FS_OFFSET`
 * local, which MSVC compiled into a garbage-pointer dereference. The
 * `local_4` SEH-state cookie writes (the SUBFIELD/CONCAT31 ladder) are
 * kept - they are dead stores here but document the original's
 * per-cell unwind states. Raw/near-verbatim port otherwise.
 */
#include "ghidra_types.h"


int __fastcall AvatarPartWorkspace_Construct(int param_1)

{
  undefined4 local_4;

  local_4 = 0xffffffff;
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x42537d/0x425396/.../0x425480 (`mov edi,esi` then a run of
   * `lea edi,[esi+N]`, esi = this file's own param_1) - 11 distinct
   * CValueGuard cells at param_1+0/0x23c/0x460/0x684/0x8a8/0xacc/0xcf0/
   * 0xf14/0x1138/0x135c/0x1580, each confirmed by the activeFlag(+0x220)/
   * tableHandle(+0x14) zero-write pair immediately above its own call.
   * See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1, 0);
  local_4 = 0;
  *(undefined1 *)(param_1 + 0x45c) = 0;
  *(undefined4 *)(param_1 + 0x250) = 0;
  EncodeOutgoingPacketField(param_1 + 0x23c, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x680) = 0;
  *(undefined4 *)(param_1 + 0x474) = 0;
  EncodeOutgoingPacketField(param_1 + 0x460, 0);
  SUBFIELD(local_4,0,undefined1) = 2;
  *(undefined1 *)(param_1 + 0x8a4) = 0;
  *(undefined4 *)(param_1 + 0x698) = 0;
  EncodeOutgoingPacketField(param_1 + 0x684, 0);
  SUBFIELD(local_4,0,undefined1) = 3;
  *(undefined1 *)(param_1 + 0xac8) = 0;
  *(undefined4 *)(param_1 + 0x8bc) = 0;
  EncodeOutgoingPacketField(param_1 + 0x8a8, 0);
  SUBFIELD(local_4,0,undefined1) = 4;
  *(undefined1 *)(param_1 + 0xcec) = 0;
  *(undefined4 *)(param_1 + 0xae0) = 0;
  EncodeOutgoingPacketField(param_1 + 0xacc, 0);
  SUBFIELD(local_4,0,undefined1) = 5;
  *(undefined1 *)(param_1 + 0xf10) = 0;
  *(undefined4 *)(param_1 + 0xd04) = 0;
  EncodeOutgoingPacketField(param_1 + 0xcf0, 0);
  SUBFIELD(local_4,0,undefined1) = 6;
  *(undefined1 *)(param_1 + 0x1134) = 0;
  *(undefined4 *)(param_1 + 0xf28) = 0;
  EncodeOutgoingPacketField(param_1 + 0xf14, 0);
  SUBFIELD(local_4,0,undefined1) = 7;
  *(undefined1 *)(param_1 + 0x1358) = 0;
  *(undefined4 *)(param_1 + 0x114c) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1138, 0);
  SUBFIELD(local_4,0,undefined1) = 8;
  *(undefined1 *)(param_1 + 0x157c) = 0;
  *(undefined4 *)(param_1 + 0x1370) = 0;
  EncodeOutgoingPacketField(param_1 + 0x135c, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
  *(undefined1 *)(param_1 + 0x17a0) = 0;
  *(undefined4 *)(param_1 + 0x1594) = 0;
  EncodeOutgoingPacketField(param_1 + 0x1580, 0);
  return param_1;
}

