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
        iVar3 = QueueSpriteFrameSpans();
        return iVar3;
      }
      /* QueueTextureRegionSpans dropped param_1(region index)/param_2
       * (registry group) entirely, and in_EAX(y) was already the only
       * visible arg - confirmed via objdump at 0x4e3c44: ECX=0(index),
       * EDX=0xea60(group, same constant as the uVar1<0xea61/60000 tree
       * search just above), ESI(y)=400-*(param_1+8) (pushed directly,
       * matches this line's pre-existing expression exactly). */
      iVar2 = QueueTextureRegionSpans(0,0xea60,400 - *(int *)(param_1 + 8));
    }
  }
  return iVar2;
}

