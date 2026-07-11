/* AppendEncodedBlock - 0x004d2570 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall AppendEncodedBlock(undefined4 param_1)

{
  int iVar1;
  int unaff_EBX;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_20 [8];
  
  EncodeHandshakeBlock(*(undefined4 *)(unaff_EBX + 0x84e8),
               &DAT_0056dbf0 + *(int *)(unaff_EBX + 0x4cc) * 0x10,param_1,local_20);
  puVar2 = local_20;
  puVar3 = (undefined4 *)(*(int *)(unaff_EBX + 0x44d0) + 0x4d0 + unaff_EBX);
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(int *)(unaff_EBX + 0x44d0) = *(int *)(unaff_EBX + 0x44d0) + 0x20;
  return;
}

