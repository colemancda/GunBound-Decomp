/* FUN_0053572b - 0x0053572b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __setmode_lk
   
   Library: Visual Studio 2003 Release */

int __setmode_lk(uint param_1,int param_2)

{
  int *piVar1;
  byte *pbVar2;
  byte bVar3;
  undefined4 *puVar4;
  int iVar5;
  
  piVar1 = &DAT_00f28320 + ((int)param_1 >> 5);
  iVar5 = (param_1 & 0x1f) * 0x24;
  bVar3 = *(byte *)(*piVar1 + 4 + iVar5);
  if (param_2 == 0x8000) {
    pbVar2 = (byte *)(*piVar1 + 4 + iVar5);
    *pbVar2 = *pbVar2 & 0x7f;
  }
  else {
    if (param_2 != 0x4000) {
      puVar4 = (undefined4 *)FUN_0052b6d4();
      *puVar4 = 0x16;
      return -1;
    }
    pbVar2 = (byte *)(*piVar1 + 4 + iVar5);
    *pbVar2 = *pbVar2 | 0x80;
  }
  return (-(uint)((bVar3 & 0x80) != 0) & 0xffffc000) + 0x8000;
}

