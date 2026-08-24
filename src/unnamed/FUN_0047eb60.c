/* FUN_0047eb60 - 0x0047eb60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CONSTRUCTOR BODY, ESI RECOVERED: regEsi is the object fresh from
 * operator_new, held by the caller in local_8bc and passed explicitly now.
 */
#include "ghidra_types.h"


undefined4 FUN_0047eb60(undefined4 *regEsi)

{
  
  InitProjectile(regEsi,0x186a2);
  regEsi[0xfe7] = 0;
  regEsi[0x1028] = 0;
  *regEsi = &PTR_FUN_005560d0;
  /* The original ends `mov eax, esi / ret`: it returns the object it just
   * initialised.  The port returned 0 while regEsi was an unnamed dropped
   * register; the caller assigns this result to its object pointer, so
   * returning 0 nulled the freshly constructed object.  Same class of fix as
   * AppendToEncodedSocketBuffer's return. */
  return (undefined4)regEsi;
}

