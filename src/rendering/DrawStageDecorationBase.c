/* DrawStageDecorationBase - 0x004e3bd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall DrawStageDecorationBase(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  g_nCompositorLayer = 2;
  iVar3 = *(int *)(DAT_00ea0e1c + 0x1c);
  iVar2 = 0x12a - *(int *)(param_1 + 0xc);
  uVar1 = *(uint *)(iVar3 + 4);
  if (uVar1 < 0xea61) {
    while (uVar1 != 60000) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (60000 < uVar1) {
        return iVar2;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    bVar4 = true;
    if (*(int *)(iVar3 + 8) == 0) {
      while (!bVar4) {
        iVar3 = *(int *)(iVar3 + 0x10);
        bVar4 = *(int *)(iVar3 + 8) == 0;
        if (!bVar4) {
          return iVar2;
        }
      }
      if (*(char *)(iVar3 + 0x18) == '\x01') {
        /* One argument-setup block feeds both twins (0x4e3c2a..0x4e3c38
         * reaches 0x4e3c3a and 0x4e3c44 alike): ECX=0 (index), EDX=0xea60
         * (group), the value PUSHED at 0x4e3c32 is x = 400 -
         * *(param_1 + 8), and EAX - set at 0x4e3bec and untouched through
         * the tree walk - is y, i.e. this function's existing iVar2. */
        iVar3 = QueueSpriteFrameSpans(0,400 - *(int *)(param_1 + 8),iVar2,0xea60);
        return iVar3;
      }
      /* Corrected 2026-08-28 alongside the QueueSpriteFrameSpans twin
       * above, completed 2026-08-31 when QueueTextureRegionSpans was
       * recovered: ECX=0 (index) and EDX=0xea60 (group, the same
       * constant as the uVar1<0xea61/60000 tree search) are the two
       * __fastcall register slots; ESI is the value PUSHED at 0x4e3c32,
       * i.e. the x. The y is EAX = 0x12a - *(param_1+0xc), built at
       * 0x4e3be7/0x4e3bec and untouched through the tree walk - this
       * function's own iVar2, now passed as regEax. */
      iVar2 = QueueTextureRegionSpans(0,0xea60,400 - *(int *)(param_1 + 8),iVar2);
    }
  }
  return iVar2;
}

