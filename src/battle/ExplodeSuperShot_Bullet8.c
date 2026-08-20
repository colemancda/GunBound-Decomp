/* ExplodeSuperShot_Bullet8 - 0x004837e0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004837e0): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 7's super shot (texture bullet8p; vtable 0x5561c8, ctor InitSuperShot_Bullet8
 * reached only through SpawnSuperShot's case 7). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 26 argless PeekPacketChecksumState() calls (worklist 26:26).
 * this=EBX for the whole function (`lea ebx,[ebx]` at 0x48385a is a nop),
 * so the projectile cells are this-relative: +0x1178/+0xf54 (position),
 * +0x3198/+0x35ec/+0x33c8 (the three spawn parameters), +0x17e4.  The
 * three peeks whose cell the resolver saw as clobbered (0x483929,
 * 0x483b28, 0x483dcd) read the object returned by the preceding
 * HitTestLocalMobile / HitTestJewel / HitTestMine call (`mov edi,eax` -> `lea
 * eax,[edi+N]`): record+0x90c, object+0x25c, object+0x40 - the C's iVar5
 * before its own reassignment on the same line.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet8(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  byte *pbVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char local_19;
  int local_18;
  int local_10;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* RECOVERED (2026-08-19): the two dropped __fastcall register
   * arguments (orig 0x483847 mov cl,1 / 0x483849 xor edx,edx).  param_1 is the randomise flag,
   * param_2 the sub-effect index (the callee caps it at < 4).  The third
   * register argument, EAX, needs nothing here: the 2026-08-17 audit proved
   * every site passes ctx+0x6a7f70 and the callee already inlines the
   * resulting +0x6a7f74 gate peek. */
  SpawnSuperFlameEffect(1,0,uVar3,uVar2,0x2073,s_ssflame8_00554dd0);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = HitTestLocalMobile(g_clientContext,uVar4,uVar3,uVar2);
    if ((((iVar5 != 0) && (cVar1 = PeekPacketChecksumBool(), cVar1 != '\0')) &&
        (cVar1 = PeekPacketChecksumBool(), cVar1 != '\x01')) &&
       (cVar1 = PeekPacketChecksumBool(), (*(int *)(iVar5 + 0xae2c) == 1) != (bool)cVar1)) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iVar5 + 0x90c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_0048398a;
            pcVar6 = pcVar6 + *(int *)(&g_nCameraBoundX + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&g_nCameraBoundY + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_0048398a:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x35ec));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      ApplyBlastDamage(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x17e4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar9 = 1;
      uVar8 = 1;
      uVar4 = 0xff;
      uVar3 = 0;
      PeekPacketChecksumBool((byte *)(param_1 + 0xf3c));
      SpawnBlastEffect(local_10,iVar5,*(undefined1 *)(param_1 + 0x3c),7,0,uVar3,uVar2,uVar4,uVar8,uVar9);
      cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
      if (cVar1 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
  } while (local_18 < 8);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
     * index this loop is walking - plus the resulting two-position shift.
     * HitTestJewel is the layer-100006 twin of HitTestLocalMobile:
     * it looks up the entity at slot EDX and guard-computes
     * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
     * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
     * before it is ever read - orig 0x425caa mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
    iVar5 = HitTestJewel(0,local_18,uVar4,uVar3,uVar2);
    if (iVar5 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iVar5 + 0x25c));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_00483b89;
            pcVar6 = pcVar6 + *(int *)(&g_nCameraBoundX + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&g_nCameraBoundY + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_00483b89:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x35ec));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      ApplyBlastDamage(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x17e4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)(*(char *)(param_1 + 0xf3c) + *(char *)(param_1 + 0xf3d) + -0x34) !=
          *(char *)(param_1 + 0xf3e)) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      SpawnBlastEffect(local_10,iVar5,*(undefined1 *)(param_1 + 0x3c),7,0,0,uVar2,0xff,1,1);
      iVar5 = g_clientContext;
      pbVar7 = &DAT_006a7f74 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar7 + (&DAT_006a7f75)[iVar5] + -0x34) == (&DAT_006a7f76)[iVar5]) {
        local_19 = '\x01' - (((byte)(&DAT_006a7f75)[iVar5] >> (*pbVar7 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_19 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_19 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
  } while (local_18 < 8);
  local_18 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* RECOVERED (2026-08-19): the dropped EDX argument - the 0..7 SLOT
     * index this loop is walking - plus the resulting two-position shift.
     * HitTestMine is the layer-100003 twin of HitTestLocalMobile:
     * it looks up the entity at slot EDX and guard-computes
     * (entityX - x, entityY - y) from its +0x25c/+0x480 cells.  param_1 is
     * a PHANTOM (Ghidra marks the function __fastcall, but ECX is written
     * before it is ever read - orig 0x425e7a mov ecx,[eax+0x6a7f8c]), so it is passed 0. */
    iVar5 = HitTestMine(0,local_18,uVar4,uVar3,uVar2);
    if (iVar5 != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState((void *)(iVar5 + 0x40));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((-1 < iVar5) && (iVar5 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
        pcVar6 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + iVar5);
        local_10 = 0;
        if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
          do {
            if (*pcVar6 != '\0') goto LAB_00483e2e;
            pcVar6 = pcVar6 + *(int *)(&g_nCameraBoundX + g_clientContext);
            local_10 = local_10 + 1;
          } while (local_10 < *(int *)(&g_nCameraBoundY + g_clientContext));
        }
      }
      local_10 = 10000;
LAB_00483e2e:
      FUN_00436070(&DAT_006a7f70 + g_clientContext,iVar5,local_10);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x35ec));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x3198));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      ApplyBlastDamage(iVar5,local_10,0,uVar4,uVar3,uVar2,*(undefined1 *)(param_1 + 0x3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x17e4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((char)(*(char *)(param_1 + 0xf3c) + *(char *)(param_1 + 0xf3d) + -0x34) !=
          *(char *)(param_1 + 0xf3e)) {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      SpawnBlastEffect(local_10,iVar5,*(undefined1 *)(param_1 + 0x3c),7,0,0,uVar2,0xff,1,1);
      iVar5 = g_clientContext;
      pbVar7 = &DAT_006a7f74 + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if ((byte)(*pbVar7 + (&DAT_006a7f75)[iVar5] + -0x34) == (&DAT_006a7f76)[iVar5]) {
        local_19 = '\x01' - (((byte)(&DAT_006a7f75)[iVar5] >> (*pbVar7 & 7) & 1) != 1);
      }
      else {
        g_valueGuardTamperFlag = 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_19 = '\0';
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (local_19 == '\0') {
        AcquireSoundChannel(0);
      }
    }
    local_18 = local_18 + 1;
    if (0x3f < local_18) {
      return;
    }
  } while( true );
}

