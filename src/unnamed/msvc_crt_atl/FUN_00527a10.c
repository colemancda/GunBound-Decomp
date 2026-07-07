/* FUN_00527a10 - 0x00527a10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _pow
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

double __cdecl _pow(double _X,double _Y)

{
  ushort in_FPUControlWord;
  float10 fVar1;
  
  if ((DAT_00f2830c != 0) && ((MXCSR & 0x1f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    fVar1 = (float10)FUN_0052edf9();
    return (double)fVar1;
  }
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}

