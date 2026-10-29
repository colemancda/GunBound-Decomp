/* AtlArray_CopyConstructElement_450 - 0x0042aeb0 in the original binary.
 *
 * NAMED (2026-10-29), LIKELY: the copy constructor E(const E&) of the
 * 0x450-byte avatar-item record that the CAtlArrays at g_clientContext +
 * 0x44e20..0x44e50 hold - the `::new (m_pData + iElement) E(element)`
 * that AtlArray_Add_450 runs on the new slot (0x42ae85, after the
 * placement-new null test), its one binary call site.  Destination and
 * source are both pushed (`ret 8`), and it returns the destination
 * (`mov eax,esi`).
 *
 * The body confirms the role against its siblings: it copies the
 * guarded bool at +0 (word + byte), the dword at +4 and the two guarded
 * value cells at +8 and +0x22c (Peek the source, Encode into the
 * destination), but first zeroes the destination's table handles at
 * +0x1c / +0x240 and trailing bytes at +0x228 / +0x44c - exactly the
 * fields AtlArray_ConstructElement_450 initialises and
 * AtlArray_CopyElement_450 (the assignment operator) leaves alone.
 *
 * LIKELY rather than CERTAIN because the name is the container's, not
 * the record's: like AtlArray_ConstructElement_450, this is a member of
 * the element type, carried under the container prefix plus stride only
 * because the record type is still unnamed.  It should become the
 * record's copy constructor once the type is named.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: a two-cell COPY CONSTRUCTOR - each Peek reads param_2 (EBP, the source) at the same offset the Encode beside it writes into param_1 (ESI, the dest): +8 and +0x22c.  Two-object copier: same offset, different base.
 */
#include "ghidra_types.h"


undefined2 * AtlArray_CopyConstructElement_450(undefined2 *param_1,undefined2 *param_2)

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
  uVar1 = PeekPacketChecksumState((void *)((int)param_2 + 8));
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
  uVar1 = PeekPacketChecksumState((void *)((int)param_2 + 0x22c));
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x42af22
   * (`lea edi,[esi + 0x22c]`, esi = param_1): cell is param_1+0x22c;
   * tableHandle(+0x14)=param_1+0x240 (== `param_1 + 0x120` above) is
   * zeroed just above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x22c, uVar1);
  return param_1;
}

