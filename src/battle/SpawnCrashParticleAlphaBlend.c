/* SpawnCrashParticleAlphaBlend - 0x00436bd0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - three plain globals (&DAT_00e9ba40 x2, &DAT_00e9bed8).
 *
 * Evidence. The constructor it calls, InitCrashParticleAlphaBlend (0x50-byte object),
 * stamps class id 0x2e631 and installs vtable 0x556544. The class-id switch
 * in FUN_00450c20, the draw pass that binds the "CrashTexture" texture once
 * and then walks the layers, puts 0x2e631 in the group drawn with blend
 * mode 1 (SRCALPHA / INVSRCALPHA, ordinary alpha) and 0x2e633 in the
 * additive group (mode 2, SRCALPHA / ONE). The other spawner of the same
 * shape, SpawnCrashParticleAdditive, builds class 0x2e633, so the two particle spawners
 * differ by blend mode, and the names say so. SpawnCrashEffect (class
 * 0x2e644, also additive) is the detonation-time sibling and is named from
 * the same texture.
 *
 * Callers. All 18 binary sites (SimulateProjectileFrame and the Simulate*
 * bullet bodies, two each) load EAX with ctx + 0x6a7f70 and push (x, y,
 * value); the port reads the same flag at ctx + 0x6a7f74 directly instead of
 * taking EAX, and the earlier audit of that helper family found the register
 * uniform. The spawn is gated on a roll: rand() % 200 must be below
 * DAT_005f2f54 times the third argument, where DAT_005f2f54 is the 1..3
 * value HandleMouseInput stores from a three-position option and
 * CarveTerrainCrater and SpawnCraterDebris also scale by. The particle is
 * placed at (x, y) plus a random offset of up to 20 less a global bias
 * (+0x38, +0x3c), given a random variant (+0x44), and registered. LIKELY:
 * "particle" is the class's role as a short-lived textured sprite; the exact
 * visual (smoke, dust) is not established, and a trail role is not claimed.
 */
#include "ghidra_types.h"


void SpawnCrashParticleAlphaBlend(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    iVar2 = _rand();
    if ((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3 - iVar2 % 200 != 0 &&
        iVar2 % 200 <= (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3)) {
      pvVar3 = operator_new(0x50);
      if (pvVar3 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (int)InitCrashParticleAlphaBlend((undefined4 *)pvVar3);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x38) = (iVar5 % 0x15 - iVar4) + param_1;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x3c) = (iVar5 % 0x15 - iVar4) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x44) = iVar5 % iVar4;
      /* EDX = ctx+0x6a7f88 (the battle entity registry), EDI = the object just
       * built; the port had passed (0,0,NULL). */
RegisterActiveObject(0,(int)g_clientContext + 0x6a7f88,(undefined4 *)iVar2);
    }
  }
  return;
}

