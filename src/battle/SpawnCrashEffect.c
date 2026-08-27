/* SpawnCrashEffect - 0x00436ac0 in the original binary.
 *
 * Spawns the impact "crash" effect at a detonation point.
 *
 * NAMED 2026-08-26, from the effect class's own draw method rather than from
 * this body.  The constructor it calls (0x464200) stamps class id 0x2e644 and
 * installs vtable 0x555ccc, and that vtable's slot 3 (0x464280) draws the
 * object by looking the texture up BY NAME: `mov eax,0xeb1bd8` (g_textureCache)
 * / `push 0x555b80` -- and 0x555b80 is s_CrashTexture_00555b80, "CrashTexture",
 * the string PreloadBattleTextures already preloads by that name.  Slot 2
 * (0x464250) is the per-frame decay: it advances +0x40/+0x48, shrinks +0x4c by
 * a quarter each tick and raises the done-flag at +0x14 when it drops below 4.
 *
 * All 24 call sites are detonation paths -- 17 are named Detonate* / Explode*
 * bodies and the other 7 are still-unnamed functions that each call
 * ApplyBlastDamage or SpawnBlastEffect alongside this one.
 *
 * param_1/param_2 are the impact point (stored to +0x38/+0x3c); regEbx is the
 * projectile's m_subtype (+0x3f90, declared in src/cxx/Projectile.h), stored
 * to +0x18 and used to pick the frame set -- 0xff means "no subtype" and
 * suppresses the effect entirely.  +0x44 gets rand() %% peek(DAT_00e9bed8), a
 * random variant.  The whole thing is gated on the effects-enabled guard bool
 * at g_clientContext + 0x6a7f74, the same flag the rest of the effect family
 * checks.
 *
 * FUN_00436b50 is its near-twin: same class, same guard, same random variant,
 * but no subtype -- called only from DetonateShot2_Bullet13 and
 * DetonateSuperShot_Bullet13.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e9bed8), from tools/guard_cell_resolve.py.
 *
 * EBX RECOVERED (2026-08-26) at all 24 sites: the projectile's subtype field
 * at +0x3f90, which src/cxx/Projectile.h already declares as
 * `u32 m_subtype` ("shot subtype / blast frame set").  Every site is the same
 * instruction shape -- `mov ebx,[<projectile> + 0x3f90]` -- off either the
 * caller's own `this` or a frame slot holding the projectile it is detonating.
 */
#include "ghidra_types.h"


void SpawnCrashEffect(undefined4 param_1,undefined4 param_2,int regEbx)
{
  char cVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if ((cVar1 == '\0') && (regEbx != 0xff)) {
    pvVar2 = operator_new(0x50);
    if (pvVar2 == (void *)0x0) {
      iVar3 = 0;
    }
    else {
      FUN_00464200();
    }
    *(undefined4 *)(iVar3 + 0x38) = param_1;
    *(undefined4 *)(iVar3 + 0x3c) = param_2;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = _rand();
    *(int *)(iVar3 + 0x18) = regEbx;
    *(int *)(iVar3 + 0x44) = iVar5 % iVar4;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

