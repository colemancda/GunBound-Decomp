/* InvokeWidget - 0x00406300 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NEWLY DISCOVERED, NOT YET FIXED (2026-07-13): `in_EAX` and
 * `unaff_ESI` are dropped-register arguments; this is a 2-real-argument
 * function, not the current 3-`param` `__fastcall` shape. Confirmed via
 * objdump at 19 call sites (`grep -rn "InvokeWidget" src/` for the
 * full list) that EVERY caller does `xor edx,edx` (param_2/EDX is
 * always a literal 0) and pushes a bool on the stack (param_3, the
 * "enabled" flag) - those two are already modeled correctly. But EAX
 * and ESI are BOTH also live incoming values, not garbage: at
 * State02_ServerSelect_ProcessPacket's call site (0x4e0998) `mov
 * eax,0xe9be90` / `mov esi,0x2`; at State03_GameRoomList_OnCommand's
 * (0x428ac1) `mov eax,0xe9be90` / `mov esi,0xd`. EAX (`DAT_00e9be90`,
 * the flat-ButtonWidget registry root) looks invariant across the
 * sites checked - safe to hardcode. ESI does NOT - it's the target
 * widget's id within that registry (2 for the ServerSelect connect
 * button, 0xd for whatever GameRoomList control this is) and genuinely
 * varies per caller. Fixing this needs each of the 19 call sites
 * individually traced for its real widget id, INCLUDING the 4 sites
 * already "promoted" to C++ (Panel.cpp x3, State02_ServerSelect.cpp,
 * Mobile.cpp) which currently call `InvokeWidget(enabled)` with only
 * the bool and are just as affected - every one of them is silently
 * looking up whatever garbage id happens to be in ESI at the call,
 * not the intended widget. Deferred as its own pass; not attempted
 * here given the number of sites and the risk of guessing wrong on
 * which id each site actually means.
 */
#include "ghidra_types.h"


undefined4 __fastcall InvokeWidget(undefined4 param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int in_EAX;
  int *piVar3;
  uint unaff_ESI;
  
  iVar1 = *(int *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while( true ) {
    if (param_2 < uVar2) {
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
    if (uVar2 == param_2) break;
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  piVar3 = *(int **)(iVar1 + 0x10);
  uVar2 = piVar3[2];
  if (unaff_ESI < uVar2) {
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  while (uVar2 != unaff_ESI) {
    piVar3 = (int *)piVar3[4];
    uVar2 = piVar3[2];
    if (unaff_ESI < uVar2) {
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
  }
  if (param_3 != '\0') {
    if ((piVar3[9] != 3) && (piVar3[9] != -1)) {
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
    if ((char)piVar3[0x13] == '\x01') {
                    /* WARNING: Could not recover jumptable at 0x00406367. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*piVar3 + 4))();
      /* Ghidra emitted a bare `return;` in a value-returning function;
       * MSVC falls through with whatever's in EAX, gcc 14 rejects it
       * (-Wreturn-mismatch). This path's result is unused by callers -
       * return 0 to satisfy both toolchains without inventing a value. */
      return 0;
    }
                    /* WARNING: Could not recover jumptable at 0x00406374. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*piVar3 + 4))();
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x00406347. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*piVar3 + 4))();
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

