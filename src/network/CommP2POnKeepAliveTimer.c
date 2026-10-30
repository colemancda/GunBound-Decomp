/* CommP2POnKeepAliveTimer - 0x004ffe80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-30, LIKELY (was FUN_004ffe80).  The WM_TIMER handler
 * CommP2PNotifyWndProc runs for the timer id stored at +0x2c4
 * (param_1[0xb1]).  UpsertP2PPeerRecord arms that timer -
 * SetTimer(hwnd, 0x14b, 50000, NULL) - once a peer record exists, and
 * nothing in the tree kills it short of DestroyCommEngine's teardown, so
 * it fires every 50 s for the life of the P2P layer.  Each firing does
 * two unrelated jobs, which is why the name is the trigger rather than
 * either job:
 *   1. to every peer whose record+0x1c flag (node+0x30) is clear - the
 *      flag RetransmitPendingP2PDatagrams sets when a peer exhausts its
 *      retries - it sendto's a bare 0x26-byte header, no payload, with
 *      the record's +0x18 counter (node+0x2c, post-incremented) as the
 *      sequence word.  0x26 is the size CommP2PReceiveDatagram treats as
 *      a header-only datagram: it checks the addressing, looks the
 *      sender up, tries to retire that sequence from its pending map,
 *      and then overwrites the sender's stored address with the
 *      recvfrom source.  A periodic header-only send whose only lasting
 *      effect on the far side is that address refresh is a keep-alive;
 *      that reading is the LIKELY part.
 *   2. it walks each record's +0x80 array (node+0x94/+0x98, stride
 *      0x1750 - the datagrams FUN_004fe110 queues while a peer has no
 *      address and UpsertP2PPeerRecord flushes) and expires entries whose
 *      time() stamp at +0x174c is more than 60 s old (`cmp eax,0x3c;
 *      jle` at 0x500048): each goes to the owner's slot-0 delivery
 *      callback with a leading 0 (failure; RetransmitPendingP2PDatagrams
 *      reports exhausted retries the same way) and is removed in place
 *      with the ATL RemoveAt bounds checks (ThrowCxxException(E_INVALIDARG)).
 * The scoping pass's alternative, SendP2PKeepAlives, would hide job 2.
 *
 * DISPATCH `this` RESTORED (2026-10-30): the slot-0 call at 0x500069
 * sets ECX = param_1 as `this` (`mov ecx,[esp+0x58]` at 0x50004d: the
 * frame is sub esp,0x44 plus esi/ebx/edi/ebp pushed, so +0x58 is the
 * first stack argument); the port dropped it.  param_1 is the CCommP2P
 * sub-object (vtable 0x5575ac); slot 0 is 0x504800 (read from .rdata),
 * not carved, ret 0x18 - six stack arguments, matching the six pushes.
 * Treated, as in RetransmitPendingP2PDatagrams, as a raw-C erased
 * __thiscall: cdecl with `this` first (P2PDeliveryResultFn).
 */
#include "ghidra_types.h"

/* Slot 0 of the CCommP2P vtable 0x5575ac: the delivery-result callback
 * 0x504800 (not carved, ret 0x18): erased __thiscall, cdecl `this` first. */
typedef void (*P2PDeliveryResultFn)(undefined4 *self,int ok,char *node,uint seq,int addr,
                                     uint port,int payload);


void CommP2POnKeepAliveTimer(undefined4 *param_1)

