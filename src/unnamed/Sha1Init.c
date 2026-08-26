/* Sha1Init - 0x004f76c0 in the original binary.
 *
 * SHA-1 init: the five IV words 0x67452301 / 0xefcdab89 / 0x98badcfe /
 * 0x10325476 / 0xc3d2e1f0, then the two length words and the buffer index at
 * +0x5c.  The context arrives in EAX, which is why its one call site looked
 * argument-less; that site is three lines above the Sha1Absorb calls that
 * already name the same buffer (local_3128), so the register and the
 * existing SHA-1 functions agree on what it is.
 */
#include "ghidra_types.h"


void Sha1Init(undefined4 *regEax)

{
  
  *regEax = 0x67452301;
  regEax[1] = 0xefcdab89;
  regEax[2] = 0x98badcfe;
  regEax[3] = 0x10325476;
  regEax[4] = 0xc3d2e1f0;
  regEax[5] = 0;
  regEax[6] = 0;
  regEax[0x17] = 0;
  return;
}

