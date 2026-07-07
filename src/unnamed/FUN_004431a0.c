/* FUN_004431a0 - 0x004431a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004431a0(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  int in_EAX;
  uint uVar5;
  
  uVar1 = *(ushort *)(DAT_005b3484 + 0x501fe + in_EAX * 8);
  uVar5 = (uint)((uVar1 & 0x8000) != 0x8000);
  uVar2 = *(ushort *)(&DAT_006aa664 + uVar5 * 8 + DAT_005b3484);
  if (uVar2 == 0xffff) {
    uVar2 = *(ushort *)(DAT_005b3484 + 0x50200 + in_EAX * 8);
  }
  uVar3 = *(ushort *)(&DAT_006aa666 + uVar5 * 8 + DAT_005b3484);
  if (uVar3 == 0xffff) {
    uVar3 = *(ushort *)(DAT_005b3484 + 0x50202 + in_EAX * 8);
  }
  uVar4 = *(ushort *)(&DAT_006aa662 + uVar5 * 8 + DAT_005b3484);
  if (uVar4 == 0xffff) {
    uVar4 = uVar1;
  }
  uVar1 = *(ushort *)(&DAT_006aa668 + uVar5 * 8 + DAT_005b3484);
  if (uVar1 == 0xffff) {
    uVar1 = *(ushort *)(DAT_005b3484 + 0x50204 + in_EAX * 8);
  }
  FUN_004141b0(uVar1 & 0x7fff,uVar4 & 0x7fff,uVar3 & 0x7fff,uVar2 & 0x7fff,0,in_EAX + 200000,
               in_EAX + 300000);
  return;
}

