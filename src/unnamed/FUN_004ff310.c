/* FUN_004ff310 - 0x004ff310 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EDI RECOVERED (2026-08-25): the string to hash.  All three call sites are
 * the same instruction in the three copies of the map-find helper --
 * `mov edi,[esp+0x10]` at 0x4fef77 / 0x4ff137 / 0x500efd, each with two
 * pushes pending over a `push ebp`, so each resolves to that helper's own
 * param_1.  Typed int rather than char * because the body indexes it as
 * `*(char *)(uVar3 + regEdi)`, the shape Ghidra emitted.
 */
#include "ghidra_types.h"


int FUN_004ff310(int regEdi)

{
  int iVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  uVar3 = 0;
  if (*(char *)(regEdi + 0x11) != '\0') {
    do {
      iVar1 = _toupper((int)*(char *)(uVar3 + regEdi));
      iVar4 = iVar4 * 0x21 + iVar1;
      bVar2 = (char)uVar3 + 1;
      uVar3 = (uint)bVar2;
    } while (bVar2 < *(byte *)(regEdi + 0x11));
  }
  return iVar4;
}

