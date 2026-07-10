/* FUN_00426230 - 0x00426230 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00426230(void)

{
  int in_EAX;
  int iVar1;
  uint uVar2;
  char *_Format;
  undefined4 uVar3;
  int iVar4;
  char local_400 [1024];
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = (uint)(iVar1 / 0x14) / 0xe10;
  iVar4 = in_EAX + 0x23330;
  uVar3 = (undefined4)(((ulonglong)(uint)(iVar1 / 0x14) % 0xe10) / 0x3c);
  _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x204);
  _sprintf(local_400,_Format,iVar4,uVar2,uVar3);
  (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_400,2,6);
  return;
}

