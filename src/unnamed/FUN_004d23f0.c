/* FUN_004d23f0 - 0x004d23f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004d23f0(void)

{
  int iVar1;
  hostent *phVar2;
  char *pcVar3;
  int iVar4;
  int *unaff_EDI;
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

