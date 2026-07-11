/* FUN_0050a030 - 0x0050a030 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_0050a030(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  
  puVar1 = g_gameStateVTableArray[7];
  if ((*(char *)(param_1 + 0x90) != '\0') && (*(int *)(param_1 + 0x94) == -1)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(int *)(param_1 + 0x94) = *(int *)(puVar1 + 0x454) + iVar3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0xffffffff);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RadioGroup_RefreshEnableStates(param_1);
    if (*(uint *)(g_clientContext + 0x44e24) <= *(uint *)(param_1 + 0x94)) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_004240c0(g_clientContext,(uVar4 & 0x8000) == 0x8000,(int)uVar4 >> 0x10,uVar4 & 0x7fff);
  }
  cVar2 = Widget_MouseMoveChildren(param_2,param_3);
  if ((cVar2 == '\0') &&
     ((((*(char *)(param_1 + 0x1e) != '\0' || (param_2 <= *(int *)(param_1 + 0x28))) ||
       (*(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28) <= param_2)) ||
      ((param_3 <= *(int *)(param_1 + 0x2c) ||
       (*(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c) <= param_3)))))) {
    return 0;
  }
  return 1;
}

