/* FUN_00527d50 - 0x00527d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Multiple Matches With Different Base Names
    _acos
    _asin
    _atan
    _cos
     8 names - too many to list
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

double __cdecl FID_conflict__cos(double _X)

{
  ushort in_FPUControlWord;
  float10 fVar1;
  
  if ((DAT_00f2830c != 0) && ((MXCSR & 0x1f80) == 0x1f80 && (in_FPUControlWord & 0x7f) == 0x7f)) {
    fVar1 = (float10)FUN_005300e8();
    return (double)fVar1;
  }
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}

