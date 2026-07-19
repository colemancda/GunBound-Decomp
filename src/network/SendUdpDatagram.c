/* SendUdpDatagram - 0x004e72d0 in the original binary.
 *
 * Sends one UDP datagram from a connection object's socket to an
 * explicit (address, port) peer. The address/port arrive in ECX/EDX
 * (__fastcall), the payload/length on the stack, and the connection
 * object itself in EAX.
 *
 * RECOVERED (2026-07-19), verified with angr/capstone against the
 * original. Two separate layers of dropped register arguments:
 *
 * 1. CALLEE - the connection object arrives in EAX. The very first
 *    instruction of the function reads it before any write:
 *      0x4e72d0  mov eax, dword ptr [eax + 0x14]     ; socket handle
 *    Ghidra emitted this as an uninitialised `in_EAX`, so the port
 *    fetched its SOCKET from a garbage pointer. Promoted to the
 *    trailing `connection` parameter (the repo's established idiom -
 *    see src/network/AllocCipherSchedule.c).
 *
 * 2. CALL SITES - ECX (destination address) and EDX (destination port)
 *    are loaded at every one of the 16 call sites, but Ghidra
 *    decompiled the *callers* against a 2-argument (buf, len)
 *    signature and dropped both. All 16 sites were disassembled; every
 *    one follows one of two shapes, with `idx` the peer slot:
 *      primary : ecx = *(int   *)(conn + 0x18 + idx*4)
 *                dx  = *(short *)(conn + 0x58 + idx*2)
 *      fallback: ecx = *(int   *)(conn + 0x38 + idx*4)   (guarded != -1)
 *                dx  = *(short *)(conn + 0x68 + idx*2)
 *    e.g. 0x4e7219 `mov ecx,[esi+ebx*4+0x18]` / 0x4e7214
 *    `mov dx,[esi+ebx*2+0x58]` before the call at 0x4e7221, and
 *    0x4e7226 `mov ecx,[esi+ebx*4+0x38]` / 0x4e7233
 *    `mov dx,[esi+ebx*2+0x68]` before 0x4e723b. The two keepalive
 *    sites (0x4e68e0, 0x4e7728) instead use the stored last-peer pair
 *    `ecx = *(int *)(conn + 0x4520c)` / `dx = *(short *)(conn +
 *    0x45210)`. Recovering these was forced by giving the function a
 *    real prototype in include/functions.h: the previous empty
 *    declaration `undefined4 __fastcall SendUdpDatagram();` let the
 *    2-argument calls through with garbage in buf/len.
 *
 * The port's `param_1`/`param_2` are the address/port; the guard at
 * 0x4e72db/0x4e72ef (`cmp ecx,-1` / `cmp dx,0xffff`) drops datagrams
 * aimed at an unset peer slot.
 */
#include "ghidra_types.h"


undefined4 __fastcall SendUdpDatagram(int param_1,int param_2,char *param_3,int param_4,
                                     int connection)

{
  int in_EAX;
  int iVar1;
  sockaddr local_10;

  in_EAX = connection;
  if (*(SOCKET *)(in_EAX + 0x14) != 0xffffffff) {
    local_10.sa_family = 2;
    if ((param_1 != -1) && (param_2 != -1)) {
      SUBFIELD(local_10.sa_data,0,undefined2) = param_2;
      SUBFIELD(local_10.sa_data,2,undefined4) = param_1;
      iVar1 = sendto(*(SOCKET *)(in_EAX + 0x14),param_3,param_4,0,&local_10,0x10);
      if (iVar1 == -1) {
        ShowErrorDialog(1);
        WSAGetLastError();
        return 0;
      }
    }
  }
  return 1;
}

