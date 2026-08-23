/* SpawnFlameEffect - 0x004372f0 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_004372f0): allocates a 0x54 effect object, textures it via FindPreloadedTextureByName(param_6), sets animation "flame" (s_flame_00553d2c) and registers it; called from ~27 detonation sites; gated by the global effects flag ctx+0x6a7f74.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00e9bed8), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


void __thiscall
SpawnFlameEffect(char param_1,undefined4 param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x54);
    if (pvVar2 == (void *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00471af0();
    }
    piVar3[0xe] = param_3;
    piVar3[0xf] = param_4;
    if (param_1 == '\0') {
      iVar5 = 0;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9bed8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar5 = _rand();
      iVar5 = iVar5 % iVar4;
    }
    *(char *)(piVar3 + 0x14) = param_1;
    piVar3[0x11] = iVar5;
    piVar3[6] = param_5;
    iVar5 = FindPreloadedTextureByName(param_6);
    piVar3[7] = iVar5;
    (**(code **)(*piVar3 + 4))(s_flame_00553d2c);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

