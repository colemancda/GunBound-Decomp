/* FUN_00425a30 - 0x00425a30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00425a30(int param_1)

{
  undefined4 uVar1;
  byte *in_EAX;
  uint uVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  uVar2 = (uint)*in_EAX;
  pbVar4 = in_EAX + 1;
  pbVar5 = (byte *)(param_1 + 0x44e64);
  for (uVar3 = (uint)(*in_EAX >> 2); uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pbVar5 = *(undefined4 *)pbVar4;
    pbVar4 = pbVar4 + 4;
    pbVar5 = pbVar5 + 4;
  }
  for (uVar3 = uVar2 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pbVar5 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    pbVar5 = pbVar5 + 1;
  }
  *(undefined1 *)(uVar2 + 0x44e64 + param_1) = 0;
  pbVar4 = in_EAX + 1 + uVar2;
  *(byte *)(param_1 + 0x44ef8) = *pbVar4;
  uVar1 = *(undefined4 *)(pbVar4 + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(param_1 + 0x457a1) = *(undefined4 *)(pbVar4 + 5);
  *(undefined4 *)(param_1 + 0x457a5) = *(undefined4 *)(pbVar4 + 9);
  *(byte *)(param_1 + 0x45124) = pbVar4[0xd];
  return;
}

