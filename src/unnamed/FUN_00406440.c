/* FUN_00406440 - 0x00406440 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


byte * __fastcall FUN_00406440(byte *param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = _rand();
  *param_1 = (byte)iVar1;
  iVar1 = _rand();
  param_1[1] = (byte)iVar1;
  bVar2 = *param_1 & 7;
  bVar2 = ~('\x01' << bVar2) & (byte)iVar1 | '\0' << bVar2;
  param_1[1] = bVar2;
  param_1[2] = (bVar2 + *param_1) - 0x34;
  return param_1;
}

