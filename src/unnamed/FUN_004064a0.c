/* FUN_004064a0 - 0x004064a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004064a0(int param_1)

{
  int iVar1;
  byte bVar2;
  byte *unaff_ESI;
  
  iVar1 = _rand();
  *unaff_ESI = (byte)iVar1;
  iVar1 = _rand();
  unaff_ESI[1] = (byte)iVar1;
  bVar2 = *unaff_ESI & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | (param_1 != '\0') << bVar2;
  unaff_ESI[1] = bVar2;
  unaff_ESI[2] = (bVar2 + *unaff_ESI) - 0x34;
  return;
}

