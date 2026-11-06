/* SpawnCrashParticleAdditive_556488 - 0x00436b50 in the original binary.
 *
 * Spawns the CrashTexture additive particle built by
 * InitCrashParticleAdditive_556488 (key 0x2e644, vtable 0x00556488),
 * taking only the (x, y) position (ret 8), gated on the effects flag at
 * ctx + 0x6a7f74 and given a random variant from DAT_00e9bed8. Evidence
 * from outside the body: the constructor's key is in the additive group
 * of FUN_00450c20. Callers DetonateShot2_Bullet13 (0x4a0289) and
 * DetonateSuperShot_Bullet13 (0x487409) both load EAX with ctx +
 * 0x6a7f70 (tools/callsite_regs.py: uniform), which the port reads
 * directly. CORRECTION: SpawnCrashEffect's note calls this its near-twin
 * of the same class; the key 0x2e644 is shared, but SpawnCrashEffect
 * builds InitCrashEffect (vtable 0x00555ccc, +0x48/+0x4c = 0x40/0xc4)
 * while this builds vtable 0x00556488 (0x20/0x100), so they are
 * different classes and the key cannot be the suffix. LIKELY.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e9bed8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void SpawnCrashParticleAdditive_556488(undefined4 param_1,undefined4 param_2)

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
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x50);
    if (pvVar2 == (void *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = (int)InitCrashParticleAdditive_556488((undefined4 *)pvVar2);
    }
    *(undefined4 *)(iVar3 + 0x38) = param_1;
    *(undefined4 *)(iVar3 + 0x3c) = param_2;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = _rand();
    *(int *)(iVar3 + 0x44) = iVar5 % iVar4;
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

