/* FUN_0050fd90 - 0x0050fd90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0050fd90(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  
  iVar1 = DAT_005a99e8;
  iVar6 = 0;
  iVar2 = DAT_005ab704;
  uVar3 = DAT_005ab4f4;
  pbVar5 = DAT_005a9680;
  if (0 < DAT_005a99e8) {
    do {
      if (iVar2 < 2) {
        while (iVar2 < 0x19) {
          uVar3 = uVar3 << 8 | (uint)*pbVar5;
          pbVar5 = pbVar5 + 1;
          iVar2 = iVar2 + 8;
          DAT_005a9680 = pbVar5;
          DAT_005ab4f4 = uVar3;
          DAT_005ab704 = iVar2;
        }
      }
      if ((&DAT_005ab604)[iVar6] == 0) {
        (&DAT_005ab4fc)[iVar6] = 4;
      }
      else {
        iVar2 = iVar2 + -2;
        _DAT_005ab888 = uVar3 >> ((byte)iVar2 & 0x1f);
        iVar4 = _DAT_005ab888 << ((byte)iVar2 & 0x1f);
        DAT_005ab704 = iVar2;
        (&DAT_005ab4fc)[iVar6] = _DAT_005ab888;
        uVar3 = uVar3 - iVar4;
        DAT_005ab4f4 = uVar3;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar1);
    (&DAT_005ab4fc)[iVar6] = 5;
    return;
  }
  DAT_005ab4fc = 5;
  return;
}

