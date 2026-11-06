/* SpawnCrashParticleAdditive - 0x00436dc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - three plain globals, cell for cell the twin of SpawnCrashParticleAlphaBlend.
 *
 * Evidence. The constructor it calls, FUN_0048dcc0 (0x50-byte object),
 * stamps class id 0x2e633 and installs vtable 0x556308. The class-id switch
 * in FUN_00450c20, the draw pass that binds the "CrashTexture" texture once
 * and then walks the layers, puts 0x2e633 in the additive group (blend mode
 * 2, SRCALPHA / ONE) and the sibling spawner SpawnCrashParticleAlphaBlend's
 * class 0x2e631 in the ordinary-alpha group (mode 1). The two spawners are
 * otherwise the same shape, so the blend mode is what separates them, and the
 * names say so. SpawnCrashEffect (class 0x2e644) is the detonation-time
 * additive sibling.
 *
 * Callers. All 18 binary sites load EAX with ctx + 0x6a7f70 and push (x, y,
 * value); in SimulateProjectileFrame the value is the peek of a guard cell
 * and the call comes right before SpawnCrashParticleAlphaBlend. The port
 * reads the flag at ctx + 0x6a7f74 directly instead of taking EAX. The spawn
 * is gated on rand() % 400 (half the sibling's rate for the same inputs)
 * against DAT_005f2f54, the 1..3 value HandleMouseInput stores from a
 * three-position option, times the third argument. The object is placed at
 * (x, y) plus the same random offset and bias as the sibling. LIKELY: the
 * role of the particle is not established beyond its blend mode and texture.
 *
 * Known port defect, not changed here: the call to FUN_0048dcc0 discards the
 * object, so iVar2 is uninitialised in the port.
 */
#include "ghidra_types.h"


void SpawnCrashParticleAdditive(int param_1,int param_2,int param_3)

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
    if ((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3 - iVar2 % 400 != 0 &&
        iVar2 % 400 <= (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_3)) {
      pvVar3 = operator_new(0x50);
      if (pvVar3 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        /* FUN_0048dcc0 is void-returning (see its own definition) -
         * this call site's return-value use is a Ghidra per-call-site
         * decompilation inconsistency, same class as entry/WinMain.c's
         * FUN_004058c0 fix. iVar2 is left uninitialized here as a
         * result. */
        FUN_0048dcc0();
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
      RegisterActiveObject(0, 0, (undefined4 *)0);
    }
  }
  return;
}

