/* IsNearZero - 0x004e9490 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the callers MultiplyMatrix4x4InPlace and
 * MultiplyMatrix4x4ToScratch test whether the right-hand matrix is affine
 * by checking that its fourth column is (0, 0, 0, 1): cells [0xb], [0xf] -
 * 1 and [3] are compared inline against the epsilon at 0x54c870, and cell
 * [7] goes through this function, which is the same test out of line (|x|
 * < 1e-5; 0x54c870 holds the float 0x3727c5ac = 1e-5, the epsilon
 * InvertAffineMatrix4x4 also uses). A zero test with an epsilon is what
 * the callers need there.
 *
 * Argument type: the binary loads its argument with fld DWORD PTR [esp+4],
 * a 4-byte float, although the port declares a double. Not changed here.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 IsNearZero(double param_1)

{
  if (ABS(param_1) < _DAT_0054c870) {
    return 1;
  }
  return 0;
}

