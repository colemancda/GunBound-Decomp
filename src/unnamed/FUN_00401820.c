/* FUN_00401820 - 0x00401820 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_00401820(HMODULE param_1)

{
  uint in_EAX;
  HGLOBAL hResData;
  ushort *puVar1;
  DWORD DVar2;
  ushort *puVar3;
  HRSRC unaff_EBX;
  uint uVar4;
  
  hResData = LoadResource(param_1,unaff_EBX);
  if (hResData == (HGLOBAL)0x0) {
    return 0;
  }
  puVar1 = LockResource(hResData);
  if (puVar1 != (ushort *)0x0) {
    DVar2 = SizeofResource(param_1,unaff_EBX);
    puVar3 = (ushort *)(DVar2 + (int)puVar1);
    for (uVar4 = in_EAX & 0xf; uVar4 != 0; uVar4 = uVar4 - 1) {
      if (puVar3 <= puVar1) {
        return 0;
      }
      puVar1 = puVar1 + *puVar1 + 1;
    }
    if (puVar1 < puVar3) {
      return -(uint)(*puVar1 != 0) & (uint)puVar1;
    }
  }
  return 0;
}

