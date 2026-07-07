/* FUN_00534983 - 0x00534983 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __frnd
   
   Library: Visual Studio 2003 Release */

float10 __frnd(double param_1)

{
  return (float10)ROUND(param_1);
}

