/* FUN_00448370 - 0x00448370 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00448370(int param_1)

{
  char cVar1;
  int iVar2;
  
  (**(code **)(*(int *)(param_1 + 0x30bbc) + 8))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 == 0) {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 != '\x01') {
      cVar1 = PeekPacketChecksumBool();
      if ((cVar1 != '\x01') && (g_stateChangeInProgress == 0)) {
        iVar2 = FUN_0044c3d0(param_1,g_cursorAnchorX,g_cursorAnchorY);
        if (iVar2 != -1) {
          if (*(int *)(param_1 + 0x3478c) == iVar2) {
            *(int *)(param_1 + 0x34790) = *(int *)(param_1 + 0x34790) + 1;
            return;
          }
          *(int *)(param_1 + 0x3478c) = iVar2;
          *(undefined4 *)(param_1 + 0x34790) = 0;
          return;
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x3478c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x34790) = 0;
  return;
}

