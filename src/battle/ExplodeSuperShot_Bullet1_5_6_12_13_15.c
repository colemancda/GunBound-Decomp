/* ExplodeSuperShot_Bullet1_5_6_12_13_15 - 0x0048de60 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_0048de60): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 0's super shot (texture bullet1p; vtable 0x555ac4, ctor FUN_0044d970
 * reached only through SpawnSuperShot's case 0); mobile type 4's super
 * shot (texture bullet5p; vtable 0x55631c, ctor FUN_0048de40 reached only
 * through SpawnSuperShot's case 4); mobile type 5's super shot (texture
 * bullet6p; vtable 0x555bf0, ctor FUN_00452c80 reached only through
 * SpawnSuperShot's case 5); mobile type 11's super shot (texture
 * bullet12p; vtable 0x55661c, ctor FUN_004ae370 reached only through
 * SpawnSuperShot's case 11); mobile type 12's super shot (texture
 * bullet13p; vtable 0x55620c, ctor FUN_004856d0 reached only through
 * SpawnSuperShot's case 12); mobile type 14's super shot (texture
 * bullet15p; vtable 0x556098, ctor FUN_0047de30 reached only through
 * SpawnSuperShot's case 14). Type/role CONFIRMED via vtable geometry
 * (tools/projectile_class_map.py); the mobile NAME is not confirmable (no
 * mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 19 argless PeekPacketChecksumState() calls (peek status
 * "clean", 19 C : 19 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x48de60-0x48e17d; no gotos, straight-line, so the sites order-zip.
 *
 * Same detonation-twin tail as ExplodeSuperShot_Bullet3, offset for offset: the
 * ten-cell crater block (0x6ac/0x488/0x2f74/0x2d50/0x2b2c/0x2908/0x26e4/
 * 0x24c0/0x1178/0xf54), then three 0x1178+0xf54 pairs, then 0x15c0 and a
 * fourth pair.  The object is spilled in the prologue at 0x48de74 (one
 * push deep, so the `[esp+0x18]` text names frame[0x14]), and the two
 * hot cells are cached in frame[0x28] = param_1+0x1178 and frame[0x10] =
 * param_1+0xf54 from 0x48dff5/0x48e016 on.  Both slots hold Peek RESULTS
 * earlier in the function (0x48deab, 0x48df3c) - only the later stores
 * make them cells, which is why each read was matched to its own most
 * recent writer rather than to the slot's first use.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet1_5_6_12_13_15(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x6ac));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState((void *)(param_1 + 0x2f74));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState((void *)(param_1 + 0x2d50));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar7 = PeekPacketChecksumState((void *)(param_1 + 0x2b2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar8 = PeekPacketChecksumState((void *)(param_1 + 0x2908));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar9 = PeekPacketChecksumState((void *)(param_1 + 0x26e4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar10 = PeekPacketChecksumState((void *)(param_1 + 0x24c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  ApplyCraterExcavation(uVar10,uVar9,uVar8,uVar7,uVar6,uVar5,uVar4,uVar3);
  RebuildTerrainColumnCache(&DAT_006a7708 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00450eb0(uVar4,uVar3,param_1,1,0,0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00436ac0(uVar4,uVar3);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004372f0(*(undefined4 *)(param_1 + 8),uVar4,uVar3,*(undefined4 *)(param_1 + 0x3894),
               param_1 + 0x3898);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x15c0));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_00437150(uVar5,uVar4,0x3c,uVar3);
  iVar1 = g_clientContext;
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 != '\x01') {
    iVar11 = *(int *)(&DAT_006a7750 + iVar1);
    if (iVar11 < 0x10) {
      iVar11 = 0xf;
    }
    *(int *)(&DAT_006a7750 + iVar1) = iVar11;
    iVar11 = *(int *)(&DAT_006a7754 + iVar1);
    if (iVar11 < 0xb) {
      iVar11 = 10;
    }
    *(int *)(&DAT_006a7754 + iVar1) = iVar11;
  }
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
  }
  return;
}

