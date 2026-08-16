/* SyncOutgoingChecksumField - 0x004262d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the prologue
 * (0x4262d7) is `mov esi,ecx; mov edi,eax` - so besides its two stack
 * arguments this takes a CONTEXT in ECX and a CELL in EAX, and Ghidra kept
 * neither.  ESI is only used as `lea eax,[esi + 0x6a7f74]` (a context-relative
 * GuardedBool), so the cell is the EAX one, now the explicit `self` parameter;
 * the third peek reads EDI, which the prologue set from that same EAX.
 *
 * All 82 call sites were resolved before this promotion.  They come in a very
 * regular shape: one "object" call whose cell is <obj> + 0x3d5 (0xf54 bytes,
 * exactly one 0x224 cell below the + 0x45e it already passes), plus a PAIR of
 * scratch calls that SWAP their two stack cells - each one's dropped EAX cell
 * is the other one's second argument (verified instruction-by-instruction at
 * DetonateProjectile 0x4577ea/0x4578b8 and DetonatePrimaryShot_Bullet4
 * 0x4a376d/0x4a3839).  NOTE the C sites of that pair are in the REVERSE of
 * address order, which is why the swap is stated in terms of the C arguments
 * rather than the address sequence.
 */
#include "ghidra_types.h"


void SyncOutgoingChecksumField(void *self,int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  code *pcVar5;
  ushort local_8 [2];
  uint local_4;
  
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState(param_2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState(self);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    InsertChecksumStateRecord(uVar3,uVar2);
    return;
  }
  cVar1 = FindChecksumStateRecord(local_8,&param_1);
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    local_4 = PeekPacketChecksumState(self);
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((local_8[0] == local_4) && (uVar4 = PeekChecksumStateUnderLock(param_2), param_1 == uVar4)) {
      return;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4263ae/
     * 0x4263cc/0x4263e9 all 3 calls in this function use the same cell,
     * param_2 (already used as a cell pointer at this function's
     * PeekChecksumStateUnderLock(param_2) call above; register-resident
     * as EAX for the first two, stack-spilled to [esp+0x24] for the third
     * after the intervening critical-section calls). See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(param_2, (uint)local_8[0]);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = (uint)param_1;
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_2, 0xffffff9c);
    pcVar5 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = 0xffffff9c;
  }
  EncodeOutgoingPacketField(param_2, uVar4);
  (*pcVar5)(&DAT_005a9068);
  return;
}

