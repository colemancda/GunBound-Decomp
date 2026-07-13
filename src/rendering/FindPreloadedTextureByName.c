/* FindPreloadedTextureByName - 0x004017d0 in the original binary.
 *
 * Ghidra emitted the texture-list base pointer as `unaff_EBX`, i.e. read
 * out of EBX without ever assigning it - a dropped-argument false
 * positive. Disassembly at every call site (e.g. 0x4060ad, 0x41243c,
 * 0x42b742, ...) shows the exact same sequence immediately before
 * `call 0x4017d0`:
 *     mov ebx, ds:0x5b3484   ; g_clientContext
 *     add ebx, 0x67ec70      ; + DAT_0067ec70
 * with the name string pushed separately as the real (only) stack
 * argument. So EBX isn't a per-call argument at all - it's the fixed
 * global `g_clientContext + DAT_0067ec70` (the preloaded-texture table
 * inside the client context arena, see globals.h), reloaded from the
 * global in every caller rather than passed in. Fixed by reading that
 * global directly instead of trusting the bogus `unaff_EBX` local.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise - not
 * hand-verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include "globals.h"
#include <windows.h>


int * FindPreloadedTextureByName(char *param_1)

{
  int iVar1;
  int *textureTable;
  int iVar2;
  int *_Str2;

  textureTable = (int *)(&DAT_0067ec70 + g_clientContext);
  iVar2 = 0;
  if (0 < *textureTable) {
    _Str2 = textureTable + 1;
    do {
      iVar1 = __stricmp(param_1,(char *)_Str2);
      if (iVar1 == 0) {
        return textureTable + iVar2 * 6 + 0x8001;
      }
      iVar2 = iVar2 + 1;
      _Str2 = _Str2 + 0x20;
    } while (iVar2 < *textureTable);
  }
  return (int *)0x0;
}

