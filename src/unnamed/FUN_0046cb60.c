/* FUN_0046cb60 - 0x0046cb60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * CONSTRUCTOR BODY, ESI RECOVERED: regEsi is the object fresh from
 * operator_new, held by the caller in pvVar2 and passed explicitly now.
 *
 * in_EAX stays OPEN: it is InitMobile's second argument (the class id).
 * Its value at the sole call site loads a caller stack slot, and
 * CreateMobile contains an indirect switch jmp, which the esp model
 * refuses -- so the slot cannot be named without CFG-following.
 */
#include "ghidra_types.h"


undefined4 FUN_0046cb60(undefined4 *regEsi)

{
  undefined4 in_EAX;
  
  InitMobile(regEsi,in_EAX);
  *regEsi = &PTR_FUN_00555e54;
  regEsi[0x2ffc] = 2;
  /* The original ends `mov eax, esi / ret`: it returns the object it just
   * initialised.  The port returned 0 while regEsi was an unnamed dropped
   * register; the caller assigns this result to its object pointer, so
   * returning 0 nulled the freshly constructed object.  Same class of fix as
   * AppendToEncodedSocketBuffer's return. */
  return (undefined4)regEsi;
}

