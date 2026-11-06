/* SpawnCrashParticleAdditive_2e634 - 0x00436ec0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 4 argless PeekPacketChecksumState() calls (4 C : 4 orig,
 * goto-free zip) - all plain globals.
 *
 * Evidence (LIKELY). The constructor it calls, FUN_00481e30 (0x50-byte
 * object, orig 0x436f17-0x436f23), stamps class id 0x2e634 (190004) at +4
 * and installs vtable 0x556180. The class-id switch in FUN_00450c20, the
 * draw pass that binds the "CrashTexture" texture once and then walks the
 * layers, lists 0x2e634 with 0x2e633 and 0x2e644 in the additive group
 * (blend mode 2, SRCALPHA / ONE), so this is a third CrashTexture additive
 * particle next to SpawnCrashParticleAdditive (class 0x2e633, ctor
 * FUN_0048dcc0). It is a distinct class and a distinct spawner shape, so
 * the class id is the suffix: this one takes only (x, y) (ret 8), and its
 * spawn roll is rand() % peek(0x796aa0) against DAT_005f2f54 with no
 * third-argument scale, unlike the (x, y, value) siblings.
 *
 * Callers. All 18 binary sites (SimulateProjectileFrame and the Simulate*
 * bullet bodies, two each) load EAX with ctx + 0x6a7f70 (tools/
 * callsite_regs.py: eax uniform, "add eax,0x6a7f70") and push (x, y); the
 * +4 add before PeekPacketChecksumBool at 0x436ec0 makes that the flag at
 * ctx + 0x6a7f74, which the port reads directly. The particle is placed at
 * (x, y) plus a random offset of up to 20 less a global bias (+0x38,
 * +0x3c) and registered. The particle role is not established beyond its
 * class, blend mode and texture.
 */
#include "ghidra_types.h"


void SpawnCrashParticleAdditive_2e634(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = _rand();
    if (iVar3 % iVar2 < (int)(uint)(byte)(&DAT_005f2f54)[g_clientContext]) {
      pvVar4 = operator_new(0x50);
      if (pvVar4 == (void *)0x0) {
        iVar2 = 0;
      }
      else {
        FUN_00481e30();
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x38) = (iVar5 % 0x15 - iVar3) + param_1;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x3c) = (iVar5 % 0x15 - iVar3) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x44) = iVar5 % iVar3;
      RegisterActiveObject(0, 0, (undefined4 *)0);
    }
  }
  return;
}

