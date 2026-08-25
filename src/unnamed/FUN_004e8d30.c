/* FUN_004e8d30 - 0x004e8d30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25): the node, `mov eax,edi` at 0x4e8898 in
 * FUN_004e87b0, where EDI is the source's piVar6 -- the guard immediately
 * above the call (`mov al,[edi+0xf]; test al,al; je`) is that function's
 * `if (*(char *)((int)piVar6 + 0xf) == '\0')`, so the register and the
 * source variable are the same value on the same line.
 */
#include "ghidra_types.h"


void FUN_004e8d30(int *regEax)

{
  char cVar1;
  int *piVar2;
  
  piVar2 = (int *)*regEax;
  cVar1 = *(char *)((int)piVar2 + 0xf);
  while (cVar1 == '\0') {
    piVar2 = (int *)*piVar2;
    cVar1 = *(char *)((int)piVar2 + 0xf);
  }
  return;
}

