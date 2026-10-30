/* AtlArray_DestroyElement_450 - 0x00426810 in the original binary.
 *
 * NAMED (2026-10-29): the destructor ~E() of the 0x450-byte avatar-item
 * record that the four CAtlArrays at g_clientContext + 0x44e20..0x44e50
 * hold.  Every caller runs it where CAtlArray runs ~E:
 *
 * - AtlArray_CallDestructors_450 (0x426711), once per element;
 * - AtlArray_CallConstructors_450's catch block (0x44c8da), unwinding
 *   the elements already built before rethrowing;
 * - the `nNewSize == 0` arm of AtlArray_SetCount_450 (0x44c7d3) and
 *   AtlArray_RemoveAll_450 (0x44c605), and AtlArray_RemoveAt_450
 *   (0x44c6e5), each in a 0x450-stride loop over m_pData;
 * - ClientContext_Destructor's four inlined ~CAtlArray loops (0x4197e9, 0x419821,
 *   0x419858, 0x419891) and AtlArray_InsertAt_450 (0x50d066);
 * - and at scope end on a stack temporary built by
 *   AtlArray_ConstructElement_450 (0x428550) in State03/State07's packet
 *   handlers and in FUN_0050a320 - temporaries that are filled and then
 *   pushed into these arrays (CAtlArray::Add, 0x42ae30, or InsertAt).
 *
 * The body releases the record's two CValueGuard table handles, at +0x240
 * and then +0x1c - the handles AtlArray_ConstructElement_450 zeroes for
 * the guarded value cells at +0x22c and +8.
 *
 * WHY AtlArray_..._450.  The record type is still unnamed, so this
 * follows AtlArray_CopyElement_450 (the same record's operator=, see its
 * header) and CArray_CopyElement_1750: the container prefix plus the
 * element stride.  When the record type is named, this should become its
 * destructor along with those.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void AtlArray_DestroyElement_450(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005380ab;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_4 = 0;
  if (*(int *)(param_1 + 0x240) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x240),&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if (*(int *)(param_1 + 0x1c) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(param_1 + 0x1c),&g_valueGuardKeyTable);
    TreeInsert(local_14,&g_valueGuardMap);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

