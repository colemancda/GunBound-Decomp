/* InsertTextureCacheRecord - 0x004f45d0 in the original binary.
 *
 * Sorted (inline strcmp) insert of a texture name-record into the
 * cache's record list (head +0x1b4, link +0x98); frees the argument on
 * a duplicate name - the insert mirror of FindTextureCacheEntryByName
 * (0x4f4650). NAMED (2026-07-18); called by PreloadTexture.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void InsertTextureCacheRecord(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int in_EAX;
  byte *pbVar4;
  int iVar5;
  byte *pbVar6;
  bool bVar7;
  
  pbVar4 = *(byte **)(in_EAX + 0x1b4);
  pbVar3 = (byte *)(in_EAX + 0x11c);
  while (pbVar2 = pbVar4, pbVar4 = param_1, pbVar6 = pbVar2, pbVar2 != (byte *)0x0) {
    do {
      bVar1 = *pbVar4;
      bVar7 = bVar1 < *pbVar6;
      if (bVar1 != *pbVar6) {
LAB_004f4614:
        iVar5 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_004f4619;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar4[1];
      bVar7 = bVar1 < pbVar6[1];
      if (bVar1 != pbVar6[1]) goto LAB_004f4614;
      pbVar4 = pbVar4 + 2;
      pbVar6 = pbVar6 + 2;
    } while (bVar1 != 0);
    iVar5 = 0;
LAB_004f4619:
    if (iVar5 == 0) {
      _free(param_1);
      return;
    }
    if (0 < iVar5) break;
    pbVar3 = pbVar2;
    pbVar4 = *(byte **)(pbVar2 + 0x98);
  }
  *(byte **)(pbVar3 + 0x98) = param_1;
  *(byte **)(param_1 + 0x98) = pbVar2;
  return;
}

