/* FUN_0040d160 - 0x0040d160 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


undefined4 * FUN_0040d160(undefined4 *regEsi)

{
  FUN_004154c0(0,10,regEsi);
  return regEsi;
}

