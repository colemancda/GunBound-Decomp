/* SpawnCrashParticleAlphaBlend_2e632 - 0x00436cd0 in the original binary.
 *
 * Spawns the class-0x2e632 CrashTexture ordinary-alpha particle
 * (constructor InitCrashParticleAlphaBlend_2e632, vtable 0x00556250),
 * the third alpha class beside SpawnCrashParticleAlphaBlend (0x2e631).
 * Evidence from outside the body: the constructor stamps key 0x2e632 and
 * FUN_00450c20 draws that key in the blend-mode-1 group with 0x2e631;
 * the spawn is the same shape as SpawnCrashParticleAlphaBlend, a rand()
 * % 200 roll against the effects option (DAT_005f2f54) scaled by the
 * third argument, a position jittered by up to 20 less the global bias
 * at DAT_00e9ba40, and a random variant peeked from DAT_00e9bed8. Its
 * sole caller is SimulateMobileFrame (0x00462786), which passes ECX and
 * two stack values (ret 8) and loads EAX with ctx + 0x6a7f70 as every
 * spawner of this family does; the port reads the flag at +0x74
 * directly. The class key is unique in the image, so it is the suffix,
 * as for SpawnCrashParticleAdditive_2e634. LIKELY: the particle's role
 * beyond class, blend mode and texture is not established.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: &DAT_00e9ba40 then &DAT_00e9bed8 (emitter family).
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, no-prototype sweep). This is a genuine
 * __thiscall: `ret 8` at orig 0x436db1 confirms 2 STACK arguments
 * (param_2/param_3), plus ECX (param_1, the `this`) = 3 total - the
 * declaration's shape was already correct. The bug was purely at both
 * call sites, which had NO prototype in include/functions.h (the header's
 * generator skips this split-line `void __thiscall` definition, per
 * fastcall-decls-missing-from-functions-h), so a 2-argument call compiled
 * silently instead of erroring: the ECX/`this` argument was dropped, and
 * the two stack values that WERE passed landed one slot too far right.
 * Confirmed at the sole call site's original instructions (0x462763-
 * 0x462786 in SimulateMobileFrame, orig 0x461ca0): `push 0x28` happens
 * BEFORE the two PeekChecksumStateUnderLock calls and survives both
 * (untouched, since each Peek callee is `ret 4` and only consumes its own
 * single pushed arg) - it becomes stack-arg 2 (param_3). The FIRST Peek's
 * result (on `param_1 + 0x2cc`) is kept in ESI across the second Peek
 * call and copied into ECX right before this call (`mov ecx,esi` at
 * 0x462784) - i.e. it is param_1 (`this`), not a discarded value as the
 * raw port had it. The SECOND Peek's result (on `param_1 + 0x243`,
 * already named uVar9 in the port) is pushed last and lands as stack-arg
 * 1 (param_2). Both call sites (SimulateMobileFrame.c and its src/cxx/
 * Mobile.cpp twin) now capture the first Peek's result into a new local
 * and pass all three arguments in this order: SpawnCrashParticleAlphaBlend_2e632(<first-Peek
 * result>, <second-Peek result>, 0x28).
 */
#include "ghidra_types.h"


void __thiscall SpawnCrashParticleAlphaBlend_2e632(int param_1,int param_2,int param_3)

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
        iVar2 = (int)InitCrashParticleAlphaBlend_2e632((undefined4 *)pvVar3);
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      *(int *)(iVar2 + 0x38) = (iVar5 % 0x15 - iVar4) + param_2;
      iVar4 = _rand();
      *(int *)(iVar2 + 0x3c) = param_1 - iVar4 % 0x15;
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

