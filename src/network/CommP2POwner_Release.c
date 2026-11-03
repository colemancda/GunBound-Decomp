/* CommP2POwner_Release - 0x004fd3c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-29, CERTAIN (was FUN_004fd3c0).  Slot 1 of 0x5575c8, the
 * public-API vtable that ConstructCommP2POwner (0x4fd0f0) stamps at +0
 * (`mov dword ptr [ebp], 0x5575c8` at 0x4fd13a).  Slot 0 of the same
 * table, 0x4fd3b0, is the matching AddRef: `inc dword ptr [ecx+0x1a6c]`;
 * ret.  This slot decrements the same +0x1a6c counter and, at zero, runs
 * DestroyCommP2POwner (0x4fd230) and then _free (0x525546) on the object
 * - the COM-style AddRef/Release pair, so the original member name is
 * used.  Unlike COM's Release it returns nothing (no EAX is set; `ret`
 * with no stack cleanup, ECX = this).
  *
 * FIX (2026-11-03): was __fastcall. It is SLOT 1 of the owner vtable 0x5575c8
 * (.data 0x5575cc = 0x4fd3c0; `dec dword ptr [..+0x1a6c]` on ECX, no stack
 * arguments, plain `ret` at 0x4fd3db), and every C dispatch of that table
 * passes `this` as the first cdecl argument (erased __thiscall), so a
 * __fastcall body read garbage from ECX. Raw-C port: cdecl, this first.
 */
#include "ghidra_types.h"


void CommP2POwner_Release(void *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)((int)param_1 + 0x1a6c);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 == 0) {
    DestroyCommP2POwner(param_1);
    _free(param_1);
  }
  return;
}

