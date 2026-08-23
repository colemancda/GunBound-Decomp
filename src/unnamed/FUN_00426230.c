/* FUN_00426230 - 0x00426230 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the client context
 * arrives in EAX (`mov esi,eax` at 0x42623d) - Ghidra kept the artifact name
 * in_EAX and even used it (`in_EAX + 0x23330`), so it is simply made the
 * parameter.  The peek reads ctx + 0x6aa67c (the elapsed-time cell; the body
 * formats it as h:m).  All 6 callers pass g_clientContext now.
 */
#include "ghidra_types.h"


void FUN_00426230(int in_EAX)

{
  int iVar1;
  uint uVar2;
  char *_Format;
  undefined4 uVar3;
  int iVar4;
  char local_400 [1024];
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(in_EAX + 0x6aa67c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar2 = (uint)(iVar1 / 0x14) / 0xe10;
  iVar4 = in_EAX + 0x23330;
  uVar3 = (undefined4)(((ulonglong)(uint)(iVar1 / 0x14) % 0xe10) / 0x3c);
  _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x204);
  _sprintf(local_400,_Format,iVar4,uVar2,uVar3);
  (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_400,2,6);
  return;
}

