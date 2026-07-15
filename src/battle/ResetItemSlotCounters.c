/* ResetItemSlotCounters - 0x004dbf30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void ResetItemSlotCounters(uint param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  int local_c;
  
  bVar4 = (param_1 & 0xff00) == 0xff00;
  iVar3 = 6 - (uint)bVar4;
  local_c = 0;
  if (0 < iVar3) {
    do {
      if (bVar4) {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (cVar1 == -1) {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          cVar1 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (cVar1 == (char)param_1) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
             * 0x4dc002 (`lea edi,[esi + ecx + 0x39f30]`). esi+0x39f30 is
             * the well-known g_clientContext+0x39f30 per-slot ValueGuard
             * array (0x224-byte stride, 6 slots - see the identical
             * `g_clientContext + 0x39f30 + iVarN` array-base idiom in
             * DrawWindGauge.c/FUN_004cbda0.c/State09_ReadyRoom_*.c,
             * where the same 0x224 stride index is used as a
             * pre-scaled byte offset, not a raw index), so ecx is
             * `local_c*0x224`, the current loop slot's byte offset. See
             * tools/encodeoutgoingpacketfield_sites.json. */
            EncodeOutgoingPacketField(g_clientContext + local_c * 0x224 + 0x39f30, 0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
             * 0x4dc024 (`lea edi,[esi + edx + 0x3a154]`): the parallel
             * array at g_clientContext+0x3a154 (== 0x39f30+0x224, the
             * next element's would-be base - confirmed the same pairing
             * appears together in State09_ReadyRoom_RenderRosterAndItems.c
             * using the same index expression for both bases), same
             * `local_c*0x224` slot offset. See
             * tools/encodeoutgoingpacketfield_sites.json. */
            EncodeOutgoingPacketField(g_clientContext + local_c * 0x224 + 0x3a154, 0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_c = local_c + 1;
          }
        }
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        cVar1 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (cVar1 == -1) {
          local_c = local_c + 1;
        }
        else {
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (uVar2 == (param_1 & 0xff)) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
             * 0x4dc0b9 (`lea edi,[esi + eax + 0x39f30]`): same
             * g_clientContext+0x39f30 per-slot ValueGuard array as the
             * first call above, `local_c*0x224` slot offset. See
             * tools/encodeoutgoingpacketfield_sites.json. */
            EncodeOutgoingPacketField(g_clientContext + local_c * 0x224 + 0x39f30, 0);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
        }
      }
      local_c = local_c + 1;
    } while (local_c < iVar3);
  }
  return;
}

