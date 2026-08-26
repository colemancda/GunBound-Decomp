/* FUN_0045d360 - 0x0045d360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 10 argless PeekPacketChecksumState() calls.  EAX is the
 * caller's object for the whole function (the file's regEax), so the
 * cells are regEax + 0x8de8/0x8bc4/0x900c/0x9678/0x989c/0x9ac0 plus the
 * globals 0xe55ab8 / 0xe9ba40.  The two remaining peeks (0x45d506 and
 * 0x45d5b6) read frame[0x20], loaded at 0x45d4fc / 0x45d5ac from
 * `(*(uint *)(regEax + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4` -
 * the per-player battle stat array this file already indexes the same way
 * at its PeekChecksumStateUnderLock a few lines above (ApplyAvatarStat-
 * Bonuses writes that array; ComputeTurnDelay reads cell 3 of it).
 *
 * EAX RECOVERED (2026-08-25) at all nine sites: the mobile record whose guard
 * cells this reads (+0x8de8 and +0x8bc4).
 *
 * Eight of the nine load it the same way -- `mov eax,[<ctx> + 0x621e0]` with
 * the base traced to g_clientContext -- which is the local-player mobile
 * pointer that ChangePlayerMobile's header already documents ("re-points the
 * local-player record at g_clientContext+0x621e0") and BeginNewTurn reads by
 * the same expression.
 *
 * The ninth (0x4625e9, in SimulateMobileFrame) passes that function's own
 * mobile instead: `mov eax,ebp` where EBP is its incoming ECX, set once at
 * 0x461cbc.  The linear trace reports `pop ebp` there because the call sits
 * past a hoisted epilogue; the entry-path definition is the `mov ebp,ecx`.
 * Simulating a mobile reads that mobile's own cells rather than the local
 * player's, which is the sensible reading and the only site that differs.
 *
 * Two sites in State11_InBattle_OnTick were ALSO short -- they passed nothing
 * to a one-parameter function -- so those are re-slotted, not appended: the
 * binary pushes 0 at both.
 */
#include "ghidra_types.h"


int FUN_0045d360(int param_1,int regEax)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = PeekPacketChecksumState((void *)(regEax + 0x8de8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(regEax + 0x8bc4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar4 = PeekPacketChecksumState((void *)(&DAT_00e55ab8));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = PeekPacketChecksumState((void *)(regEax + 0x900c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar5 = ((400 - iVar3) / iVar4) * iVar5;
  cVar1 = DecodeGuardedBool(regEax + 0x8bae);
  /* DecodeGuardedBool (0x406860) is the NEGATED twin of PeekPacketChecksumBool
   * (0x4065a0): same code, `sete al` on the result.  So this gates the stat
   * term on the guarded bool at regEax+0x8bae being CLEAR.
   *
   * THE ARGUMENT BELOW IS CURRENTLY INERT (2026-08-26).  The cell is right --
   * `lea eax,[esi+0x8bae]` at 0x45d3f9 -- but DecodeGuardedBool is still
   * declared `bool DecodeGuardedBool(void)` with a K&R-empty prototype, so the
   * value is pushed and ignored and the callee still reads an uninitialised
   * `byte *in_EAX`.  Passing it costs nothing and it becomes live the moment
   * that callee is promoted; see the tools/guard_cell_resolve.py commit that
   * added 0x406860 to FAMILY, which is what makes the 35-site sweep possible. */
  if (cVar1 != '\0') {
    cVar1 = PeekPacketChecksumBool((byte *)(regEax + 0x8bba));
    if (cVar1 == '\0') {
      cVar1 = PeekPacketChecksumBool((byte *)(regEax + 0x8bb7));
      if (cVar1 == '\0') {
        iVar3 = regEax + 0x9230;
      }
      else {
        iVar3 = regEax + 0x9454;
      }
      iVar3 = PeekChecksumStateUnderLock(iVar3);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar3 = PeekPacketChecksumState((void *)(regEax + 0x9678));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
    iVar5 = iVar5 + iVar3;
  }
  cVar1 = PeekPacketChecksumBool((byte *)(regEax + 0x8bb4));
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(regEax + 0x989c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = iVar5 + iVar3;
    if (param_1 != '\0') {
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(regEax + 0xbfbc));
      iVar5 = iVar5 + iVar3;
      goto LAB_0045d4b9;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)((*(uint *)(regEax + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(regEax + 0xbfbc));
    if (iVar4 + iVar3 * -3 < 0) {
      iVar3 = 0;
    }
    else {
      iVar4 = PeekChecksumStateUnderLock((*(uint *)(regEax + 8) & 7) * 0x1120 + 0x50cf4 + g_clientContext);
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(regEax + 0xbfbc));
      iVar3 = iVar3 + iVar4 * -3;
    }
  }
  else {
LAB_0045d4b9:
    if (param_1 == '\0') goto LAB_0045d527;
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = PeekPacketChecksumState((void *)(regEax + 0x9ac0));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = PeekPacketChecksumState((void *)((*(uint *)(regEax + 8) & 7) * 0x1120 + g_clientContext + 0x50cf4));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar3 = iVar3 + iVar4 * -3;
  }
  iVar5 = iVar5 + iVar3;
LAB_0045d527:
  *(undefined1 *)(regEax + 0xae68) = 1;
  cVar1 = PeekPacketChecksumBool((byte *)(regEax + 0x8ba8));
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x45d555
     * (`lea edi,[esi+0xae6c]`). Objdump of orig/GunBound.gme confirms
     * esi = eax at function entry (`mov esi,eax` at 0x45d372), i.e. esi is
     * this file's own `regEax`; the cell is regEax+0xae6c. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(regEax + 0xae6c, iVar5 + iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = PeekPacketChecksumState((void *)(&DAT_00e9ba40));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return iVar3 * (iVar5 + iVar2);
}

