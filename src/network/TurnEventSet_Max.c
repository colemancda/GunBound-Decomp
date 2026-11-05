/* TurnEventSet_Max - 0x004e8d10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_004e8d10 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body:
 * _Tree::_Max(node): mirror of TurnEventSet_Min through the right link
 * (+8). Sole caller TurnEventSet_Erase uses it for the rbegin update (`if
 * header->right == erased: header->right = Max(replacement)`).
 *
 * (FUN_004e87b0 below is TurnEventSet_Erase's old symbol.)
 *
 * EAX RECOVERED (2026-08-25): the node, `mov eax,edi` at 0x4e88bb in
 * FUN_004e87b0, where EDI is the source's piVar6 -- the guard immediately
 * above the call (`mov al,[edi+0xf]; test al,al; je`) is that function's
 * `if (*(char *)((int)piVar6 + 0xf) == '\0')`, so the register and the
 * source variable are the same value on the same line.
 */
#include "ghidra_types.h"


void TurnEventSet_Max(int regEax)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(regEax + 8);
  cVar1 = *(char *)(iVar2 + 0xf);
  while (cVar1 == '\0') {
    iVar2 = *(int *)(iVar2 + 8);
    cVar1 = *(char *)(iVar2 + 0xf);
  }
  return;
}

