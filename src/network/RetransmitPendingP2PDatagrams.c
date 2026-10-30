/* RetransmitPendingP2PDatagrams - 0x004ffbe0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, CERTAIN (was FUN_004ffbe0).  The WM_TIMER handler
 * CommP2PNotifyWndProc runs for the timer id stored at +0x2c0
 * (param_1[0xb0]).  That timer is armed by the P2P send path FUN_004fe110
 * - SetTimer(hwnd, 0x14a, 900, NULL) into +0x2c0 - right after it
 * sends a datagram through SendEncryptedP2PDatagram and records a copy
 * with IntMap_SetAt_1768 in the peer record's +0x50 map, stamped with
 * GetSystemTimeAsFileTime.  This walks every peer-table node (record at
 * node+0x14, so that map is node+0x64) and every entry in it:
 *   - fewer than 6 tries (`cmp eax,5; jle` at 0x4ffd0f) and older than
 *     900 ms (`cmp eax,0x384; jbe` at 0x4ffda2, the FILETIME delta
 *     divided by 10000): resend the stored copy through
 *     SendEncryptedP2PDatagram to the peer's address(es), try count +1;
 *   - out of tries: either one second round (tries reset, flags set),
 *     or hand the entry to the owner's vtable slot 0 with a leading 0
 *     and IntMap_RemoveKey_1768 it.  CommP2PReceiveDatagram makes the
 *     same slot-0 call with a leading 1 when an ACK retires an entry
 *     from the same map, so slot 0 is the delivery-result callback and
 *     this is the failure half.
 * When nothing is left pending it KillTimer's +0x2c0 and zeroes it, so
 * the next FUN_004fe110 send re-arms it.
 *
 * DISPATCH `this` RESTORED (2026-10-30): both owner-vtable calls set
 * ECX = EBX = param_1 as `this` (`mov ecx,ebx` at 0x4ffd2c and 0x4ffd67;
 * EBX = [esp+0x40] = param_1 at 0x4ffbf8 and again at 0x4ffd73); the
 * port dropped it.  param_1 is the CCommP2P sub-object at owner+0x2c,
 * whose vtable ConstructCommP2POwner stamps as 0x5575ac.  Read from the
 * original's .rdata: slot 0 = 0x504800, slot 1 = 0x504880.
 *   - slot 1 (call at 0x4ffd2e, one push: EBP = the peer node, whose
 *     first 0x10 bytes are the peer name) is RequestP2PPeerByName,
 *     ported as (char *name, int regEcx) with `this` as the trailing
 *     regEcx (it reads regEcx - 0x2c = the owner).  The call goes
 *     through P2PRequestPeerFn, that exact shape.
 *   - slot 0 (call at 0x4ffd69, six pushes, ret 0x18 at 0x504853) is
 *     not carved; like the session-handler slot in
 *     CommP2POwner_OnConnectionClosed it is treated as a raw-C erased
 *     __thiscall, cdecl with `this` first (P2PDeliveryResultFn).
 * The vtable is still the placeholder PTR_LAB_005575ac, so neither path
 * runs yet.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20): the 2 SendEncryptedP2PDatagram() calls here
 * (orig 0x4ffdec/0x4ffe24) were each missing the callee's leading
 * __thiscall arg. Both sites do `mov ecx,ebp` immediately before the
 * call - EBP is not used as a frame pointer in this function (see the
 * `push ebx/push ebp/push esi/push edi` prologue after `sub esp,0x2c`);
 * it is a GPR holding the same struct pointer the source calls `iVar6`
 * (read at `+0x14/+0x18/+0x1c/+0x20/+0x24/+0x28` around both call sites,
 * matching `iVar6`'s field accesses in this file). See SendEncryptedP2PDatagram.c's
 * header for the callee-side evidence.
 */
#include "ghidra_types.h"

/* Slot 1 of the CCommP2P vtable 0x5575ac: RequestP2PPeerByName (0x504880),
 * whose port takes the ECX `this` as its trailing regEcx. */
typedef uint (*P2PRequestPeerFn)(char *name,int self);
/* Slot 0 of the CCommP2P vtable 0x5575ac: the delivery-result callback
 * 0x504800 (not carved, ret 0x18): erased __thiscall, cdecl `this` first. */
typedef void (*P2PDeliveryResultFn)(int *self,int ok,int node,uint seq,void *addr,uint port,
                                     void *payload);


