/* ConnectToHostPort - 0x004fe5f0 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fe5f0).  Opens a TCP socket and connects it:
 * socket(), htons(param_2) for the port, connect(), with WSAGetLastError and
 * closesocket on failure.  Its parameter list already says so - `(undefined4
 * host, u_short port)`.  Called from ResolveHostAddress.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


int ConnectToHostPort(undefined4 param_1,u_short param_2,int regEbx)

{
  SOCKET s;
  int iVar1;
  int iVar2;
  int unaff_EBX = regEbx;
  sockaddr local_10;
  
  s = socket(2,1,0);
  iVar1 = 0;
  if (s != 0xffffffff) {
    local_10.sa_data[0] = '\0';
    local_10.sa_data[1] = '\0';
    local_10.sa_data[6] = '\0';
    local_10.sa_data[7] = '\0';
    local_10.sa_data[8] = '\0';
    local_10.sa_data[9] = '\0';
    local_10.sa_data[10] = '\0';
    local_10.sa_data[0xb] = '\0';
    local_10.sa_data[0xc] = '\0';
    local_10.sa_data[0xd] = '\0';
    local_10.sa_family = 2;
    SUBFIELD(local_10.sa_data,2,undefined2) = SUB42(param_1,0);
    SUBFIELD(local_10.sa_data,4,undefined2) = SUB42((uint)param_1 >> 0x10,0);
    SUBFIELD(local_10.sa_data,0,undefined2) = htons(param_2);
    iVar1 = ConfigureAsyncSocket(unaff_EBX,&local_10);
    if (iVar1 == 0) {
      closesocket(s);
      return 0;
    }
    iVar2 = connect(s,&local_10,0x10);
    if ((iVar2 == -1) && (iVar2 = WSAGetLastError(), iVar2 != 0x2733)) {
      /* DROPPED-REG FIX 2026-08-28: orig 0x4fe682 `lea eax,[ebx+4]` - the
         raw list at manager+4 - with the node (the ConfigureAsyncSocket
         result) still in EDI from 0x4fe64b. */
      FUN_004ff720((int *)(unaff_EBX + 4),(int *)iVar1);
      return 0;
    }
  }
  return iVar1;
}

