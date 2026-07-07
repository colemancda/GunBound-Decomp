/* FUN_004f0650 - 0x004f0650 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004f0650(void)

{
  uint uVar1;
  int iVar2;
  int unaff_ESI;
  DWORD local_8;
  int local_4;
  
  uVar1 = SetFilePointer(*(HANDLE *)(unaff_ESI + 0x1000),*(LONG *)(unaff_ESI + 0x1010),(PLONG)0x0,0)
  ;
  if (uVar1 != 0xffffffff) {
    uVar1 = ReadFile(*(HANDLE *)(unaff_ESI + 0x1000),&local_4,4,&local_8,(LPOVERLAPPED)0x0);
    if (local_8 == 4) {
      iVar2 = *(int *)(unaff_ESI + 0x1010) + local_4 + 8;
      *(int *)(unaff_ESI + 0x1010) = iVar2;
      *(undefined4 *)(unaff_ESI + 0x100c) = 0;
      return CONCAT31((int3)((uint)iVar2 >> 8),1);
    }
  }
  return uVar1 & 0xffffff00;
}

