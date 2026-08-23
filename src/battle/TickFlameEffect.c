/* TickFlameEffect - 0x00471c70 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_00471c70): vtable slot 2 (Tick) of BOTH
 * CFlameEffect (vtable 0x555ef0) and CSuperFlameEffect (0x5560bc) - see
 * src/cxx/Effects.h.  Advances the sprite animation, marks the object dead
 * when the animation finishes, steps the anim phase mod the guarded frame
 * divisor.
 *
 * No confirmed real name/purpose beyond the above. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both read &DAT_00e9bed8.
 */
#include "ghidra_types.h"


int __fastcall TickFlameEffect(int param_1)

{
  int iVar1;
  int iVar2;
  
  AdvanceSpriteAnimation(param_1);
  if (*(char *)(param_1 + 0x34) != '\0') {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  if (*(char *)(g_clientContext + 0x45578) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = *(int *)(param_1 + 0x44) + 5;
    *(int *)(param_1 + 0x44) = iVar2 % iVar1;
    return iVar2 / iVar1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = *(int *)(param_1 + 0x44) + 2;
  *(int *)(param_1 + 0x44) = iVar2 % iVar1;
  return iVar2 / iVar1;
}

