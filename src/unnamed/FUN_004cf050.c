/* FUN_004cf050 - 0x004cf050 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004cf050(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  uint local_10;
  int local_c;
  int local_8;
  int local_4;
  
  if (*(int *)(param_2 + 0x10b0) < 8) {
    *(undefined1 *)(*(int *)(param_2 + 0x10b0) + 0x10a8 + param_2) = param_1;
    *(int *)(param_2 + 0x10b0) = *(int *)(param_2 + 0x10b0) + 1;
    local_8 = 0;
    local_4 = 0;
    local_10 = 0;
    local_c = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 != -1) {
        iVar3 = 0;
        if (0 < *(int *)(param_2 + 0x10b0)) {
          do {
            if (*(byte *)(param_2 + 0x10a8 + iVar3) == local_10) break;
            iVar3 = iVar3 + 1;
          } while (iVar3 < *(int *)(param_2 + 0x10b0));
        }
        if (iVar3 == *(int *)(param_2 + 0x10b0)) {
          cVar2 = *(char *)(g_clientContext + 0x4590c + local_10);
          if (cVar2 == '\0') {
            local_8 = local_8 + 1;
          }
          else if (cVar2 == '\x01') {
            local_4 = local_4 + 1;
          }
        }
      }
      local_10 = local_10 + 1;
      local_c = local_c + 0x224;
    } while (local_c < 0x1120);
    if ((local_8 != 0) && (local_4 != 0)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 != 1) {
        return;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar3 != 0) {
          return;
        }
      }
    }
    iVar3 = g_clientContext;
    pbVar6 = (byte *)(g_clientContext + 0x6214c);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *pbVar6 = (byte)iVar4;
    iVar4 = _rand();
    bVar1 = *pbVar6;
    *(byte *)(iVar3 + 0x6214d) = (byte)iVar4;
    bVar5 = '\x01' << (bVar1 & 7);
    bVar5 = ~bVar5 & (byte)iVar4 | bVar5;
    *(byte *)(iVar3 + 0x6214d) = bVar5;
    *(byte *)(iVar3 + 0x6214e) = bVar5 + bVar1 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (iVar3 == iVar4) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if ((((iVar3 == 3) || (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) &&
            (cVar2 = PeekPacketChecksumBool(), cVar2 == '\0')) && (cVar2 = DecodeGuardedBool(), cVar2 == '\0')) {
          FUN_00413bf0();
        }
      }
    }
  }
  return;
}

