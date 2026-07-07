/* FUN_00530bc4 - 0x00530bc4 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __statfp
   
   Library: Visual Studio 2003 Release */

int __statfp(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}

