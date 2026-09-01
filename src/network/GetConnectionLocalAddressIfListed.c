/* GetConnectionLocalAddressIfListed - 0x00503930 in the original binary.
 *
 * The address-fetching sibling of GetConnectionSocketIfListed (0x503910,
 * the function immediately before this one): the identical
 * membership walk over the connection list at *(container+4) looking
 * for `param_1` itself, but instead of returning the node's SOCKET at
 * +8 it calls getsockname on it and writes the socket's LOCAL end out:
 * the 4-byte IPv4 address (sa_data[2..5]) through param_2 and the
 * 2-byte network-order port (sa_data[0..1]) through param_3.  Returns 1
 * on success, 0 when the node is unlisted, its socket is -1, or
 * getsockname fails.
 *
 * The one call site, 0x501be3 in FUN_00501770, passes the same
 * node/container pair as the sibling's site in the same function
 * (*(callerThis+0x1780) and callerThis-0x2f0) and uses the outputs on
 * the handshake path right next to an EncodeHandshakeBlock call and a
 * getsockname of the caller's own UDP socket - the block where the
 * client gathers its local endpoints.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall GetConnectionLocalAddressIfListed(undefined4 *param_1,char *param_2,char *param_3,int regEax)

{
  undefined4 *puVar1;
  int iVar2;
  int local_14;
  sockaddr local_10;
  
  puVar1 = *(undefined4 **)(regEax + 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if (param_1 == puVar1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  if (param_1[2] == 0xffffffff) {
    return 0;
  }
  local_14 = 0x10;
  iVar2 = getsockname(param_1[2],&local_10,&local_14);
  if (iVar2 == -1) {
    return 0;
  }
  *(undefined4 *)param_2 = SUBFIELD(local_10.sa_data,2,undefined4);
  *(undefined2 *)param_3 = SUBFIELD(local_10.sa_data,0,undefined2);
  return 1;
}

