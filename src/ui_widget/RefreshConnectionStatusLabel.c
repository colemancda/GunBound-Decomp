/* RefreshConnectionStatusLabel - 0x0050ce60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void RefreshConnectionStatusLabel(int param_1)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  puVar1 = g_gameStateVTableArray[7];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar2 != -1) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(puVar1 + 0x454) + iVar2)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((uVar3 & 0xe0000000) == 0) {
      uVar3 = Widget_FindChildIndex();
      if (uVar3 != 0xffffffff) {
        if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        Widget_RemoveChild();
      }
      iVar2 = Widget_FindChildIndex();
      if (iVar2 == -1) {
        uVar4 = CreateLabelWidget(0,0x4b0,0xe,0x1fc,0x40,0x17);
        Widget_AddChild(uVar4);
      }
    }
    else {
      uVar3 = Widget_FindChildIndex();
      if (uVar3 != 0xffffffff) {
        if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        Widget_RemoveChild();
      }
      iVar2 = Widget_FindChildIndex();
      if (iVar2 == -1) {
        uVar4 = CreateLabelWidget(3,0x4b3,0xe,0x1fc,0x40,0x17);
        Widget_AddChild(uVar4);
        return;
      }
    }
  }
  return;
}

