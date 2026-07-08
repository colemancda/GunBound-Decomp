/* State10_Loading_OnEnter - 0x0043e840 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall State10_Loading_OnEnter(int param_1)

{
  char *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  byte bVar11;
  int iVar12;
  byte *pbVar13;
  undefined4 *puVar14;
  undefined1 auStack_108 [8];
  char acStack_100 [128];
  char acStack_80 [128];
  
  FUN_004f1790(&DAT_00ea0e18,10000);
  *(undefined4 *)(param_1 + 4) = 0;
  iVar12 = g_clientContext;
  pbVar13 = &DAT_006a9b6c + g_clientContext;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar13 = (byte)iVar5;
  iVar5 = _rand();
  bVar2 = *pbVar13;
  (&DAT_006a9b6d)[iVar12] = (byte)iVar5;
  bVar11 = bVar2 & 7;
  bVar11 = ~('\x01' << bVar11) & (byte)iVar5 | '\0' << bVar11;
  (&DAT_006a9b6d)[iVar12] = bVar11;
  (&DAT_006a9b6e)[iVar12] = bVar2 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar12 = g_clientContext;
  pbVar13 = (byte *)(g_clientContext + 0x6214f);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar13 = (byte)iVar5;
  iVar5 = _rand();
  bVar2 = *pbVar13;
  *(byte *)(iVar12 + 0x62150) = (byte)iVar5;
  bVar11 = bVar2 & 7;
  bVar11 = ~('\x01' << bVar11) & (byte)iVar5 | '\0' << bVar11;
  *(byte *)(iVar12 + 0x62150) = bVar11;
  *(byte *)(iVar12 + 0x62151) = bVar2 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar12 = g_clientContext;
  pbVar13 = (byte *)(g_clientContext + 0x62152);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar13 = (byte)iVar5;
  iVar5 = _rand();
  bVar2 = *pbVar13;
  *(byte *)(iVar12 + 0x62153) = (byte)iVar5;
  bVar11 = bVar2 & 7;
  bVar11 = ~('\x01' << bVar11) & (byte)iVar5 | '\0' << bVar11;
  *(byte *)(iVar12 + 0x62153) = bVar11;
  *(byte *)(iVar12 + 0x62154) = bVar2 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00420280(g_clientContext);
  iVar12 = g_clientContext;
  puVar14 = (undefined4 *)(&DAT_006a7670 + g_clientContext);
  for (iVar5 = 0x20; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar14 = 0;
    puVar14 = puVar14 + 1;
  }
  *(undefined4 *)(g_gameStateVTableArray[0xb] + 0x10b8) = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *(byte *)(iVar12 + 0x62149) = (byte)iVar5;
  iVar5 = _rand();
  bVar2 = *(byte *)(iVar12 + 0x62149);
  *(byte *)(iVar12 + 0x6214a) = (byte)iVar5;
  bVar11 = bVar2 & 7;
  bVar11 = ~('\x01' << bVar11) & (byte)iVar5 | '\0' << bVar11;
  *(byte *)(iVar12 + 0x6214a) = bVar11;
  *(byte *)(iVar12 + 0x6214b) = bVar2 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar12 = g_clientContext;
  pbVar13 = (byte *)(g_clientContext + 0x6214c);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = _rand();
  *pbVar13 = (byte)iVar5;
  iVar5 = _rand();
  bVar2 = *pbVar13;
  *(byte *)(iVar12 + 0x6214d) = (byte)iVar5;
  bVar11 = bVar2 & 7;
  bVar11 = ~('\x01' << bVar11) & (byte)iVar5 | '\0' << bVar11;
  *(byte *)(iVar12 + 0x6214d) = bVar11;
  *(byte *)(iVar12 + 0x6214e) = bVar2 + bVar11 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar6 = (char *)(g_clientContext + 0x45914);
  iVar12 = 8;
  do {
    if (*pcVar6 != '\0') {
      *pcVar6 = '\x04';
    }
    pcVar6 = pcVar6 + 1;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  switch(uVar7) {
  case 0:
    pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,800);
    pcVar10 = (char *)(param_1 + 8);
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar10 = cVar3;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
    break;
  case 1:
    pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,0x321);
    pcVar10 = (char *)(param_1 + 8);
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar10 = cVar3;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
    break;
  case 2:
    pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,0x322);
    pcVar10 = (char *)(param_1 + 8);
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar10 = cVar3;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
    break;
  case 3:
    pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,0x323);
    pcVar10 = (char *)(param_1 + 8);
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar10 = cVar3;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
  }
  uVar8 = (uint)(*(byte *)(g_clientContext + 0x45124) >> 1);
  uVar9 = uVar8;
  pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,0x324);
  _sprintf(acStack_100,pcVar6,uVar8,uVar9);
  pcVar6 = acStack_100;
  do {
    cVar3 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar3 != '\0');
  uVar9 = (int)pcVar6 - (int)acStack_100;
  pcVar6 = (char *)(param_1 + 7);
  do {
    pcVar10 = pcVar6 + 1;
    pcVar6 = pcVar6 + 1;
  } while (*pcVar10 != '\0');
  pcVar10 = acStack_100;
  for (uVar8 = uVar9 >> 2; iVar12 = g_clientContext, uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar6 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar6 = pcVar6 + 1;
  }
  cVar3 = *(char *)(iVar12 + 0x45123);
  if (cVar3 == '\0') {
    pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x325);
    pcVar6 = pcVar10;
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar3 != '\0');
    uVar9 = (int)pcVar6 - (int)pcVar10;
    pcVar6 = (char *)(param_1 + 7);
    do {
      pcVar1 = pcVar6 + 1;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar1 != '\0');
LAB_0043eca8:
    for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar6 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  else {
    if (cVar3 == '\x01') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x326);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
      goto LAB_0043eca8;
    }
    if (cVar3 == '\x02') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x327);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
      goto LAB_0043eca8;
    }
  }
  cVar3 = *(char *)(g_clientContext + 0x45126);
  if (cVar3 == '\0') {
    pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x328);
    pcVar6 = pcVar10;
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar3 != '\0');
    uVar9 = (int)pcVar6 - (int)pcVar10;
    pcVar6 = (char *)(param_1 + 7);
    do {
      pcVar1 = pcVar6 + 1;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar1 != '\0');
LAB_0043ed58:
    for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar6 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  else {
    if (cVar3 == '\x01') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x329);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
      goto LAB_0043ed58;
    }
    if (cVar3 == '\x02') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x32a);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
      goto LAB_0043ed58;
    }
  }
  if (*(char *)(g_clientContext + 0x45127) == '\0') {
    pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x32b);
    pcVar6 = pcVar10;
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar3 != '\0');
    uVar9 = (int)pcVar6 - (int)pcVar10;
    pcVar6 = (char *)(param_1 + 7);
    do {
      pcVar1 = pcVar6 + 1;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar1 != '\0');
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pcVar6 = (char *)FUN_0043dc70(&DAT_00796eec,0x32c);
    _sprintf(acStack_80,pcVar6,uVar7);
    pcVar6 = acStack_80;
    do {
      cVar3 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar3 != '\0');
    uVar9 = (int)pcVar6 - (int)acStack_80;
    pcVar6 = (char *)(param_1 + 7);
    do {
      pcVar10 = pcVar6 + 1;
      pcVar6 = pcVar6 + 1;
    } while (*pcVar10 != '\0');
    pcVar10 = acStack_80;
    for (uVar8 = uVar9 >> 2; iVar12 = g_clientContext, uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar6 = pcVar6 + 4;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pcVar6 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar6 = pcVar6 + 1;
    }
    cVar3 = *(char *)(iVar12 + 0x45127);
    if (cVar3 == '\x01') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x32d);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
    }
    else if (cVar3 == '\x02') {
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x32e);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
    }
    else {
      if (cVar3 != '\x03') goto LAB_0043eec8;
      pcVar10 = (char *)FUN_0043dc70(&DAT_00796eec,0x32f);
      pcVar6 = pcVar10;
      do {
        cVar3 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar3 != '\0');
      uVar9 = (int)pcVar6 - (int)pcVar10;
      pcVar6 = (char *)(param_1 + 7);
      do {
        pcVar1 = pcVar6 + 1;
        pcVar6 = pcVar6 + 1;
      } while (*pcVar1 != '\0');
    }
  }
  for (uVar8 = uVar9 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
    pcVar10 = pcVar10 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
    *pcVar6 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    pcVar6 = pcVar6 + 1;
  }
LAB_0043eec8:
  iVar12 = g_clientContext;
  *(undefined4 *)(param_1 + 0x108) = 0xffffffff;
  FUN_004f18c0(&DAT_00ea0e18,0x2711,(uint)*(byte *)(iVar12 + 0x475c4) << 1);
  FUN_004f18c0(&DAT_00ea0e18,0x2711,(uint)*(byte *)(g_clientContext + 0x475c4) * 2 + 1);
  *(undefined1 *)(param_1 + 0x14c) = 0;
  iVar12 = g_clientContext;
  puVar14 = (undefined4 *)(&DAT_006a76f4 + g_clientContext);
  if (*(void **)(&DAT_006a76f4 + g_clientContext) != (void *)0x0) {
    _free(*(void **)(&DAT_006a76f4 + g_clientContext));
    *puVar14 = 0;
  }
  iVar4 = DAT_007934e4;
  iVar5 = g_clientContext;
  *(undefined4 *)(&DAT_006a76f8 + iVar12) = 0;
  *(undefined4 *)(&DAT_006a76fc + iVar12) = 0;
  *(undefined4 *)(&DAT_006a7704 + iVar5) = 0xffffffff;
  *(undefined1 *)(iVar4 + 8) = 1;
  _DAT_00e9af1c = 500;
  FUN_004e8ad0(*(undefined4 *)(DAT_00e9af14 + 4));
  *(int *)(DAT_00e9af14 + 4) = DAT_00e9af14;
  _DAT_00e9af18 = 0;
  *(int *)DAT_00e9af14 = DAT_00e9af14;
  *(int *)(DAT_00e9af14 + 8) = DAT_00e9af14;
  FUN_004e86f0(auStack_108);
  FUN_004e86f0(auStack_108);
  return;
}

