/* Mobile13_Construct - 0x0046cb60 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence: its only caller is CreateMobile's case 0xd, which operator_new's
 * the 0xd1d4-byte mobile and assigns this function's return value to the
 * object pointer; every other case inlines InitMobile plus its own vtable
 * store. The vtable it stores, 0x555e54, is the one Mobile13_Destructor
 * (the next function in the image, 0x46cba0) and Mobile13_ScalarDtor
 * identify as type 13's (see the vtable census), so this is the type-13
 * constructor. The extra +0xbff0 = 2 store is the m_type13Field cell in
 * Mobile.h. It returns the object (mov eax,esi).
 *
 * CONSTRUCTOR BODY, ESI RECOVERED: regEsi is the object fresh from
 * operator_new, held by the caller in pvVar2 and passed explicitly now.
 *
 * regEax stays OPEN: it is InitMobile's second argument (the class id).
 * Its value at the sole call site loads a caller stack slot, and
 * CreateMobile contains an indirect switch jmp, which the esp model
 * refuses -- so the slot cannot be named without CFG-following.
 */
#include "ghidra_types.h"


undefined4 Mobile13_Construct(undefined4 *regEsi,undefined4 regEax)

{
  
  InitMobile(regEsi,regEax);
  *regEsi = &PTR_FUN_00555e54;
  regEsi[0x2ffc] = 2;
  /* The original ends `mov eax, esi / ret`: it returns the object it just
   * initialised.  The port returned 0 while regEsi was an unnamed dropped
   * register; the caller assigns this result to its object pointer, so
   * returning 0 nulled the freshly constructed object.  Same class of fix as
   * AppendToEncodedSocketBuffer's return. */
  return (undefined4)regEsi;
}

