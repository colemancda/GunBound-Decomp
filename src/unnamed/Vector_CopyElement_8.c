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
 * the caller's `mov edi,ecx` at 0x50315b; now the trailing regEdi.
 *
 * FIXED (2026-10-30): the body now uses it. Each clone is FUN_0043de10
 * with EAX = the source handle - 0x10 (`mov eax,[edi] / sub eax,0x10` at
 * 0x503725/0x50372c, `mov eax,[edi+4] / sub eax,0x10` at
 * 0x503741/0x503744), and the clone's returned header + 0x10 is the new
 * handle (`add eax,0x10` at 0x503734/0x503750). The calls passed no
 * header, and the stores read an uninitialised iVar1 in place of the
 * return value. The SEH-prologue artifact (push -1 / push 0x537a58 /
 * mov fs:[0],esp at 0x503710-0x50371e and its try-state local) is gone.
 */
#include "ghidra_types.h"


int * Vector_CopyElement_8(int *param_1,int regEdi)

{
  int iVar1;

  iVar1 = FUN_0043de10((int *)(*(int *)regEdi + -0x10));
  *param_1 = iVar1 + 0x10;
  iVar1 = FUN_0043de10((int *)(*(int *)(regEdi + 4) + -0x10));
  param_1[1] = iVar1 + 0x10;
  return param_1;
}
