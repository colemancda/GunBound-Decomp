/* ExplodeSuperShot_Bullet2 - 0x0048d8e0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_0048d8e0): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 1's super shot (texture bullet2p; vtable 0x5562c8, ctor InitSuperShot_Bullet2
 * reached only through SpawnSuperShot's case 1). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 6 argless PeekPacketChecksumState() calls (6 C : 6 orig,
 * goto-free zip), from tools/guard_cell_resolve.py over
 * 0x48d8e0-0x48db90.  Five cells hang off the live-in ECX object
 * (param_1): the +0x1178/+0xf54 pair feeding SpawnSuperFlameEffect (the
 * "ssflame2" registration), then +0x33c8/+0x1178/+0xf54 feeding the
 * HitTestLocalMobile lookup - the same three-cell argument pattern
 * ExplodeSuperShot_Bullet11 uses for the same callee.  The sixth is
 * g_clientContext+0x45354 (the battle-mode cell).
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet2(int param_1)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar4Saved;
  undefined4 uVar5;
  int *piVar6;
  int iVar7;
  int local_240;
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053df6b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* RECOVERED (2026-08-19): the two dropped __fastcall register
     * arguments (orig 0x48d97a mov cl,1 / 0x48d97c xor edx,edx).  param_1 is the randomise flag,
     * param_2 the sub-effect index (the callee caps it at < 4).  The third
     * register argument, EAX, needs nothing here: the 2026-08-17 audit proved
     * every site passes ctx+0x6a7f70 and the callee already inlines the
     * resulting +0x6a7f74 gate peek. */
    SpawnSuperFlameEffect(1,0,uVar4,uVar3,0x206d,s_ssflame2_00555320);
    local_240 = 0;
    do {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      /* SAVED (2026-09-21): this uVar4 (the projectile's own +0x1178
       * cell) gets reassigned to a completely different cell at line
       * ~93 below before FUN_00436860's call, but orig 0x48d9df/EDI-
       * equivalent register tracking shows the ORIGINAL value here
       * survives unclobbered (no other write to its stack slot) all the
       * way to the FUN_00436860 call - captured here before the
       * HitTestLocalMobile args (uVar3/uVar4/uVar5) reuse the names. */
      uVar4Saved = uVar4;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar5 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      piVar6 = (int *)HitTestLocalMobile(g_clientContext,uVar5,uVar4,uVar3);
      if (piVar6 != (int *)0x0) {
        cVar2 = PeekPacketChecksumBool();
        if (cVar2 != '\0') {
          cVar2 = PeekPacketChecksumBool();
          if ((cVar2 != '\x01') && (piVar6[9] != 0xe)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            iVar7 = PeekPacketChecksumState((void *)(g_clientContext + 0x45354));
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            if (iVar7 != 3) {
              cVar2 = PacketChecksumNotEquals(piVar6 + 0x1bf5,0);
              if (cVar2 != '\0') {
                iVar7 = piVar6[0x2c2a];
                piVar6[0x2c2a] = iVar7 + 1;
                uVar3 = EncodeChecksumDeltaSub(piVar6 + 0x2cc,local_230,iVar7 * 0xf);
                local_4 = 0;
                PeekChecksumStateUnderLock(piVar6 + 0x1bf5);
                uVar3 = PeekChecksumStateUnderLock(uVar3);
                uVar4 = PeekChecksumStateUnderLock(piVar6 + 0x243);
                /* DROPPED-ARGUMENT FIX (2026-09-21): FUN_00436860 is
                 * __fastcall with 2 register args (ECX,EDX) ahead of
                 * these 2 stack args - this call only ever passed the
                 * stack pair.  Orig 0x48dada/0x48dadd: `mov ecx,[esi+8]`
                 * (piVar6[2]); `mov edx,[esp+0x20]` = uVar4Saved
                 * unmodified (see the SAVED comment above) - no `neg`
                 * on this path, unlike the sibling sites in
                 * FUN_00478cb0/FUN_0045db20/FUN_0045ea40/FUN_0048f300. */
                FUN_00436860(piVar6[2],uVar4Saved,uVar4,uVar3);
                local_4 = 0xffffffff;
                ScrubChecksumGuard();
                if (*(byte *)(param_1 + 0x3c) < 8) {
                  if (*(char *)(*(byte *)(param_1 + 0x3c) + 0x4590c + g_clientContext) ==
                      *(char *)((piVar6[2] & 7U) + 0x4590c + g_clientContext)) {
                    piVar1 = (int *)(g_clientContext + 0x5b83c + (uint)*(byte *)(param_1 + 0x3c) * 4);
                    iVar7 = PeekChecksumStateUnderLock(piVar6 + 0x1bf5);
                    *piVar1 = *piVar1 + iVar7;
                    *(undefined1 *)(piVar6 + 0x2c2d) = 1;
                  }
                  else {
                    piVar1 = (int *)(g_clientContext + 0x5b81c + (uint)*(byte *)(param_1 + 0x3c) * 4);
                    iVar7 = PeekChecksumStateUnderLock(piVar6 + 0x1bf5);
                    *piVar1 = *piVar1 + iVar7;
                  }
                }
              }
            }
            EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            /* FIXED (2026-07-16): dropped `self` arg - angr-confirmed at
             * 0x48db78: self is esi+0x6fd4 (0x1bf5 ints) - esi is
             * piVar6, the same cell already used at piVar6+0x1bf5
             * elsewhere in this function (e.g. line 60/66/76/82). */
            EncodeOutgoingPacketField(piVar6 + 0x1bf5, 0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
            piVar6[0x30ab] = 4;
            (**(code **)(*piVar6 + 4))(s_shield_005562ec);
          }
        }
      }
      local_240 = local_240 + 1;
    } while (local_240 < 8);
    FUN_0048de60();
  }
  return;
}

