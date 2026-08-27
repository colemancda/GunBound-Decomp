/* FUN_004e1f70 - 0x004e1f70 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-11): CValueGuard sweep - recovered the
 * guard-cell pointers Ghidra dropped from all 51 PeekPacketChecksumState
 * and 56 EncodeOutgoingPacketField calls, per tools/guard_worklist.json
 * (status "clean" both families) + disasm of 0x4e1f70-0x4e2b18. The
 * object base is `this` in EBX (Ghidra's unaff_EBX, already read at
 * +0xefc/+0xf00 below); cells live at base/+0x890/+0xab4/+0xcd8/+0xf08
 * plus globals DAT_00796aa0/DAT_00e9ba40. The 3-iteration do-loop walks
 * a cell cursor Ghidra discarded entirely (0x4e1fa4 lea edi,[ebx+0x890];
 * saved at [esp+0x14]; advanced +0x224 per pass at 0x4e2023, with the
 * paired Encode hitting cursor-0x66c via 0x4e1fcf add edi,-0x66c) -
 * reintroduced as iVar5. Every bare-EDI Peek back-tracked mechanically
 * to its lea (all 25 resolve to the block's preceding cell lea); the 10
 * near-identical if-blocks share one verified cell pattern (gate peek
 * +0xf08; Encode(base,k); Encode(+0xcd8,k-1); Peek(+0xcd8)->
 * Encode(+0xab4); Peek(+0xab4)->Encode(+0x890); Peek(+0xf08)->
 * Encode(+0xf08,v-1)), spot-checked in full against blocks k=1
 * (0x4e21bc), k=2 (0x4e22db) and k=10 (0x4e2a38).
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_EBX is UNIFORM --
 * `g_clientContext + 0x6a64c4` at every one of the seven call sites -- so it
 * needed no pairing of binary sites to source sites at all, which is the one
 * case where filling every site with a single value is safe.
 *
 * Four sites build it as `mov ebx,[0x5b3484]` then `add ebx,0x6a64c4` and
 * three as `lea ebx,[<g_clientContext> + 0x6a64c4]`; the instruction pairs
 * were read off the disassembly at each, including the two that needed the
 * decode window realigned before capstone would resolve them.  The body uses
 * it as an object base (`unaff_EBX + 0x890` and further fields), which is
 * consistent with a context-relative record rather than a list head.
 */
#include "ghidra_types.h"


void FUN_004e1f70(int regEbx)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int unaff_EBX = regEbx;
  int local_4;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00796aa0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = _rand();
  iVar2 = iVar2 % iVar1;
  iVar5 = unaff_EBX + 0x890;
  local_4 = 3;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)iVar5);
    EncodeOutgoingPacketField((void *)(iVar5 + -0x66c), uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar4 = _rand();
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)iVar5, iVar4 % iVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar5 = iVar5 + 0x224;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField((void *)unaff_EBX, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0x890));
  iVar4 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if (iVar1 == iVar4) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
    iVar4 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (iVar1 == iVar4) {
      iVar1 = _rand();
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), iVar1 % 10);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), (iVar1 + 1) % iVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = PeekPacketChecksumState((void *)&DAT_00e9ba40);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), (iVar1 + 9) % iVar4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if ((iVar2 < 3) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if ((9 < iVar2) && (iVar2 < (int)((uint)(*(char *)(g_clientContext + 0x45126) == '\x02') * 2 + 0x10))
     ) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if ((0x13 < iVar2) &&
     (iVar2 < (int)((uint)(*(char *)(g_clientContext + 0x45126) != '\x02') * 4 + 0x1a))) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if ((0x1d < iVar2) &&
     (iVar2 < (int)((uint)(*(char *)(g_clientContext + 0x45126) != '\x02') * 4 + 0x24))) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if ((0x27 < iVar2) &&
     (iVar2 < (int)(((*(char *)(g_clientContext + 0x45126) != '\x02') - 1 & 0xfffffffb) + 0x30))) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if (((0x31 < iVar2) && (iVar2 < 0x34)) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 6);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 5);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if (((0x3b < iVar2) && (iVar2 < 0x3e)) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 6);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if (((0x45 < iVar2) && (iVar2 < 0x4b)) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if (((0x4f < iVar2) && (iVar2 < 0x54)) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 9);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  if (((0x59 < iVar2) && (iVar2 < 0x5c)) && (*(char *)(g_clientContext + 0x45126) != '\x02')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (0 < iVar1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)unaff_EBX, 10);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xcd8), 9);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xcd8));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xab4), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar3 = PeekPacketChecksumState((void *)(unaff_EBX + 0xab4));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0x890), uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar1 = PeekPacketChecksumState((void *)(unaff_EBX + 0xf08));
      EncodeOutgoingPacketField((void *)(unaff_EBX + 0xf08), iVar1 + -1);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    }
  }
  *(undefined4 *)(unaff_EBX + 0xefc) = 0;
  *(undefined4 *)(unaff_EBX + 0xf00) = 1;
  return;
}

