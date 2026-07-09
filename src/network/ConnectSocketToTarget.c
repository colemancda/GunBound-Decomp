/* ConnectSocketToTarget - 0x004e59b0 in the original binary.
 *
 * Worker-thread body of the actual connect. Creates a TCP socket
 * (AF_INET / SOCK_STREAM), builds a sockaddr_in from the stored target
 * port (conn+0x228, htons'd) and an address resolved by FUN_004e5480,
 * and calls connect(); on success sets the connected flag (conn+0x22a=1).
 * Returns that flag. Invoked from HandleSocketEvent's op 2.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 ConnectSocketToTarget(void)

{
  SOCKET SVar1;
  int iVar2;
  int unaff_ESI;
  sockaddr local_10;
  
  SVar1 = socket(2,1,0);
  *(SOCKET *)(unaff_ESI + 0x24) = SVar1;
  if (SVar1 != 0xffffffff) {
    local_10.sa_family = 2;
    SUBFIELD(local_10.sa_data,0,undefined2) = htons(*(u_short *)(unaff_ESI + 0x228));
    SUBFIELD(local_10.sa_data,2,undefined4) = FUN_004e5480();
    iVar2 = connect(*(SOCKET *)(unaff_ESI + 0x24),&local_10,0x10);
    if (iVar2 == 0) {
      *(undefined1 *)(unaff_ESI + 0x22a) = 1;
    }
  }
  return *(undefined1 *)(unaff_ESI + 0x22a);
}

