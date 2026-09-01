/* CreateBoundSocket - 0x004fe060 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fe060).  Creates a socket, bind()s it, and
 * registers it for asynchronous notification with WSAAsyncSelect.  There is no
 * listen() call, so this is the bound-but-not-listening socket the datagram
 * paths (sendto/recvfrom, FUN_004feb00 and FUN_004ff770) use rather than a
 * TCP server socket - named for what it does rather than for a role that is
 * not proven.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 CreateBoundSocket(char *regEax,int regEsi)

{
  char cVar1;
  SOCKET SVar2;
  int iVar3;
  sockaddr local_10;
  
  {
    char *startStr = regEax;
    do {
      cVar1 = *regEax;
      regEax = regEax + 1;
    } while (cVar1 != '\0');
    /* RECOVERED (2026-07-19), orig 0x4fe077-0x4fe07c: `sub ecx,edi` (ECX =
     * the strlen), `lea edx,[esi+4]` (EDX = the crypto context), EAX = the
     * string base. All three were dropped. */
    FUN_005051e0((int)(regEax - startStr) - 1,regEsi + 4,startStr);
  }
  if (*(int *)(regEsi + 0x288) != -1) {
    return 1;
  }
  SVar2 = socket(2,2,0);
  *(SOCKET *)(regEsi + 0x288) = SVar2;
  if (SVar2 != 0xffffffff) {
    local_10.sa_family = 2;
    local_10.sa_data[0] = '\0';
    local_10.sa_data[1] = '\0';
    SUBFIELD(local_10.sa_data,2,undefined4) = htonl(0);
    iVar3 = bind(*(SOCKET *)(regEsi + 0x288),&local_10,0x10);
    if ((iVar3 != -1) &&
       (iVar3 = WSAAsyncSelect(*(SOCKET *)(regEsi + 0x288),*(HWND *)(regEsi + 0x28c),0x54d,3),
       iVar3 != -1)) {
      return 1;
    }
  }
  return 0;
}

