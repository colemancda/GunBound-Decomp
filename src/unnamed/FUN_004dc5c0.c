/* FUN_004dc5c0 - 0x004dc5c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __fastcall FUN_004dc5c0(int param_1)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  uint uVar4;
  short sVar5;
  ushort uVar6;
  
  uVar1 = *(ushort *)(DAT_005b3484 + 0x458bc + param_1 * 8);
  uVar4 = (uint)((uVar1 & 0x8000) != 0x8000);
  if ((DAT_00793522 != '\0') && (*(short *)(&DAT_006aa660 + DAT_005b3484) != -1)) {
    sVar5 = *(short *)(&DAT_006aa668 + uVar4 * 8 + DAT_005b3484);
    if (sVar5 == -1) {
      sVar5 = *(short *)(DAT_005b3484 + 0x458c2 + param_1 * 8);
    }
    sVar3 = *(short *)(&DAT_006aa666 + uVar4 * 8 + DAT_005b3484);
    if (sVar3 == -1) {
      sVar3 = *(short *)(DAT_005b3484 + 0x458c0 + param_1 * 8);
    }
    uVar6 = *(ushort *)(&DAT_006aa662 + uVar4 * 8 + DAT_005b3484);
    if (*(ushort *)(&DAT_006aa662 + uVar4 * 8 + DAT_005b3484) == 0xffff) {
      uVar6 = uVar1;
    }
    sVar2 = *(short *)(&DAT_006aa664 + uVar4 * 8 + DAT_005b3484);
    if (sVar2 == -1) {
      sVar2 = *(short *)(DAT_005b3484 + 0x458be + param_1 * 8);
    }
    FUN_004141b0(sVar2,uVar6,sVar3,sVar5,0,param_1 + 200000,param_1 + 300000);
    return;
  }
  FUN_004141b0(*(undefined2 *)(DAT_005b3484 + 0x458be + param_1 * 8),uVar1,
               *(undefined2 *)(DAT_005b3484 + 0x458c0 + param_1 * 8),
               *(undefined2 *)(DAT_005b3484 + 0x458c2 + param_1 * 8),0,param_1 + 200000,
               param_1 + 300000);
  return;
}

