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
 */
#include "ghidra_types.h"


int * Vector_CopyElement_8(int *param_1)

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