void RetransmitPendingP2PDatagrams(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  _FILETIME local_18;
  undefined2 uStack_10;
  undefined2 uStack_e;
  undefined2 uStack_c;
  undefined2 uStack_a;
  undefined2 uStack_8;
  undefined4 uStack_6;
  undefined2 uStack_2;
  
  local_24 = 0;
  GetSystemTimeAsFileTime(&local_18);
  if (param_1[0xa5] != 0) {
    uVar5 = 0;
    if (param_1[0xa6] != 0) {
      piVar7 = (int *)param_1[0xa4];
      do {
        if (*piVar7 != 0) {
          iVar6 = ((int *)param_1[0xa4])[uVar5];
          goto LAB_004ffc26;
        }
        uVar5 = uVar5 + 1;
        piVar7 = piVar7 + 1;
      } while (uVar5 < (uint)param_1[0xa6]);
    }
  }
  iVar6 = 0;
LAB_004ffc26:
  if (iVar6 != 0) {
    do {
      if (iVar6 == 0) {
        local_28 = 0;
      }
      else {
        local_28 = *(int *)(iVar6 + 0xa4);
        if (local_28 == 0) {
          uVar5 = *(uint *)(iVar6 + 0xa8) % (uint)param_1[0xa6];
          local_28 = 0;
          do {
            uVar5 = uVar5 + 1;
            if ((uint)param_1[0xa6] <= uVar5) break;
            iVar2 = *(int *)(param_1[0xa4] + uVar5 * 4);
            if (iVar2 != 0) {
              local_28 = iVar2;
            }
          } while (local_28 == 0);
        }
      }
      if (*(int *)(iVar6 + 0x68) != 0) {
        uVar5 = 0;
        if (*(uint *)(iVar6 + 0x6c) != 0) {
          piVar7 = *(int **)(iVar6 + 100);
          do {
            if (*piVar7 != 0) {
              puVar3 = (undefined4 *)(*(int **)(iVar6 + 100))[uVar5];
              goto joined_r0x004ffcb0;
            }
            uVar5 = uVar5 + 1;
            piVar7 = piVar7 + 1;
          } while (uVar5 < *(uint *)(iVar6 + 0x6c));
        }
      }
      puVar3 = (undefined4 *)0x0;
joined_r0x004ffcb0:
      if (puVar3 != (undefined4 *)0x0) {
        if (puVar3 == (undefined4 *)0x0) {
          local_2c = (undefined4 *)0x0;
        }
        else {
          local_2c = (undefined4 *)puVar3[0x5d8];
          if (local_2c == (undefined4 *)0x0) {
            uVar5 = (uint)puVar3[0x5d9] % *(uint *)(iVar6 + 0x6c);
            local_2c = (undefined4 *)0x0;
            do {
              uVar5 = uVar5 + 1;
              if (*(uint *)(iVar6 + 0x6c) <= uVar5) break;
              puVar8 = *(undefined4 **)(*(int *)(iVar6 + 100) + uVar5 * 4);
              if (puVar8 != (undefined4 *)0x0) {
                local_2c = puVar8;
              }
            } while (local_2c == (undefined4 *)0x0);
          }
        }
        uVar1 = *puVar3;
        puVar8 = puVar3 + 1;
        if ((int)puVar3[0x5d6] < 6) {
          uVar5 = __aulldiv(local_18.dwLowDateTime - puVar3[0x5d4],
                            (local_18.dwHighDateTime - puVar3[0x5d5]) -
                            (uint)(local_18.dwLowDateTime < (uint)puVar3[0x5d4]),10000,0);
          if (uVar5 < 0x385) goto LAB_004ffe2f;
          iVar2 = *(int *)(iVar6 + 0x14);
          uStack_e = 0;
          uStack_c = 0;
          uStack_a = 0;
          uStack_8 = 0;
          uStack_6 = 0;
          uStack_2 = 0;
          uStack_10 = 2;
          if (iVar2 == 0) {
            iVar2 = *(int *)(iVar6 + 0x1c);
            if (iVar2 != 0) {
              uStack_e = *(undefined2 *)(iVar6 + 0x20);
              uStack_c = (undefined2)iVar2;
              uStack_a = (undefined2)((uint)iVar2 >> 0x10);
              SendEncryptedP2PDatagram((char *)iVar6,(int)param_1,(int)puVar8,(sockaddr *)&uStack_10,uVar1);
            }
            iVar2 = *(int *)(iVar6 + 0x24);
            if (iVar2 != 0) {
              uStack_e = *(undefined2 *)(iVar6 + 0x28);
              uStack_c = (undefined2)iVar2;
              uStack_a = (undefined2)((uint)iVar2 >> 0x10);
              goto LAB_004ffe20;
            }
          }
          else {
            uStack_c = (undefined2)iVar2;
            uStack_a = (undefined2)((uint)iVar2 >> 0x10);
            uStack_e = *(undefined2 *)(iVar6 + 0x18);
LAB_004ffe20:
            SendEncryptedP2PDatagram((char *)iVar6,(int)param_1,(int)puVar8,(sockaddr *)&uStack_10,uVar1);
          }
          puVar3[0x5d6] = puVar3[0x5d6] + 1;
LAB_004ffe2f:
          local_24 = local_24 + 1;
          puVar3 = local_2c;
        }
        else {
          if ((*(char *)(puVar3 + 0x5d7) == '\0') &&
             ((*(char *)(iVar6 + 0x30) != '\0' ||
              (cVar4 = (char)((P2PRequestPeerFn)*(code **)(*param_1 + 4))((char *)iVar6,(int)param_1),
               cVar4 != '\0')))) {
            puVar3[0x5d6] = 0;
            *(undefined1 *)(puVar3 + 0x5d7) = 1;
            *(undefined1 *)(iVar6 + 0x30) = 1;
            goto LAB_004ffe2f;
          }
          /* 0x4ffd67: ECX = EBX = this, call [vtbl+0] */
          ((P2PDeliveryResultFn)*(code **)*param_1)
                    (param_1,0,iVar6,*(ushort *)(puVar3 + 4),puVar3 + 5,
                     *(ushort *)((int)puVar3 + 0x12),puVar8);
          IntMap_RemoveKey_1768((int *)(iVar6 + 100),uVar1);
          puVar3 = local_2c;
        }
        goto joined_r0x004ffcb0;
      }
      iVar6 = local_28;
    } while (local_28 != 0);
    if (local_24 != 0) {
      return;
    }
  }
  if (param_1[0xb0] != 0) {
    KillTimer((HWND)param_1[0xa3],param_1[0xb0]);
    param_1[0xb0] = 0;
  }
  return;
}

