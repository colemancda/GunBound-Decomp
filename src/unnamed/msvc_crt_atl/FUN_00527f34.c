/* FUN_00527f34 - 0x00527f34 in the original binary.
 *
 * CRT sqrt: `lea edx,[esp+4] / call __fload_withFB` loads the double
 * argument, then the body runs fsqrt at 0x527f5c. The decompiler showed it as a
 * void function that never returns (the loader is a register-convention
 * helper), which left every caller with an implicit int-returning
 * declaration; it is a plain double -> double function, result in ST0.
 */
#include "ghidra_types.h"
#include <math.h>

double FUN_00527f34(double x)

{
  return sqrt(x);
}
