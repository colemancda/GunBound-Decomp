/* Vector_CopyElement_8 - 0x00503710 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the copy-construct-one-element member of the
 * 8-byte {CStringA, CStringA} pair vector - the stride-8 sibling of
 * Vector_CopyElement_34 (0x503680) and Vector_CopyElement_1e
 * (0x503770), between which it sits in the binary. Same role as both:
 * the first call Vector_InsertN_8 makes, cloning the by-value element
 * into a local buffer before any reallocation can invalidate it. The
 * body clones the pair's two CString handles from the EDI source
 * (still a dropped register here) via the 0x43de10 addref/clone the
 * whole CString family uses, dest handles at +0/+4 - stride 8, element
 * type pinned. Sole binary caller: Vector_InsertN_8 at 0x50315d.
 *
 * EDI RECOVERED (2026-10-30): the source element is EDI (`mov eax,[edi]`
 * at 0x503725, `mov eax,[edi+4]` at 0x503741, no write first), set by
 * the caller's `mov edi,ecx` at 0x50315b; now the trailing regEdi.  The
 * body still does not use it: each clone is FUN_0043de10 with EAX =
 * handle - 0x10 (0x50372c, 0x503744), and FUN_0043de10's port has no
 * parameter for EAX at any of its 11 call sites - a family-wide gap left
 * for its own change.
 */
#include "ghidra_types.h"


int * Vector_CopyElement_8(int *param_1,int regEdi)

{
  int iVar1;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537a58) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  FUN_0043de10();
  *param_1 = iVar1 + 0x10;
  local_4 = 0;
  FUN_0043de10();
  param_1[1] = iVar1 + 0x10;
  return param_1;
}

