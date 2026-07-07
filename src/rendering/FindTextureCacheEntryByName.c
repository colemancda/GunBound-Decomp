/* FindTextureCacheEntryByName - 0x004f4650 in the original binary.
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


byte * FindTextureCacheEntryByName(byte *param_1)

{
  byte bVar1;
  byte *pbVar2;
  int in_EAX;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  bool bVar6;
  
  pbVar2 = *(byte **)(in_EAX + 0x1b4);
  do {
    pbVar3 = param_1;
    pbVar5 = pbVar2;
    if (pbVar2 == (byte *)0x0) {
      return (byte *)0x0;
    }
    do {
      bVar1 = *pbVar3;
      bVar6 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_004f468e:
        iVar4 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
        goto LAB_004f4693;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar6 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_004f468e;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_004f4693:
    if (iVar4 == 0) {
      return pbVar2;
    }
    pbVar2 = *(byte **)(pbVar2 + 0x98);
  } while( true );
}

