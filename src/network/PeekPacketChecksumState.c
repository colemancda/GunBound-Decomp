/* PeekPacketChecksumState - 0x0040a2e0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


uint PeekPacketChecksumState(void)

{
  uint uVar1;
  uint *in_EAX;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint local_10 [4];
  
  uVar1 = in_EAX[5];
  if (uVar1 != 0) {
    piVar2 = (int *)FUN_0040b8c0();
    if (*piVar2 != DAT_00793774) {
      DAT_00793514 = 1;
    }
  }
  iVar3 = 0;
  while( true ) {
    in_EAX = in_EAX + 1;
    uVar4 = *(uint *)(uVar1 * 0x10 + DAT_0079376c + iVar3 * 4) ^ *in_EAX;
    local_10[iVar3] = uVar4;
    if ((iVar3 != 0) && (local_10[0] != uVar4)) break;
    iVar3 = iVar3 + 1;
    if (3 < iVar3) {
      EncodeOutgoingPacketField(local_10[0]);
      return local_10[0];
    }
  }
  DAT_00793514 = 1;
  return 0;
}