{
  char *pcVar1;
  char *_Source;
  char cVar2;
  uint uVar3;
  __time32_t _Var4;
  int *piVar5;
  int iVar6;
  int iVar7;
  SOCKET s;
  uint local_44;
  char *local_40;
  sockaddr local_38;
  ushort local_28;
  undefined1 local_26 [16];
  char local_16 [16];
  undefined4 local_6;
  
  local_28 = 0x26;
  cVar2 = FUN_004fcd80(local_26,0x10,(int)param_1 + 4);
  if (cVar2 != '\0') {
    local_38.sa_family = 2;
    if (param_1[0xa5] != 0) {
      uVar3 = 0;
      if (param_1[0xa6] != 0) {
        piVar5 = (int *)param_1[0xa4];
        do {
          if (*piVar5 != 0) {
            local_40 = (char *)((int *)param_1[0xa4])[uVar3];
            goto joined_r0x004ffee3;
          }
          uVar3 = uVar3 + 1;
          piVar5 = piVar5 + 1;
        } while (uVar3 < (uint)param_1[0xa6]);
      }
    }
    local_40 = (char *)0x0;
joined_r0x004ffee3:
    _Source = local_40;
    if (_Source != (char *)0x0) {
      local_40 = _Source;
      if ((_Source != (char *)0x0) &&
         (local_40 = *(char **)(_Source + 0xa4), local_40 == (char *)0x0)) {
        uVar3 = *(uint *)(_Source + 0xa8) % (uint)param_1[0xa6];
        do {
          uVar3 = uVar3 + 1;
          if ((uint)param_1[0xa6] <= uVar3) break;
          pcVar1 = *(char **)(param_1[0xa4] + uVar3 * 4);
          if (pcVar1 != (char *)0x0) {
            local_40 = pcVar1;
          }
        } while (local_40 == (char *)0x0);
      }
      if (_Source[0x30] == '\0') {
        _strncpy(local_16,_Source,0x10);
        local_6 = *(undefined4 *)(_Source + 0x2c);
        *(int *)(_Source + 0x2c) = *(int *)(_Source + 0x2c) + 1;
        if (*(int *)(_Source + 0x14) == 0) {
          if (*(int *)(_Source + 0x1c) != 0) {
            SUBFIELD(local_38.sa_data,0,undefined2) = *(undefined2 *)(_Source + 0x20);
            SUBFIELD(local_38.sa_data,2,undefined4) = *(int *)(_Source + 0x1c);
            sendto(param_1[0xa2],(char *)&local_28,(uint)local_28,0,&local_38,0x10);
          }
          if (*(int *)(_Source + 0x24) == 0) goto LAB_00500008;
          s = param_1[0xa2];
          SUBFIELD(local_38.sa_data,0,undefined2) = *(undefined2 *)(_Source + 0x28);
          SUBFIELD(local_38.sa_data,2,undefined4) = *(int *)(_Source + 0x24);
        }
        else {
          SUBFIELD(local_38.sa_data,0,undefined2) = *(undefined2 *)(_Source + 0x18);
          s = param_1[0xa2];
          SUBFIELD(local_38.sa_data,2,undefined4) = *(int *)(_Source + 0x14);
        }
        sendto(s,(char *)&local_28,(uint)local_28,0,&local_38,0x10);
      }
LAB_00500008:
      local_44 = *(uint *)(_Source + 0x98);
      uVar3 = local_44 - 1;
      if (-1 < (int)uVar3) {
        iVar6 = uVar3 * 0x1750;
        do {
          if (*(uint *)(_Source + 0x98) <= uVar3) {
LAB_005000d3:
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          iVar7 = *(int *)(_Source + 0x94) + iVar6;
          _Var4 = FID_conflict___time32((__time32_t *)0x0);
          if (0x3c < _Var4 - *(int *)(iVar7 + 0x174c)) {
            /* 0x50004d: ECX = this, call [vtbl+0] at 0x500069 */
            ((P2PDeliveryResultFn)*(code **)*param_1)
                      (param_1,0,_Source,*(ushort *)(iVar7 + 0xc),iVar7 + 0x10,
                       *(ushort *)(iVar7 + 0xe),iVar7);
            if (*(uint *)(_Source + 0x98) < local_44) goto LAB_005000d3;
            iVar7 = (*(uint *)(_Source + 0x98) - uVar3) + -1;
            if (iVar7 != 0) {
              _memmove((void *)(*(int *)(_Source + 0x94) + iVar6),
                       (void *)(*(int *)(_Source + 0x94) + iVar6 + 0x1750),iVar7 * 0x1750);
            }
            *(int *)(_Source + 0x98) = *(int *)(_Source + 0x98) + -1;
          }
          uVar3 = uVar3 - 1;
          local_44 = local_44 - 1;
          iVar6 = iVar6 + -0x1750;
        } while (-1 < (int)uVar3);
      }
      goto joined_r0x004ffee3;
    }
  }
  return;
}

