/* FUN_004e6160 - 0x004e6160 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004e6160(int param_1)

{
  uint3 uVar1;
  short sVar2;
  char cVar3;
  uint uVar4;
  DWORD DVar5;
  int iVar6;
  undefined4 extraout_EDX;
  short sVar7;
  ushort *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  bool bVar11;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined1 local_26c;
  short local_268;
  uint local_264;
  int local_260;
  uint local_25c;
  sockaddr local_258;
  ushort local_248;
  short sStack_246;
  char local_244;
  byte local_243;
  char local_242;
  char local_241;
  char cStack_240;
  undefined2 uStack_23f;
  undefined4 local_23b;
  undefined4 local_237;
  undefined4 local_233;
  undefined4 local_22f;
  undefined4 local_22b;
  short local_227;
  char local_225;
  undefined1 local_48 [68];
  
  puVar8 = &local_248;
  for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
    puVar8[0] = 0;
    puVar8[1] = 0;
    puVar8 = puVar8 + 2;
  }
  local_260 = 0x10;
  uVar4 = recvfrom(*(SOCKET *)(param_1 + 0x14),(char *)&local_248,0x200,0,&local_258,&local_260);
  local_264 = uVar4;
  if ((int)uVar4 < 0) {
    iVar6 = WSAGetLastError();
    if (iVar6 == 0x2733) {
      return 1;
    }
    if (iVar6 == 0x2746) {
      return 1;
    }
    return 0;
  }
  if (uVar4 == 4) {
    if (*(int *)(param_1 + 0x45208) < 1) {
      return 1;
    }
    if (CONCAT22(sStack_246,local_248) != *(int *)(param_1 + 0x45212)) {
      return 1;
    }
    *(undefined4 *)(param_1 + 0x45208) = 0xffffffff;
    if (*(int *)(param_1 + 0x44ff0) == 0) {
      return 1;
    }
    FUN_004e5dc0(3,0);
    return 1;
  }
  if ((uVar4 != local_248) || ((int)uVar4 < 0x21)) {
    *(undefined1 *)(param_1 + 0x4527c) = 1;
    return 1;
  }
  if (local_242 != *(char *)(param_1 + 0x14c)) {
    *(undefined1 *)(param_1 + 0x4527c) = 2;
    return 1;
  }
  if (7 < local_243) goto LAB_004e6760;
  if (((*(uint *)(param_1 + 0x140 + (uint)(local_243 >> 5) * 4) & 1 << (local_243 & 0x1f)) == 0) ||
     (8 < local_243)) {
    *(undefined1 *)(param_1 + 0x4527c) = 3;
    return 1;
  }
  local_278 = local_233;
  local_274 = local_22f;
  local_270 = local_22b;
  local_26c = 0;
  iVar6 = __stricmp((char *)&local_278,(char *)(param_1 + 0x15d));
  if (iVar6 != 0) {
    *(undefined1 *)(param_1 + 0x4527c) = 4;
    return 1;
  }
  local_270 = local_237;
  local_274 = local_23b;
  local_26c = 0;
  iVar6 = __stricmp((char *)&local_278,(char *)(param_1 + (local_243 + 5) * 0x18));
  if ((iVar6 != 0) || (cVar3 = FUN_00426430(), sVar7 = sStack_246, cVar3 == '\x01')) {
    *(undefined1 *)(param_1 + 0x4527c) = 5;
    return 1;
  }
  uVar1 = CONCAT12(local_244,sStack_246);
  local_268 = sStack_246;
  if (sStack_246 != 0) {
    DAT_0056dca5 = (undefined1)sStack_246;
    DAT_0056dcaa = (undefined1)((ushort)sStack_246 >> 8);
    DAT_0056dca7 = cStack_240;
    FUN_004e6f20(&local_227,uVar4 - 0x21);
  }
  sVar2 = local_268;
  iVar6 = 0x21;
  cVar3 = (char)((ushort)sStack_246 >> 8) + (char)sStack_246 + cStack_240 + -0x34;
  if (0x21 < (int)uVar4) {
    do {
      cVar3 = cVar3 + *(char *)((int)&local_248 + iVar6);
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)uVar4);
  }
  if (local_244 != cVar3) {
    *(undefined1 *)(param_1 + 0x4527c) = 6;
    return 1;
  }
  *(undefined4 *)(param_1 + 0x18 + (uint)local_243 * 4) = SUBFIELD(local_258.sa_data,2,undefined4);
  *(undefined2 *)(param_1 + 0x58 + (uint)local_243 * 2) = SUBFIELD(local_258.sa_data,0,undefined2);
  *(undefined4 *)(param_1 + 0x38 + (uint)local_243 * 4) = 0xffffffff;
  local_25c = uVar1 & 0x8000;
  *(undefined2 *)(param_1 + 0x68 + (uint)local_243 * 2) = 0xffff;
  if ((short)local_25c == -0x8000) {
    iVar6 = 0x80;
    bVar11 = true;
    puVar8 = &local_248;
    piVar9 = (int *)((uint)local_243 * 0x200 + 0x41bd8 + param_1);
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *(int *)puVar8 == *piVar9;
      puVar8 = puVar8 + 2;
      piVar9 = piVar9 + 1;
    } while (bVar11);
    if (bVar11) {
      FUN_004e6d10(CONCAT13(local_243,CONCAT12(local_244,sStack_246)),
                   CONCAT22(uStack_23f,CONCAT11(cStack_240,local_241)));
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
      SendUdpDatagram(local_48,0x24);
      if (*(int *)(param_1 + 0x38 + (uint)local_243 * 4) != -1) {
        SendUdpDatagram(local_48,0x24);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
      return 1;
    }
    if (local_241 != *(char *)(local_243 + 0x3c0 + param_1)) {
      *(undefined1 *)(param_1 + 0x4527c) = 7;
      return 1;
    }
LAB_004e64e4:
    if (local_268 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x45264));
      *(byte *)(param_1 + 0x1b4) = local_243;
      *(short *)(param_1 + 0x1b0) = sVar2;
      *(short *)(param_1 + 0x1b2) = (short)local_264;
      puVar8 = &local_248;
      puVar10 = (undefined4 *)(param_1 + 0x1b5);
      for (uVar4 = local_264 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar10 = *(undefined4 *)puVar8;
        puVar8 = puVar8 + 2;
        puVar10 = puVar10 + 1;
      }
      for (uVar4 = local_264 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(char *)puVar10 = (char)*puVar8;
        puVar8 = (ushort *)((int)puVar8 + 1);
        puVar10 = (undefined4 *)((int)puVar10 + 1);
      }
      FUN_004e8f70((short *)(param_1 + 0x1b0));
      sVar7 = (short)local_25c;
      if (sVar7 != 0) {
        *(char *)(local_243 + 0x3c0 + param_1) = *(char *)(local_243 + 0x3c0 + param_1) + '\x01';
        DAT_0056d3dc = 0xffffffff;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x45264));
      if ((sVar7 != 0) && (*(char *)(param_1 + 0x454f8) == '\0')) {
        EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
        FUN_004e6d10(CONCAT13(local_243,CONCAT12(local_244,sStack_246)),
                     CONCAT22(uStack_23f,CONCAT11(cStack_240,local_241)));
        SendUdpDatagram(extraout_EDX,0x24);
        if (*(int *)(param_1 + 0x38 + (uint)local_243 * 4) != -1) {
          SendUdpDatagram(local_48,0x24);
        }
        puVar8 = &local_248;
        puVar10 = (undefined4 *)((uint)local_243 * 0x200 + 0x41bd8 + param_1);
        for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar10 = *(undefined4 *)puVar8;
          puVar8 = puVar8 + 2;
          puVar10 = puVar10 + 1;
        }
        LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x17c));
      }
      if (local_268 != -0x6000) {
        if (local_268 != -0x5fff) {
          return 1;
        }
        DVar5 = timeGetTime();
        *(DWORD *)(param_1 + 0x454c4 + (uint)local_243 * 4) =
             DVar5 - *(int *)(param_1 + 0x45240 + (uint)local_243 * 4) >> 1;
        return 1;
      }
      QueueBroadcastEvent(0xa001);
      FUN_004e7140(local_243);
      return 1;
    }
  }
  else if (sVar7 != 0) {
    iVar6 = 0x80;
    bVar11 = true;
    puVar8 = &local_248;
    piVar9 = (int *)(param_1 + 0x42bd8);
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar11 = *(int *)puVar8 == *piVar9;
      puVar8 = puVar8 + 2;
      piVar9 = piVar9 + 1;
    } while (bVar11);
    if (bVar11) {
      return 1;
    }
    puVar8 = &local_248;
    piVar9 = (int *)(param_1 + 0x42bd8);
    for (iVar6 = 0x80; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = *(int *)puVar8;
      puVar8 = puVar8 + 2;
      piVar9 = piVar9 + 1;
    }
    goto LAB_004e64e4;
  }
  if ((*(int *)(param_1 + 0x44de0) != 0) &&
     (*(short *)(param_1 + 0x45284 + (uint)local_243 * 2) == local_227)) {
    cVar3 = FUN_00426430();
    if ((cVar3 == '\x01') && (local_225 == *(char *)(local_243 + 0x45294 + param_1))) {
      if ((local_243 < 8) &&
         (*(uint *)(param_1 + 0x13c + (uint)(local_243 >> 5) * 4) =
               *(uint *)(param_1 + 0x13c + (uint)(local_243 >> 5) * 4) | 1 << (local_243 & 0x1f),
         local_243 < 8)) {
        *(uint *)(param_1 + 0x144 + (uint)(local_243 >> 5) * 4) =
             *(uint *)(param_1 + 0x144 + (uint)(local_243 >> 5) * 4) & ~(1 << (local_243 & 0x1f));
        FUN_004e77e0(param_1);
        return 1;
      }
LAB_004e6760:
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
  }
  return 1;
}

