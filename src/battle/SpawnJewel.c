/* SpawnJewel - 0x00438410 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00438410).  Places one JEWEL - the collectible
 * that sits on the terrain and chain-detonates when a blast reaches it.
 * Evidence:
 *   - operator_new(0x2298), constructed by InitJewel, then two guarded
 *     writes: EncodeOutgoingPacketField at int index 0x97 = BYTE +0x25c gets
 *     param_2 (the X - its AdvanceTurnQueue caller passes
 *     `x % g_nCameraBoundX`), and index 0xe = byte +0x38 gets param_3 (the
 *     TYPE, which also drives a switch selecting 300 / 200 / a peeked value).
 *   - the sprite name is built with sprintf("jewel%d", param_3 + 1)
 *     (s_jewel_d_00553bd4) and the object's state is set to "normal".
 *   - both callers are placement points: AdvanceTurnQueue (between turns) and
 *     State11_InBattle_OnEnter (initial layout).
 * The object it produces is the layer-100006 entity HitTestJewel looks up and
 * ApplyBlastDamage's second pass damages; its guard block is three
 * consecutive 0x224-byte CValueGuard cells - +0x38 type, +0x25c X, +0x480 Y.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 10 argless sites.  Seven of them are offsets off ESI, which
 * 0x438514 sets from the freshly constructed object (`mov esi,eax` right
 * after the InitJewel call) -- that is piVar6, and since piVar6 is an
 * `int *` the byte offsets divide by 4: +0x25c -> +0x97 (C97), +0x38 ->
 * +0xe (C100), +0x6a4 -> +0x1a9 (C121), +0x480 -> +0x120 (C152, C155,
 * C179) and +0x19f4 -> +0x67d (C182).  C114 (0x4385ad) reads the standalone
 * global cell 0x796aa0, and the C162/C163 peek+encode pair (0x43887e /
 * 0x438885, one `inc eax` apart) both work on g_clientContext + 0x6a7f94.
 *
 * The sites do NOT sit in address order: the param_4 != 0 arm (C179/C182)
 * is emitted FIRST, at 0x438699 / 0x4386b4, ahead of the param_4 == 0 arm
 * (C152/C155 at 0x438826 / 0x43883b).  They were matched by landmark --
 * `cmp eax,0x2328` (the `9000 < iVar8` test) follows 0x43883b, and
 * `push 0x553bcc` (&DAT_00553bcc) follows 0x4386b4.
 */
#include "ghidra_types.h"


