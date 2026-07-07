/* FUN_005290fb - 0x005290fb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___sbh_heap_init
   
   Library: Visual Studio 2003 Release */

undefined4 ___sbh_heap_init(undefined4 param_1)

{
  DAT_00f29698 = HeapAlloc(DAT_00f296ac,0,0x140);
  if (DAT_00f29698 == (LPVOID)0x0) {
    return 0;
  }
  DAT_00f29690 = 0;
  DAT_00f29694 = 0;
  DAT_00f296a0 = DAT_00f29698;
  DAT_00f2969c = param_1;
  DAT_00f296a4 = 0x10;
  return 1;
}

