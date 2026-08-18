/* ExplodeSuperShot_Bullet3 - 0x0048b420 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_0048b420): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 2's super shot (texture bullet3p; vtable 0x556284, ctor FUN_0048b3f0
 * reached only through SpawnSuperShot's case 2). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 21 argless PeekPacketChecksumState() calls (peek status
 * "clean", 21 C : 21 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x48b420-0x48b7f5; no gotos, straight-line, so the sites order-zip.
 *
 * Cell layout is the already-swept detonation-twin tail, offset for
 * offset: the ten-cell crater block (0x6ac/0x488/0x2f74/0x2d50/0x2b2c/
 * 0x2908/0x26e4/0x24c0/0x1178/0xf54), then three 0x1178+0xf54 pairs,
 * then 0x15c0 + a fourth pair, then a fifth.
 *
 * The object arrives in ECX and is spilled once, in the prologue at
 * 0x48b434, to frame[0x38]; 0x48b5e2 reloads it into EDI before that
 * slot is reused for Peek results at 0x48b634 onward.  The 0x1178 and
 * 0xf54 cells are pre-computed once into frame[0x14] and frame[0x10]
 * (0x48b52c / 0x48b54f) and re-read from there for the rest of the
 * function; neither slot is written again.
 *
 * One cell needed a fix to the resolver first: 0x48b78c reads its slot
 * BETWEEN `call 0x4ee9b0` and that call's `add esp,4`, so the __cdecl
 * callee's argument is still on the stack and the operand text
 * [esp+0x18] names frame[0x14], not frame[0x18].  Read naively it would
 * have picked up a stale Peek RESULT from 0x48b46b and used a value as
 * a pointer.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet3(int param_1)

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
  SpawnFlameEffect(*(undefined4 *)(param_1 + 8),uVar4,uVar3,*(undefined4 *)(param_1 + 0x3894),
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
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
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
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 == '\0') {
    AcquireSoundChannel(0);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SpawnSuperFlameEffect(uVar4,uVar3,0x206e,s_ssflame3_00555248);
  return;
}

