/* BlitRLESprite - 0x004eb450 in the original binary.
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


undefined4 __thiscall BlitRLESprite(int param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  byte *in_EAX;
  int iVar3;
  byte *pbVar4;
  int local_4;
  
  bVar1 = *in_EAX;
  if (bVar1 != 0) {
    local_4 = param_1 + 6;
    iVar3 = param_1 + 0xc;
    do {
      pbVar4 = in_EAX + 1;
      if ((char)bVar1 < '\0') {
        bVar2 = *pbVar4;
        pbVar4 = in_EAX + 2;
        if (DAT_00793530 <= iVar3) {
          FUN_004eaeb0(param_1,param_3,&DAT_005b3628 + ((bVar1 & 0x7f) << 8 | (uint)bVar2) * 0x18);
        }
        param_1 = param_1 + 0xc;
        iVar3 = iVar3 + 0xc;
        local_4 = local_4 + 0xc;
      }
      else {
        if ((bVar1 != 0x20) && (DAT_00793530 <= local_4)) {
          FUN_004eafa0(param_1,param_3);
        }
        param_1 = param_1 + 6;
        iVar3 = iVar3 + 6;
        local_4 = local_4 + 6;
      }
    } while ((param_1 <= DAT_0056df30) && (bVar1 = *pbVar4, in_EAX = pbVar4, bVar1 != 0));
  }
  return;
}

