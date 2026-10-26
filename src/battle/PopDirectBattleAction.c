/* PopDirectBattleAction - 0x004e7b60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), LIKELY. Drains the 0x206-byte-stride record array at
 * g_replayContext+0x454a4/+0x454a8 (count at +0x454a8, this function's own
 * first check), one record per call, returning it through param_2/param_3
 * and removing it from the array (memmove-shift-down) on success. That
 * array is filled ONLY by ProcessUdpProbeDatagram.c's
 * `CArray_Add_206((param_1+0x1b0),(param_1+0x454a4))` - the UDP peer-to-
 * peer probe/relay receive path, already named - whose record layout
 * (confirmed there: byte at +4 is the per-slot id, 0-7, checked against
 * `if (7 < local_243) goto ...`) matches this function's own gating logic:
 * it looks up each record's key via TurnEventSet_Find and, using the
 * record's slot-id byte as an index into an 8-bit "seen" bitmap, pops the
 * first record whose key is ready while skipping ones whose slot is still
 * blocked by an earlier not-ready record - i.e. per-slot FIFO delivery
 * order, out-of-order between slots. Sole caller PumpBattleActions.c
 * drains this array FIRST (before PopBroadcastBattleAction's array) and,
 * only for this array, also writes each popped record to the replay file
 * before calling ApplyBattleActionToContext - matching this tree's
 * existing "direct-link" terminology for the peer-to-peer connection
 * (g_directLinkConnection, see include/globals.h), as opposed to the
 * server-relayed array PopBroadcastBattleAction drains.
 *
 * DROPPED KEY RECOVERED (2026-08-27): 0x4e7bc6 `mov cx,word ptr
 * [edi + eax]` with eax = *(param_1 + 0x454a4) and edi = iVar6 (the
 * same register the loop steps by 0x206, and the same base+4 the
 * local_8 index below reads), zero-extended into the [esp+0x20]
 * slot that `lea ebx,[esp+0x20]` then hands to the lookup.  Ghidra
 * dropped the store along with the argument, so the slot itself
 * had to be reintroduced.
 */
#include "ghidra_types.h"


uint PopDirectBattleAction(int param_1,undefined4 *param_2,uint *param_3)

{
  ushort uVar1;
  uint uVar2;
  void *_Dst;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int local_c;
  uint keySlot; /* the [esp+0x20] slot Ghidra dropped - see below */
  char local_8 [8];

  uVar2 = 0;
  if (*(int *)(param_1 + 0x454a8) == 0) {
    return 0;
  }
  uVar4 = 0;
  local_8[0] = '\0';
  local_8[1] = 0;
  local_8[2] = 0;
  local_8[3] = 0;
  local_8[4] = 0;
  local_8[5] = 0;
  local_8[6] = 0;
  local_8[7] = 0;
  if (*(int *)(param_1 + 0x454a8) != 0) {
    iVar6 = 0;
    if (*(int *)(param_1 + 0x454a8) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      keySlot = *(ushort *)(*(int *)(param_1 + 0x454a4) + iVar6);
      TurnEventSet_Find(param_1 + 0x45230,(undefined4 *)&local_c,(ushort *)&keySlot);
      if (local_c == *(int *)(param_1 + 0x45234)) {
        if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        if (local_8[*(byte *)(*(int *)(param_1 + 0x454a4) + 4 + iVar6)] == '\0') {
          if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          iVar6 = uVar4 * 0x206;
          uVar1 = *(ushort *)(*(int *)(param_1 + 0x454a4) + 2 + iVar6);
          *param_3 = (uint)uVar1;
          if (uVar4 < *(uint *)(param_1 + 0x454a8)) {
            puVar5 = (undefined4 *)(iVar6 + 5 + *(int *)(param_1 + 0x454a4));
            for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
              *param_2 = *puVar5;
              puVar5 = puVar5 + 1;
              param_2 = param_2 + 1;
            }
            for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *(undefined1 *)param_2 = *(undefined1 *)puVar5;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
              param_2 = (undefined4 *)((int)param_2 + 1);
            }
            if (uVar4 + 1 <= *(uint *)(param_1 + 0x454a8)) {
              iVar3 = (*(uint *)(param_1 + 0x454a8) - uVar4) + -1;
              if (iVar3 != 0) {
                _Dst = (void *)(iVar6 + *(int *)(param_1 + 0x454a4));
                _memmove(_Dst,(void *)((int)_Dst + 0x206),iVar3 * 0x206);
              }
              iVar6 = *(int *)(param_1 + 0x454a8) + -1;
              *(int *)(param_1 + 0x454a8) = iVar6;
              return CONCAT31((int3)((uint)iVar6 >> 8),1);
            }
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
      }
      else {
        if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        local_8[*(byte *)(*(int *)(param_1 + 0x454a4) + 4 + iVar6)] = '\x01';
      }
      uVar2 = *(uint *)(param_1 + 0x454a8);
      uVar4 = uVar4 + 1;
      iVar6 = iVar6 + 0x206;
    } while (uVar4 < uVar2);
  }
  return uVar2 & 0xffffff00;
}
