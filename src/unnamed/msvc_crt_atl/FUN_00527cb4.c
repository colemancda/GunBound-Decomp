/* FUN_00527cb4 - 0x00527cb4 in the original binary.
 *
 * CRT cos: `lea edx,[esp+4] / call __fload_withFB` loads the double
 * argument, then the body runs fcos at 0x527cd2. The decompiler showed it as a
 * void function that never returns (the loader is a register-convention
 * helper), which left every caller with an implicit int-returning
 * declaration; it is a plain double -> double function, result in ST0.
 */
#include "ghidra_types.h"
#include <math.h>

double FUN_00527cb4(double x)

{
  return cos(x);
}
