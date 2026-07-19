/* FUN_004e6b90 - 0x004e6b90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e6b90(void)

{
  uint *puVar1;
  undefined1 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int unaff_ESI;
  short *psVar7;
  bool bVar8;
  int *local_8;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  uVar6 = 0;
  local_8 = (int *)(unaff_ESI + 0x38);
  psVar7 = (short *)(unaff_ESI + 0x40bd8);
  iVar5 = unaff_ESI + 0x58;
  bVar8 = true;
  do {
    if (!bVar8) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    uVar4 = 1 << ((byte)uVar6 & 0x1f);
    iVar3 = (uVar6 >> 5) * 4;
    if (((((*(uint *)(iVar3 + 0x13c + unaff_ESI) & uVar4) == 0) &&
         ((*(uint *)(iVar3 + 0x140 + unaff_ESI) & uVar4) != 0)) &&
        ((*(uint *)(iVar3 + 0x138 + unaff_ESI) & uVar4) != 0)) &&
       (*(char *)(unaff_ESI + 0x454e4 + uVar6) != '\x01')) {
      if (*psVar7 == 0) {
        puVar1 = (uint *)(iVar3 + 0x13c + unaff_ESI);
        *puVar1 = *puVar1 | uVar4;
      }
      else {
        uVar2 = *(undefined1 *)((int)psVar7 + 7);
        *(short *)(iVar5 + 0x4522c) = psVar7[1];
        *(undefined1 *)(unaff_ESI + 0x45294 + uVar6) = uVar2;
        SendUdpDatagram(*(int *)(unaff_ESI + 0x18 + uVar6 * 4),(int)*(short *)iVar5,(char *)psVar7,
                        (int)*psVar7,unaff_ESI);
        if (*local_8 != -1) {
          SendUdpDatagram(*local_8,(int)*(short *)(iVar5 + 0x10),(char *)psVar7,(int)*psVar7,
                          unaff_ESI);
        }
      }
    }
    uVar6 = uVar6 + 1;
    local_8 = local_8 + 1;
    iVar5 = iVar5 + 2;
    psVar7 = psVar7 + 0x100;
    bVar8 = uVar6 < 8;
  } while ((int)uVar6 < 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  return;
}

