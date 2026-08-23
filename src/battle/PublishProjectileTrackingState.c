/* PublishProjectileTrackingState - 0x00458690 in the original binary.
 *
 * CProjectile's vtable slot 3 (see src/cxx/Projectile.h), referenced by 31
 * vtables - the second highest-leverage uncarved slot after
 * IsProjectileInBounds.  NEW CARVE (2026-08-19): Ghidra never carved this
 * range as a function - it is reachable only through the projectile vtables -
 * so this port is hand-derived instruction-by-instruction from the capstone
 * disassembly of 0x458690..0x45884f (no decompile existed).
 *
 * What it does: publishes this projectile's guarded state into the per-slot
 * tracking tables in the client context, then resolves two sprite/frame rows.
 * Everything is keyed by the projectile's slot id at this+0x8 (m_ctorArg1),
 * and it no-ops entirely when the primary table pointer is null.
 *
 * THE PER-SLOT RECORD.  The original writes the first field as
 * `ctx + (id + 0x1a35) * 5 * 4`, which is just ctx + 0x20c24 + id * 20 - so
 * the four scattered constants below are one 5-dword record with a 20-byte
 * stride, not four unrelated arrays:
 *     +0x20c24   X          Peek(this + 0xf54)
 *     +0x20c28   Y          Peek(this + 0x1178)
 *     +0x20c2c   angle      Peek(this + 0x1c2c)  (identified by the FACING
 *                           variant at 0x488880, which tests this same value
 *                           against the 90..270 degree window)
 *     +0x20c30   the table-2 row lookup result, truncated to a byte
 *     +0x20c34   cleared to 0 (twice - once before the lookups, once after).
 *                In the 0x488880 variant this field instead carries a FACING
 *                flag, (angle > 90 && angle < 270); classes whose sprite does
 *                not flip use this version and hardcode the 0.
 * Two separate byte flags are keyed by the same id: ctx+0x20bb4+id (cleared
 * when the +0x3810 GuardedBool reads true) and ctx+0x20ba4+id (set to the
 * INVERSE of CheckGuardedBoolAnd's result).
 *
 * The row address arithmetic is the same group-of-four shape DrawFlameEffect
 * documents: ((id >> 2) * stride + (id & 3) * 2) << 6, over the table pointer
 * and stride pair at ctx+0x20b94/0x20b98 and again at ctx+0x20b9c/0x20ba0.
 *
 * Raw/near-verbatim hand port - not hand-verified against a running client.
 * See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"
#include <windows.h>


void __fastcall PublishProjectileTrackingState(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int ctx;

  ctx = g_clientContext;
  iVar1 = *(int *)(ctx + 0x20b94);          /* orig 0x458699 - table 1 */
  if (iVar1 == 0) {
    return;
  }
  /* orig 0x4586a7-0x4586c5 */
  cVar5 = PeekPacketChecksumBool((byte *)(param_1 + 0x3810));
  if (cVar5 != '\0') {
    *(undefined1 *)(ctx + *(int *)(param_1 + 8) + 0x20bb4) = 0;
  }
  /* orig 0x4586cf-0x4586f5: `test eax,eax / setl al` - the sign of the peek */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x488));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* orig 0x4586fb-0x458726: the flag is the INVERSE of the guard result */
  cVar5 = CheckGuardedBoolAnd(iVar2 < 0);
  *(undefined1 *)(ctx + *(int *)(param_1 + 8) + 0x20ba4) = (cVar5 == '\0');

  /* orig 0x45872f-0x4587c8: the five-dword per-slot record (stride 20) */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c24) = iVar2;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c28) = iVar2;

  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1c2c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c2c) = iVar2;
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c34) = 0;

  /* orig 0x4587cb-0x4587f4: row 1 = table1 + ((id>>2)*stride + (id&3)*2) << 6 */
  iVar3 = *(int *)(ctx + 0x20b98);
  iVar4 = *(int *)(param_1 + 8);
  iVar2 = (((iVar4 >> 2) * iVar3 + (iVar4 & 3) * 2) << 6) + iVar1;
  if (iVar2 == 0) {
    return;
  }
  /* orig 0x4587ec-0x4587f4: EDX = this+0x18, EAX = this+0x30, stack =
   * (rowAddr, stride); param_1 is FUN_00455b60's phantom ECX. */
  FUN_00455b60(0,*(uint *)(param_1 + 0x18),iVar2,iVar3,*(uint *)(param_1 + 0x30));

  /* orig 0x4587f9-0x458843: table 2, same shape; result truncated to a byte */
  iVar1 = *(int *)(ctx + 0x20b9c);
  if (iVar1 == 0) {
    return;
  }
  iVar3 = *(int *)(ctx + 0x20ba0);
  iVar4 = *(int *)(param_1 + 8);
  iVar2 = (((iVar4 >> 2) * iVar3 + (iVar4 & 3) * 2) << 6) + iVar1;
  /* orig 0x458820-0x458828: same, but EDX = this+0x38 (m_lifetime). */
  iVar2 = FUN_00455b60(0,*(uint *)(param_1 + 0x38),iVar2,iVar3,*(uint *)(param_1 + 0x30));
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c30) = iVar2 & 0xff;
  *(int *)(ctx + *(int *)(param_1 + 8) * 0x14 + 0x20c34) = 0;
  return;
}
