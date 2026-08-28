/* ResolveHostAddress - 0x004fdd30 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_004fdd30).  Resolves a host string to an
 * address - inet_addr first, falling back to gethostbyname - and hands the
 * result to ConnectToHostPort.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


undefined4 ResolveHostAddress(undefined4 param_1,undefined4 param_2,char *regEax)

{
  char **ppcVar1;
  char *pcVar2;
  char *in_EAX = regEax;
  ulong uVar3;
  hostent *phVar4;
  char **ppcVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  
  uVar3 = inet_addr(in_EAX);
  if (uVar3 == 0xffffffff) {
    phVar4 = gethostbyname(in_EAX);
    if (phVar4 == (hostent *)0x0) {
      return 0;
    }
    ppcVar5 = phVar4->h_addr_list;
    uVar8 = 0;
    pcVar2 = *ppcVar5;
    while (pcVar2 != (char *)0x0) {
      ppcVar1 = ppcVar5 + 1;
      ppcVar5 = ppcVar5 + 1;
      uVar8 = uVar8 + 1;
      pcVar2 = *ppcVar1;
    }
    uVar6 = FUN_00504e90();
    uVar3 = *(ulong *)phVar4->h_addr_list[uVar6 % uVar8];
  }
  /* DROPPED-REG FIX 2026-08-28: the manager for ConnectToHostPort's EBX
     is this function's own param_1 - `mov ebx,[esp+0x10]` at 0x4fdd79,
     one pending push deep, is entry+4 - the parameter the body never
     otherwise touches. */
  uVar7 = ConnectToHostPort(uVar3,param_2,(int)param_1);
  return uVar7;
}

