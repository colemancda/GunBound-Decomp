/* GetConnectionSocketIfListed - 0x00503910 in the original binary.
 *
 * Membership-checked socket lookup: walks the connection list at
 * *(container+4) looking for `node` itself, and returns *(node+8) -- the
 * SOCKET -- if the node is listed, else -1.
 *
 * Named from its one call site (FUN_00501770, 0x0050187d): the result is
 * passed straight to getpeername as the socket, with the name/namelen pair
 * the caller pushed beforehand.  The membership walk is the point of the
 * function -- a node that has been unlinked no longer yields its socket.
 *
 * Both inputs are now RECOVERED at that call site: the container arrives as
 * regEax = callerThis - 0x2f0 and the node as param_1 =
 * *(callerThis + 0x1780), read off `lea eax,[edi-0x2f0]` and
 * `mov ecx,[edi+0x1780]` at 0x0050186d-0x0050187d, where EDI holds
 * FUN_00501770's own entry ECX throughout.
 */
#include "ghidra_types.h"


undefined4 __fastcall GetConnectionSocketIfListed(undefined4 *param_1,int regEax)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(regEax + 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    if (param_1 == puVar1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return param_1[2];
}

