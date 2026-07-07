/* FUN_0050fe50 - 0x0050fe50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0050fe50(void)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  float fVar8;
  
  if (DAT_005ab4fc < 5) {
    iVar4 = 0;
    uVar1 = DAT_005ab4f4;
    iVar3 = DAT_005ab704;
    pbVar6 = DAT_005a9680;
    uVar7 = DAT_005ab4fc;
    do {
      switch((&switchD_0050fe76::switchdataD_0051008c)[uVar7]) {
      case (undefined *)0x50fe7d:
        if (iVar3 < 0x12) {
          for (; iVar3 < 0x19; iVar3 = iVar3 + 8) {
            uVar1 = uVar1 << 8 | (uint)*pbVar6;
            pbVar6 = pbVar6 + 1;
            DAT_005a9680 = pbVar6;
          }
        }
        bVar2 = (char)iVar3 - 6;
        uVar7 = uVar1 >> (bVar2 & 0x1f);
        iVar3 = iVar3 + -0xc;
        uVar1 = uVar1 - (uVar7 << (bVar2 & 0x1f));
        *(float *)((int)&DAT_005a99f4 + iVar4) =
             (float)(&DAT_005a9888)[uVar7] * *(float *)((int)&DAT_005a9684 + iVar4);
        uVar7 = uVar1 >> ((byte)iVar3 & 0x1f);
        *(float *)(iVar4 + 0x5a9af4) =
             (float)(&DAT_005a9888)[uVar7] * *(float *)((int)&DAT_005a9684 + iVar4);
        uVar1 = uVar1 - (uVar7 << ((byte)iVar3 & 0x1f));
        break;
      case (undefined *)0x50feec:
        if (iVar3 < 0xc) {
          for (; iVar3 < 0x19; iVar3 = iVar3 + 8) {
            uVar1 = uVar1 << 8 | (uint)*pbVar6;
            pbVar6 = pbVar6 + 1;
            DAT_005a9680 = pbVar6;
          }
        }
        iVar3 = iVar3 + -6;
        uVar7 = uVar1 >> ((byte)iVar3 & 0x1f);
        fVar8 = (float)(&DAT_005a9888)[uVar7] * *(float *)((int)&DAT_005a9684 + iVar4);
        uVar1 = uVar1 - (uVar7 << ((byte)iVar3 & 0x1f));
        *(float *)((int)&DAT_005a99f4 + iVar4) = fVar8;
        *(float *)(iVar4 + 0x5a9af4) = fVar8;
        break;
      case (undefined *)0x50ff7d:
        if (iVar3 < 6) {
          for (; iVar3 < 0x19; iVar3 = iVar3 + 8) {
            uVar1 = uVar1 << 8 | (uint)*pbVar6;
            pbVar6 = pbVar6 + 1;
            DAT_005a9680 = pbVar6;
          }
        }
        iVar3 = iVar3 + -6;
        _DAT_005ab888 = uVar1 >> ((byte)iVar3 & 0x1f);
        fVar8 = (float)(&DAT_005a9888)[_DAT_005ab888] * *(float *)((int)&DAT_005a9684 + iVar4);
        uVar1 = uVar1 - (_DAT_005ab888 << ((byte)iVar3 & 0x1f));
        DAT_005ab4f4 = uVar1;
        DAT_005ab704 = iVar3;
        *(float *)((int)&DAT_005a99f4 + iVar4) = fVar8;
        goto LAB_00510068;
      case (undefined *)0x50ffe8:
        if (iVar3 < 0xc) {
          for (; iVar3 < 0x19; iVar3 = iVar3 + 8) {
            uVar1 = uVar1 << 8 | (uint)*pbVar6;
            pbVar6 = pbVar6 + 1;
            DAT_005a9680 = pbVar6;
          }
        }
        bVar2 = (char)iVar3 - 6;
        uVar7 = uVar1 >> (bVar2 & 0x1f);
        iVar3 = iVar3 + -0xc;
        uVar1 = uVar1 - (uVar7 << (bVar2 & 0x1f));
        DAT_005ab704 = iVar3;
        *(float *)((int)&DAT_005a99f4 + iVar4) =
             (float)(&DAT_005a9888)[uVar7] * *(float *)((int)&DAT_005a9684 + iVar4);
        _DAT_005ab888 = uVar1 >> ((byte)iVar3 & 0x1f);
        fVar8 = (float)(&DAT_005a9888)[_DAT_005ab888] * *(float *)((int)&DAT_005a9684 + iVar4);
        uVar1 = uVar1 - (_DAT_005ab888 << ((byte)iVar3 & 0x1f));
        DAT_005ab4f4 = uVar1;
LAB_00510068:
        *(float *)(iVar4 + 0x5a9af4) = fVar8;
        *(float *)(iVar4 + 0x5a9bf4) = fVar8;
      case (undefined *)0x510074:
        goto switchD_0050fe76_caseD_510074;
      }
      iVar3 = iVar3 + -6;
      _DAT_005ab888 = uVar1 >> ((byte)iVar3 & 0x1f);
      iVar5 = _DAT_005ab888 << ((byte)iVar3 & 0x1f);
      DAT_005ab704 = iVar3;
      *(float *)(iVar4 + 0x5a9bf4) =
           (float)(&DAT_005a9888)[_DAT_005ab888] * *(float *)((int)&DAT_005a9684 + iVar4);
      uVar1 = uVar1 - iVar5;
      DAT_005ab4f4 = uVar1;
switchD_0050fe76_caseD_510074:
      uVar7 = *(uint *)((int)&DAT_005ab500 + iVar4);
      iVar4 = iVar4 + 4;
    } while (uVar7 < 5);
  }
  return;
}

