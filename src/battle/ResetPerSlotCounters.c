/* ResetPerSlotCounters - 0x004d09c0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence. The body zeroes eight guarded cells, one per player slot, at
 * object + 0x11dc + k * 0x224 (the 0x224 stride is the per-slot stride
 * EquipAvatarPart and FinishTurnAndSelectNext use). The same cells are the
 * per-slot counter that FinishTurnAndSelectNext peeks at (cursor
 * param_1 + 0x11dc + k * 0x224, "every slot whose counter is > 1 gets it
 * reset") and that ProcessBattleAction increments with
 * EncodeIncrementedChecksum on param_1 + 0x11dc. The callers use it as a
 * bulk reset at the end of a turn pass: after the per-slot loop in
 * ProcessBattleAction, at the end of FinishTurnAndSelectNext and of
 * FUN_004ccd10 (its sibling), and in OnEnter after the +0x22fc seed bytes are
 * written. What the counter counts is not established, so the name keeps the
 * structural noun. LIKELY.
 *
 * Recovered argument. The object arrives in EAX and was dropped, so the
 * eight EncodeOutgoingPacketField calls had no cell (EDI in the original is
 * object + 0x11dc, advanced by 0x224 per iteration). It is now the
 * parameter regEax. Each of the four sites was checked from disassembly:
 *  - ProcessBattleAction 0x4b7fad: mov eax, edi with edi = [esp+0x14], the
 *    saved entry ECX (0x4b549f mov edi, ecx; 0x4b54a1 stores it; the later
 *    writes to that offset are after pushes and hit a different slot). That
 *    is local_27ec = param_1 in the port, the base the 0x11dc increment
 *    below already uses.
 *  - OnEnter 0x4bc784: mov eax, ebp, the same ebp whose +0x22fc..0x22fe
 *    bytes were just stored (param_1).
 *  - FinishTurnAndSelectNext 0x4cb8d6: mov eax, edi; both paths into
 *    0x4cb8d4 reload edi from [esp+0x72c], the first stack argument
 *    (0x70c locals + 4 pushes + 3 SEH words + return address).
 *  - FUN_004ccd10 0x4cd6e0: mov eax, ebx after ebx is reloaded from
 *    [esp+0x730], its first stack argument; the three jumps straight to
 *    0x4cd6de come from a block where ebx still holds param_1 (it is the
 *    base of the 0x2382 read at 0x4cd643).
 */
#include "ghidra_types.h"


void ResetPerSlotCounters(int regEax)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 8;
  iVar2 = regEax + 0x11dc;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField((void *)iVar2,0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = iVar2 + 0x224;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}

