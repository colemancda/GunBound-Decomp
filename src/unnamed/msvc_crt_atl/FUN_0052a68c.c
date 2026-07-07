/* FUN_0052a68c - 0x0052a68c in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __freeptd
   
   Library: Visual Studio 2003 Release */

void __cdecl __freeptd(_ptiddata _Ptd)

{
  if (DAT_0056c230 != -1) {
    if (_Ptd == (_ptiddata)0x0) {
      _Ptd = (_ptiddata)(*DAT_005b1914)(DAT_0056c230);
    }
    __freefls_4(_Ptd);
    (*DAT_005b1918)(DAT_0056c230,0);
  }
  return;
}

