/* FUN_0052e33f - 0x0052e33f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 2003 Release */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_005b1760 == 1) || ((DAT_005b1760 == 0 && (DAT_0056bf74 == 1)))) {
    __NMSG_WRITE(0xfc);
    if (DAT_005b1a1c != (code *)0x0) {
      (*DAT_005b1a1c)();
    }
    __NMSG_WRITE(0xff);
  }
  return;
}

