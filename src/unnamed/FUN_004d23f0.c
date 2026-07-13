/* FUN_004d23f0 - 0x004d23f0 in the original binary.
 *
 * Resolves the local hostname's IP address list into a connection
 * object's address array (gethostname + gethostbyname), used to populate
 * the client's own address info for one of the 3 connection objects
 * WinMain constructs at startup.
 *
 * FIXED (2026-07-13): `unaff_EDI` is a dropped register, not garbage -
 * confirmed via objdump that it's used with no prior write (`mov
 * [edi+4],esi` etc, no `mov edi,...` anywhere in the function body). All
 * 3 call sites (src/entry/WinMain.c) set EDI to that connection's own
 * object pointer (`DAT_005b2b58`/`DAT_005b2b5c`/`DAT_005b2b60`)
 * immediately before the call - a genuinely varying per-call argument,
 * not a fixed global. Promoted to an explicit parameter; all 3 callers
 * updated.
 */
#include "ghidra_types.h"


void FUN_004d23f0(int *conn)

{
  int iVar1;
  hostent *phVar2;
  char *pcVar3;
  int iVar4;
  int *unaff_EDI = conn;
  char local_80 [128];
  
  iVar4 = 0;
  iVar1 = gethostname(local_80,0x80);
  if (iVar1 != -1) {
    phVar2 = gethostbyname(local_80);
    if ((phVar2 != (hostent *)0x0) && (*phVar2->h_addr_list != (char *)0x0)) {
      pcVar3 = (char *)((int)unaff_EDI + 5);
      do {
        pcVar3[-1] = *phVar2->h_addr_list[iVar4];
        *pcVar3 = phVar2->h_addr_list[iVar4][1];
        pcVar3[1] = phVar2->h_addr_list[iVar4][2];
        pcVar3[2] = phVar2->h_addr_list[iVar4][3];
        iVar1 = iVar4 + 1;
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 4;
      } while (phVar2->h_addr_list[iVar1] != (char *)0x0);
    }
    *unaff_EDI = iVar4;
    return;
  }
  unaff_EDI[1] = 0;
  *unaff_EDI = 0;
  return;
}

