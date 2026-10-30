/* FUN_00401910 - 0x00401910 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-10-30): the original links an EH frame
 * (mov eax,fs:[0] / push 0x537922 / mov fs:[0],esp at 0x401910-0x40191e)
 * and unlinks it before returning.  Ghidra rendered that as writes
 * through an uninitialised `unaff_FS_OFFSET` pointer plus the try-state
 * counter local_4 (including a CONCAT31 sub-byte store).  The handler
 * (LAB_00537922) is not part of this decompile, so the plumbing is
 * stripped as in ConstructStringFromText.c.
 */
#include "ghidra_types.h"


undefined4 * FUN_00401910(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  ActiveObjectRegistry_BaseConstructor(param_1);
  param_1[2] = &PTR_LAB_00551cf4;
  *param_1 = &PTR_FUN_00551cf0;
  param_1[2] = &PTR_LAB_00551cb8;
  param_1[0x6f9] = 0;
  param_1[0x6fa] = 0;
  param_1[0x6fb] = 0;
  param_1[0x6fc] = 0;
  param_1[0x6fd] = 10;
  param_1[0x6fe] = 0;
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,param_1 + 0x6ff);
  puVar3 = param_1 + 3;
  for (iVar2 = 0x300; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x304] = 0;
  param_1[0x303] = 0;
  param_1[0x3c8] = 0;
  param_1[0x3c9] = 0;
  puVar3 = param_1 + 0x3ca;
  for (iVar2 = 0x1a0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x56a] = 0;
  puVar3 = param_1 + 0x56b;
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  puVar3 = param_1 + 0x66b;
  for (iVar2 = 0x80; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  param_1[0x6eb] = 0xffffffff;
  *(undefined1 *)((int)param_1 + 0x1bbe) = 0;
  *(undefined1 *)(param_1 + 0x6f3) = 0;
  param_1[0x6f4] = 0;
  *(undefined1 *)(param_1 + 0x6f5) = 1;
  param_1[0x6f6] = 0;
  param_1[0x6f7] = 0;
  param_1[0x6f8] = 0;
  uVar1 = CreateCommP2POwner(param_1 + 2);
  param_1[0x6f7] = uVar1;
  return param_1;
}

