/* SpawnRiderEffect - 0x0042bb10 in the original binary.
 *
 * RENAMED (2026-08-17, from FUN_0042bb10): allocates a 0x48 effect object with the "rider" texture (s_rider_00553f98), clamps its Y to g_nCameraBoundY-0x26 and picks facing from the screen half; gated by the effects flag.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND ESI RECOVERED (2026-08-27).  `ret 8` gives two
 * stack arguments against three declared parameters, so param_1 is ECX and
 * only param_2/param_3 are pushed -- but every site passed just TWO values,
 * which were landing in param_1 and param_2 instead of param_2 and param_3.
 *
 * The body says what the registers are: param_1 is compared against
 * g_nCameraBoundY and unaff_ESI against g_nCameraBoundX / 2, so ECX is the Y
 * coordinate and ESI the X.
 *
 * Four of the five sites are in FUN_004ce610 and are identical -- `xor ecx,ecx`
 * (Y = 0) with `mov esi,[ebp + 0x29c]` where ebp is that function's param_1 --
 * so they need no pairing among themselves.
 *
 * AdvanceTurnQueue's site takes both from peeks the source currently
 * DISCARDS.  Its ESI is local_45c, which the line above reassigns from
 * `PeekPacketChecksumState(piVar2 + 0x243)` (Ghidra reuses that name; earlier
 * in the function it holds the terrain context, and at the call it does not).
 * Its ECX is the result of the OTHER peek, `PeekPacketChecksumState(piVar2 +
 * 0x2cc)`, whose value the port throws away: `mov [esp+0x18],eax` at 0x4cf45b
 * carries ONE pending push, so it writes frame E-0x468, which is exactly the
 * slot `mov ecx,[esp+0x14]` reads back at 0x4cf485 four pushes deep.  Without
 * the pending-push term those two look like different slots and the value
 * looks unwritten.
 *
 * Frame anchors for that caller, each checked against the source: `mov
 * [esp+0x14],esi` before the ebp/edi pushes is local_460, matching
 * `local_460 = param_1`; [esp+0x18] four pushes deep is local_464; and
 * `mov [esp+0x24],eax` one push deep is local_45c.
 */
#include "ghidra_types.h"


void __thiscall SpawnRiderEffect(int param_1,undefined4 param_2,int param_3,int regEsi)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int unaff_ESI = regEsi;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x48);
    if (pvVar2 == (void *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)InitRiderEffect();
    }
    iVar5 = g_clientContext;
    piVar3[0xe] = unaff_ESI;
    iVar4 = *(int *)(&g_nCameraBoundY + iVar5) + -0x26;
    if (param_1 <= *(int *)(&g_nCameraBoundY + iVar5) + -0x26) {
      iVar4 = param_1;
    }
    piVar3[0xf] = iVar4;
    piVar3[0x11] = param_3;
    *(bool *)(piVar3 + 0x10) = *(int *)(&g_nCameraBoundX + iVar5) / 2 < unaff_ESI;
    iVar5 = FindPreloadedTextureByName(s_rider_00553f98);
    piVar3[7] = iVar5;
    (**(code **)(*piVar3 + 4))(&DAT_00553f90);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

