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
 * NOTE both inputs are still DROPPED at that call site (eax = container =
 * callerThis - 0x2f0, ecx = node = [callerThis + 0x1780]); recovering them is
 * pending, and needs this signature first.
 */
#include "ghidra_types.h"


undefined4 __fastcall GetConnectionSocketIfListed(undefined4 *param_1)

{
  undefined4 *puVar1;
  int in_EAX;
  
  puVar1 = *(undefined4 **)(in_EAX + 4);
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    if (param_1 == puVar1) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return param_1[2];
}

