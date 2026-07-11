/* CheckAllPlayersReady - 0x004db4b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall CheckAllPlayersReady(int param_1)

{
  char cVar1;
  uint3 uVar3;
  int iVar2;
  uint3 extraout_var;
  int extraout_ECX;
  int iVar4;
  int iVar5;
  
  if (0 < (int)*(uint *)(param_1 + 0x628)) {
    return *(uint *)(param_1 + 0x628) & 0xffffff00;
  }
  TallyRoomTeamStats();
  if ((((*(char *)(g_clientContext + 0x45122) == '\0') ||
       (*(int *)(extraout_ECX + 0x490) == *(int *)(extraout_ECX + 0x494))) ||
      (uVar3 = (uint3)((uint)*(int *)(extraout_ECX + 0x490) >> 8),
      *(char *)(g_clientContext + 0x45120) == '\0')) &&
     ((uVar3 = 0, *(int *)(extraout_ECX + 0x490) < 5 && (*(int *)(extraout_ECX + 0x494) < 5)))) {
    iVar5 = 0;
    iVar4 = g_clientContext;
    do {
      cVar1 = *(char *)(iVar4 + 0x45914 + iVar5);
      if ((cVar1 != '\0') && (cVar1 != '\x03')) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar2 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = g_clientContext;
        uVar3 = extraout_var;
        if (iVar5 != iVar2) {
          return (uint)extraout_var << 8;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    return CONCAT31(uVar3,1);
  }
  return (uint)uVar3 << 8;
}

