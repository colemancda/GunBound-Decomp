/* FUN_005277bb - 0x005277bb in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _fast_error_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl fast_error_exit(int param_1)

{
  if (DAT_005b1760 == 1) {
    __FF_MSGBANNER();
  }
  __NMSG_WRITE(param_1);
                    /* WARNING: Subroutine does not return */
  ___crtExitProcess(0xff);
}

