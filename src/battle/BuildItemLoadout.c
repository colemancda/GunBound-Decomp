/* BuildItemLoadout - 0x004dbd50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls - the acting-slot
 * cell g_clientContext + 0x3b49c and its partner + 0x3b6c4, peeked back
 * to back under one lock (0x4dbe75 / 0x4dbe7e).
 */
#include "ghidra_types.h"


void BuildItemLoadout(int *param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  char *_Format;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  char local_80 [128];
  
  iVar3 = g_clientContext;
  *(undefined4 *)(g_clientContext + 0x457a3) = 0;
  *(undefined2 *)(iVar3 + 0x457a7) = 0;
  *(byte *)(iVar3 + 0x457a2) = *(byte *)(iVar3 + 0x457a2) & 0xe0;
  uVar6 = 0;
  do {
    bVar1 = (byte)(0x80 >> (sbyte)((ulonglong)uVar6 % 8));
    bVar8 = (*(byte *)(uVar6 / 8 + 0x457a1 + iVar3) & bVar1) == bVar1;
    if ((bVar8 != (bool)*(char *)(uVar6 + 0x4d8 + (int)param_1)) && (param_2 == '\x01')) {
      if (bVar8) {
        uVar2 = FindItemRecordByIcon(iVar3,g_awItemIconTable[uVar6]);
        _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x278);
      }
      else {
        uVar2 = FindItemRecordByIcon(iVar3,g_awItemIconTable[uVar6]);
        _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x279);
      }
      _sprintf(local_80,_Format,uVar2);
      (**(code **)(*param_1 + 0x28))(local_80,2,6);
      iVar3 = g_clientContext;
    }
    *(bool *)(uVar6 + 0x4d8 + (int)param_1) = bVar8;
    if ((!bVar8) && ((int)uVar6 < 0xb)) {
      ResetItemSlotCounters(g_awItemIconTable[uVar6]);
      iVar3 = g_clientContext;
    }
    uVar6 = uVar6 + 1;
  } while ((int)uVar6 < 0x40);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b49c));
  iVar4 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b6c4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar3 == iVar4) {
    iVar3 = 0;
    piVar5 = param_1 + 0x146;
    do {
      *piVar5 = iVar3;
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar3 < 0x40);
    param_1[0x187] = 0x40;
  }
  else {
    iVar3 = 0;
    param_1[0x187] = 0;
    piVar5 = param_1 + 0x146;
    iVar7 = 0x40;
    iVar4 = iVar3;
joined_r0x004dbed5:
    do {
      if (iVar4 < 0x40) {
        if (*(char *)(iVar4 + 0x4d8 + (int)param_1) == '\0') {
          iVar3 = iVar3 + 1;
          iVar4 = iVar4 + 1;
          goto joined_r0x004dbed5;
        }
        param_1[0x187] = param_1[0x187] + 1;
        *piVar5 = iVar3;
        iVar3 = iVar3 + 1;
      }
      piVar5 = piVar5 + 1;
      iVar7 = iVar7 + -1;
      iVar4 = iVar3;
    } while (iVar7 != 0);
  }
  if (0xb < param_1[0x187]) {
    param_1[0x187] = 0xb;
  }
  return;
}

