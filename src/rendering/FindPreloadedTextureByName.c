/* FindPreloadedTextureByName - 0x004017d0 in the original binary.
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


int * FindPreloadedTextureByName(char *param_1)

{
  int iVar1;
  int *unaff_EBX;
  int iVar2;
  int *_Str2;
  
  iVar2 = 0;
  if (0 < *unaff_EBX) {
    _Str2 = unaff_EBX + 1;
    do {
      iVar1 = __stricmp(param_1,(char *)_Str2);
      if (iVar1 == 0) {
        return unaff_EBX + iVar2 * 6 + 0x8001;
      }
      iVar2 = iVar2 + 1;
      _Str2 = _Str2 + 0x20;
    } while (iVar2 < *unaff_EBX);
  }
  return (int *)0x0;
}

