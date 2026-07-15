/* FUN_00506210 - 0x00506210 in the original binary.
 *
 * NOT YET NAMED - the "submit" push-helper called by FUN_00506310
 * (that file's own header has the full vtable-family derivation for
 * their shared unnamed dialog class, vtable 0x557c0c). If the single
 * text-entry child is empty, pushes a queued event with param2=9;
 * otherwise param2=8. Raw/near-verbatim port of Ghidra's decompiler
 * output otherwise, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00506210(undefined4 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if ((uint)param_1[4] <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    pcVar5 = (char *)(*(int *)(param_1[3] + uVar3 * 4) + 0x38);
    pcVar4 = pcVar5;
    if (pcVar5 != (char *)0x0) {
      do {
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
      } while (cVar1 != '\0');
    }
    FUN_004056c0(param_1 + 0x14,pcVar5);
  }
  uVar2 = *param_1;
  if (*(int *)(param_1[0x14] + -0xc) == 0) {
    uVar3 = DAT_00795070 + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != DAT_00795074) {
      *(undefined4 *)(g_inputEventMsgQueue + DAT_00795070 * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + DAT_00795070 * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + DAT_00795070 * 4) = 9;
      DAT_00795070 = uVar3;
      return CONCAT31((int3)(uVar3 >> 8),1);
    }
  }
  else {
    uVar3 = DAT_00795070 + 1 & 0x800001ff;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffe00) + 1;
    }
    if (uVar3 != DAT_00795074) {
      *(undefined4 *)(g_inputEventMsgQueue + DAT_00795070 * 4) = 0;
      *(undefined4 *)(g_inputEventParam1Queue + DAT_00795070 * 4) = uVar2;
      *(undefined4 *)(g_inputEventParam2Queue + DAT_00795070 * 4) = 8;
      DAT_00795070 = uVar3;
    }
  }
  return CONCAT31((int3)(uVar3 >> 8),1);
}

