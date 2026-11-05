/* LocalizedStrings_Construct - 0x0040d160 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040d160 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: its only
 * caller is the CRT dynamic-initializer stub at 0x540ee0, which does mov
 * esi,0x796eec / call 0x40d160 / push 0x5432e0 / call _atexit. 0x796eec is
 * g_localizedStringTable, the map GetLocalizedString, ShowErrorDialog and
 * LocalizedStrings_SetAt use, so this is the constructor of that map, and
 * 0x5432e0 (chain to 0x40d170 and then 0x4154e0) is its registered
 * destructor. The body forwards to LocalizedStrings_InitHeader with EDX =
 * 10 and returns this.
 *
 * CONSTRUCTOR of the localized-string map object (2026-08-25, workflow-
 * analysed).  The whole body is `mov edx,0xa / mov eax,esi / call
 * FUN_004154c0 / mov eax,esi / ret`: ESI is `this`, forwarded to
 * FUN_004154c0 in EAX with EDX = 10 (ECX a phantom there), and returned.
 * Its only caller is an unported CRT dynamic-initializer stub at 0x540ee0
 * (`push esi / mov esi,0x796eec / call / push 0x5432e0 / call _atexit`)
 * constructing &g_localizedStringTable and registering the matching
 * destructor thunk -- so there is no source call site to fix, only this
 * signature.  It now returns the object, as the original does.
 */
#include "ghidra_types.h"


undefined4 * LocalizedStrings_Construct(undefined4 *regEsi)

{
  FUN_004154c0(0,10,regEsi);
  return regEsi;
}

