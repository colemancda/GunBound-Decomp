/* ResolveHostToIPv4Addr - 0x004e5480 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): its sole caller ConnectSocketToTarget
 * passes the hostname at conn+0x28 and stores the result into the sockaddr
 * address field it gives connect, with 0xffffffff (INADDR_NONE) as the
 * failure value, so the return is an IPv4 address in network byte order.
 * Behaviour: empty or dot-terminated strings fail, strings made only of
 * digits and dots go through inet_addr, anything else through
 * gethostbyname and the first address.
 *
 * Not ResolveHostAddress (0x4fdd30): that one tries inet_addr first, then
 * picks a RANDOM entry of the h_addr_list and hands the result straight to
 * ConnectToHostPort. This one only resolves. The proposed name
 * ResolveHostAddressChecked was not used because its qualifier implies a
 * contrast with ResolveHostAddress that is not the actual difference
 * (connect-and-pick-random versus resolve-only).
 */
#include "ghidra_types.h"


ulong __fastcall ResolveHostToIPv4Addr(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  ulong uVar4;
  hostent *phVar5;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = (int)pcVar2 - (int)(param_2 + 1);
  if ((iVar3 != 0) && (param_2[iVar3 + -1] != '.')) {
    do {
      iVar3 = iVar3 + -1;
      if ((iVar3 < 0) || (cVar1 = param_2[iVar3], cVar1 == '.')) {
        uVar4 = inet_addr(param_2);
        return uVar4;
      }
    } while (('/' < cVar1) && (cVar1 < ':'));
    phVar5 = gethostbyname(param_2);
    if (phVar5 != (hostent *)0x0) {
      return *(ulong *)*phVar5->h_addr_list;
    }
  }
  return 0xffffffff;
}