void SpawnJewel(undefined4 param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  void *pvVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  char *pcVar9;
  undefined4 *puVar10;
  byte bVar11;
  uint uVar12;
  undefined4 *unaff_FS_OFFSET;
  bool bVar13;
  int local_94;
  char local_8c [128];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cf6e;
  *unaff_FS_OFFSET = &local_c;
  cVar3 = PeekPacketChecksumBool((byte *)(param_1 + 4));
  if (cVar3 != '\0') goto LAB_004388b4;
  iVar8 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar12 = 0;
  while (uVar1 = *(uint *)(iVar8 + 4), iVar4 = iVar8, uVar1 < 0x186a7) {
    while (uVar1 != 0x186a6) {
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(uint *)(iVar4 + 4);
      if (0x186a6 < uVar1) goto LAB_0043848e;
    }
    iVar4 = *(int *)(iVar4 + 0x10);
    bVar13 = *(uint *)(iVar4 + 8) == uVar12;
    if (uVar12 <= *(uint *)(iVar4 + 8) && !bVar13) break;
    while (!bVar13) {
      iVar4 = *(int *)(iVar4 + 0x10);
      bVar13 = *(uint *)(iVar4 + 8) == uVar12;
      if (uVar12 < *(uint *)(iVar4 + 8)) goto LAB_0043848e;
    }
    uVar12 = uVar12 + 1;
    if (7 < (int)uVar12) break;
  }
LAB_0043848e:
  if (uVar12 == 8) goto LAB_004388b4;
  uVar1 = uVar12 + 8;
  uVar2 = *(uint *)(iVar8 + 4);
  while (uVar2 < 0x7a121) {
    if (uVar2 == 500000) {
      puVar10 = *(undefined4 **)(iVar8 + 0x10);
      uVar2 = puVar10[2];
      if (uVar2 <= uVar1) goto LAB_004384c7;
      break;
    }
    iVar8 = *(int *)(iVar8 + 0x1c);
    uVar2 = *(uint *)(iVar8 + 4);
  }
  goto LAB_004384ed;
  while( true ) {
    puVar10 = (undefined4 *)puVar10[4];
    uVar2 = puVar10[2];
    if (uVar1 < uVar2) break;
LAB_004384c7:
    if (uVar2 == uVar1) {
      *(undefined4 *)(puVar10[3] + 0x10) = puVar10[4];
      *(undefined4 *)(puVar10[4] + 0xc) = puVar10[3];
      (**(code **)*puVar10)(1);
      break;
    }
  }
LAB_004384ed:
  pvVar5 = operator_new(0x2298);
  local_4 = 0;
  if (pvVar5 == (void *)0x0) {
    piVar6 = (int *)0x0;
  }
  else {
    piVar6 = (int *)InitJewel(pvVar5,uVar12);
  }
  local_4 = 0xffffffff;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(piVar6 + 0x97), param_2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)(piVar6 + 0xe), param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  switch(param_3) {
  case 0:
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar7 = 300;
    break;
  case 1:
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar7 = 200;
    break;
  case 2:
  case 3:
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar7 = PeekPacketChecksumState((void *)(&DAT_00796aa0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    break;
  default:
    goto switchD_0043857e_default;
  }
  EncodeOutgoingPacketField((void *)(piVar6 + 0x1a9), uVar7);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
switchD_0043857e_default:
  _sprintf(local_8c,s_jewel_d_00553bd4,param_3 + 1);
  iVar8 = FindPreloadedTextureByName(local_8c);
  piVar6[7] = iVar8;
  if (param_4 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar8 = _rand();
    *(char *)(piVar6 + 0x706) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)((int)piVar6 + 0x1c19) = (byte)iVar8;
    bVar11 = *(byte *)(piVar6 + 0x706) & 7;
    bVar11 = ~('\x01' << bVar11) & (byte)iVar8 | '\0' << bVar11;
    *(byte *)((int)piVar6 + 0x1c19) = bVar11;
    *(byte *)((int)piVar6 + 0x1c1a) = bVar11 + *(byte *)(piVar6 + 0x706) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if ((-1 < param_2) && (param_2 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar9 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + param_2);
      local_94 = 0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar9 != '\0') goto LAB_00438814;
          pcVar9 = pcVar9 + *(int *)(&g_nCameraBoundX + g_clientContext);
          local_94 = local_94 + 1;
        } while (local_94 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    local_94 = 10000;
LAB_00438814:
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(piVar6 + 0x120), local_94);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar8 = PeekPacketChecksumState((void *)(piVar6 + 0x120));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (9000 < iVar8) {
      (**(code **)*piVar6)(1);
      goto LAB_004388b4;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar8 = PeekPacketChecksumState((void *)(g_clientContext + 0x6a7f94));
    EncodeOutgoingPacketField((void *)(g_clientContext + 0x6a7f94), iVar8 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (**(code **)(*piVar6 + 4))(s_normal_00552230);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar8 = _rand();
    *(char *)(piVar6 + 0x706) = (char)iVar8;
    iVar8 = _rand();
    *(byte *)((int)piVar6 + 0x1c19) = (byte)iVar8;
    bVar11 = '\x01' << (*(byte *)(piVar6 + 0x706) & 7);
    bVar11 = ~bVar11 & (byte)iVar8 | bVar11;
    *(byte *)((int)piVar6 + 0x1c19) = bVar11;
    *(byte *)((int)piVar6 + 0x1c1a) = bVar11 + *(byte *)(piVar6 + 0x706) + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(piVar6 + 0x120), 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)(piVar6 + 0x67d), 0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    (**(code **)(*piVar6 + 4))(&DAT_00553bcc);
    uVar12 = DAT_005b3480 * 0xda003 + 0x5703b11;
    DAT_005b3480 = DAT_005b3480 + (uVar12 * 0x61 + 0x61) % 0xf4241;
    if ((uVar12 & 1) != 0) {
      uVar12 = DAT_005b3480 * 0xda003 + 0x5703b11;
      DAT_005b3480 = DAT_005b3480 + (uVar12 * 0x61 + 0x61) % 0xf4241;
      pcVar9 = (char *)GetLocalizedString(&g_localizedStringTable,uVar12 % 10 + 0x803);
      SpawnSpeechBalloon((int)uVar1,g_clientContext + 0x6a7f70,pcVar9);
    }
  }
  RegisterActiveObject(0, 0, (undefined4 *)0);
LAB_004388b4:
  *unaff_FS_OFFSET = local_c;
  return;
}

