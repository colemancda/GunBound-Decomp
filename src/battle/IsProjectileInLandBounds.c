/* IsProjectileInLandBounds - 0x00491a40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (LIKELY). Vtable slot 7 of twelve projectile vtables (0x555b34,
 * 0x555bec, 0x555d30, 0x555fb8, 0x556074, 0x5560b4, 0x55617c, 0x556228,
 * 0x55637c, 0x5563c4, 0x5564b8, 0x5565c8; tools/find_vtable_refs.py), the
 * same slot as IsProjectileInBounds (0x458850, forty vtables), which is the
 * bounds test on the guarded X cell (this+0xf54) and Y cell (this+0x1178).
 * This is the sibling that tests those same two cells against the stage
 * land size instead of the guarded world-bounds cells: 0 <= x < the value at
 * ctx+0x6a7720, y < the value at ctx+0x6a7724, and y not below -1000
 * (PacketChecksumLessThan(y, 0xfffffc18) false). ctx+0x6a7720/0x6a7724 are
 * stage object +0x18/+0x1c (stage object at ctx+0x6a7708), which
 * LoadStageLandFile fills with the two values read from the .lnd file ahead
 * of the w*h body; the tree's globals.h calls them g_nCameraBoundX/Y. They
 * are the land width and height, hence Land rather than Camera in the name.
 * Returns AL (mov al,1 / xor al,al), this in ECX, no stack arguments; the
 * declaration in functions.h now carries the real (int param_1) list.
 * No direct callers; reached only through the vtables.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at all 3 argless PeekPacketChecksumState() calls (3 C : 3 orig,
 * goto-free zip) - all off the live-in ECX object: +0xf54 twice, then +0x1178.
 */
#include "ghidra_types.h"


int __fastcall IsProjectileInLandBounds(int param_1)

{
  char extraout_AL;
  int iVar1;
  undefined4 extraout_EAX;
  uint3 uVar3;
  int iVar2;
  undefined4 extraout_EAX_00;
  uint3 extraout_var;
  uint3 extraout_var_00;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  uVar3 = (uint3)((uint)extraout_EAX >> 8);
  if (-1 < iVar1) {
    iVar1 = *(int *)(&g_nCameraBoundX + g_clientContext);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = (uint3)((uint)extraout_EAX_00 >> 8);
    if (iVar2 < iVar1) {
      iVar1 = *(int *)(&g_nCameraBoundY + g_clientContext);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = extraout_var;
      if (iVar2 < iVar1) {
        PacketChecksumLessThan(param_1 + 0x1178,0xfffffc18);
        uVar3 = extraout_var_00;
        if (extraout_AL == '\0') {
          return CONCAT31(extraout_var_00,1);
        }
      }
    }
  }
  return (uint)uVar3 << 8;
}

