/* FUN_004fcf70 - 0x004fcf70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the FUN_004fe110() call (orig
 * 0x4fcfd5) was missing its leading __thiscall arg. Disasm shows
 * `lea ecx,[edi+0x1a90]` immediately before the call - the same
 * `regEdi + 0x1a90` "this" object used by the other FUN_004fe110 call
 * sites (see FUN_004fcf10.c / FUN_004fe110.c). The 5 already-present
 * arguments were already correctly positioned.
 */
#include "ghidra_types.h"


void FUN_004fcf70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int regEbx,int *regEdi)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 auStack_190 [100];
  
  iVar2 = 0;
  if (100 < param_1) {
    param_1 = 100;
  }
  iVar3 = 0;
  if (0 < param_1) {
    do {
      cVar1 = (**(code **)(*regEdi + 0x3c))(*(undefined4 *)(regEbx + iVar3 * 4));
      if (cVar1 == '\0') {
        auStack_190[iVar2] = *(undefined4 *)(regEbx + iVar3 * 4);
        iVar2 = iVar2 + 1;
      }
      else {
        SendP2PMessageToPeer((undefined4 *)((char *)regEdi + 0x1a90),regEdi + 0xb,
                     *(undefined4 *)(regEbx + iVar3 * 4),param_2,param_3,param_4);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < param_1);
    if (0 < iVar2) {
      /* 0x4fcffb `mov eax,esi` / call 0x4fd030, then 0x4fd019 `mov cl,al`
       * and 0x4fd01b `mov edx,esi`, with esi = [esp+0x1a0] = param_2, the
       * message type (the same slot SendP2PMessageToPeer receives it in). */
      FUN_00502650((int)regEdi,iVar2,(int)auStack_190,(undefined4 *)param_3,param_4,
                   (unsigned char)FUN_004fd030((unsigned short)param_2),(unsigned short)param_2);
    }
  }
  return;
}

