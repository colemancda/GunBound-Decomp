/* SpawnCrashParticleBurst - 0x00437150 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY, name is a role guess). Callers: all 21 binary sites
 * (tools/callsite_regs.py; tools/count_call_args.py counts 22 source sites
 * including the cxx extern) are detonation or explosion bodies (Detonate*,
 * Explode*, plus FUN_004513b0, FUN_0046a4d0, FUN_0046b680, FUN_0049d270).
 * Each loads EAX with ctx + 0x6a7f70 and pushes (x, y, 0x3c, n), so arg3 is
 * always the 0x3c scatter span and arg4 a per-site count factor. EAX is the
 * effects-guard block the same helper family takes (see
 * SpawnCrashParticleAdditive); the port reads its +4 flag at ctx + 0x6a7f74
 * directly, so no call site needs an extra argument. ret 0x10 matches the
 * four declared parameters.
 * Unlike the probabilistic CrashParticle spawners there is no rand() gate:
 * it spawns DAT_005f2f54 (the 1..3 effects option) times arg4 particles in
 * a loop, each scattered within +-span/2 of (x, y). The inline object is
 * 0x58 bytes with class id 0x2e633 at +4, the CrashTexture additive class
 * SpawnCrashParticleAdditive documents, but with vtable 0x555ce0 (that one
 * installs 0x556308 through InitCrashParticleAdditive), so it is a distinct class
 * sharing the id. Burst, because it emits a counted batch at once.
 * The particle role is
 * not established beyond class id and texture.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - three plain globals (&DAT_00e9bed8, &DAT_00e9ba40 x2).
 */
#include "ghidra_types.h"


void SpawnCrashParticleBurst(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_8;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if ((cVar1 == '\0') &&
     (local_8 = 0, 0 < (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_4))) {
    do {
      puVar2 = operator_new(0x58);
      puVar5 = (undefined4 *)0x0;
      if (puVar2 != (undefined4 *)0x0) {
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2[7] = 0;
        puVar2[10] = 0;
        puVar2[0xb] = 0;
        puVar2[0x10] = 0;
        puVar2[1] = 0x2e633;
        puVar2[2] = 0xffffffff;
        *(undefined1 *)(puVar2 + 5) = 0;
        *(undefined1 *)((int)puVar2 + 0x15) = 0;
        puVar2[6] = 0xffffffff;
        *(undefined1 *)(puVar2 + 8) = 0;
        puVar2[9] = 0xffffffff;
        *puVar2 = &PTR_FUN_00555ce0;
        puVar2[0x12] = 0x10;
        puVar2[0x13] = 0x80;
        puVar5 = puVar2;
      }
      iVar3 = _rand();
      puVar5[0xe] = (iVar3 % param_3 - param_3 / 2) + param_1;
      iVar3 = _rand();
      puVar5[0xf] = (iVar3 % param_3 - param_3 / 2) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      puVar5[0x11] = iVar4 % iVar3;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      puVar5[0x14] = iVar4 % 0x15 - iVar3;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      puVar5[0x15] = iVar4 % 0x15 - iVar3;
      RegisterActiveObject(0, 0, (undefined4 *)0);
      local_8 = local_8 + 1;
    } while (local_8 < (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_4));
  }
  return;
}

