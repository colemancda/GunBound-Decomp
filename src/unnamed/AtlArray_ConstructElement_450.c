/* AtlArray_ConstructElement_450 - 0x00428550 in the original binary.
 *
 * NAMED (2026-10-29): the default constructor E() of the 0x450-byte
 * avatar-item record that the four CAtlArrays at g_clientContext +
 * 0x44e20..0x44e50 hold - the `::new (pElements + i) E` that
 * AtlArray_CallConstructors_450 runs per element (0x44c8b3, after the
 * placement-new null test).  Its other five binary call sites build a
 * stack temporary of the same record that is then filled and pushed into
 * these arrays and destroyed with AtlArray_DestroyElement_450 at scope
 * end: State03_GameRoomList_ProcessPacket (0x428368) and
 * State07_AvatarStore_ProcessPacket (0x444218, 0x444444, 0x445057) feed
 * it to CAtlArray::Add (0x42ae30), and AvatarStorePanel_OnMouseUp (0x50a3cf) to
 * AtlArray_CopyElement_450 and InsertAt.
 *
 * The body initialises the record's guarded bool at +0 (InitGuardedBool)
 * and the two guarded value cells at +8 and +0x22c to 0, zeroing each
 * cell's table handle (+0x1c, +0x240) and trailing byte (+0x228, +0x44c)
 * - the handles AtlArray_DestroyElement_450 releases.  It returns `this`
 * (`mov eax,esi`).  Not to be confused with
 * AtlArray_CopyConstructElement_450, the record's COPY constructor (see
 * AtlArray_CopyElement_450's header).
 *
 * The name follows AtlArray_CopyElement_450 and
 * AtlArray_DestroyElement_450 (container prefix plus element stride,
 * since the record type is unnamed); it should become the record's
 * constructor once the type is named.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * FIXED (2026-09-01): recovered the dropped guard-cell arg at the one
 * argless InitGuardedBool site (ECX arg; 0x42856e ecx=esi, esi =
 * param_1) - the cell is param_1 itself, the object base.
 */
#include "ghidra_types.h"


int AtlArray_ConstructElement_450(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005380ab;
  *unaff_FS_OFFSET = &local_c;
  InitGuardedBool((byte *)param_1);
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

