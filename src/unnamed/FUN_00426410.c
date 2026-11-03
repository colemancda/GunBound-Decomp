/* FUN_00426410 - 0x00426410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
  *
 * FIX (2026-11-03): the GetNilString result was dropped (EAX folded away),
 * so `iVar1 + 0x10` stored an uninitialised local.  0x426410 is the CString
 * default constructor the CPanel base ctor runs over its 16 slots at +0x50
 * (_eh_vector_constructor_iterator_ with 0x426410/0x405320, 0x5057a5-
 * 0x5057c1): `mov eax,[0x5b1444] / call [eax+0xc]` (GetNilString, which
 * AddRefs the nil string and returns its data header) then
 * `add eax,0x10 / mov [esi],eax` (0x426420-0x426423).
 */
#include "ghidra_types.h"


int * __fastcall FUN_00426410(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(DAT_005b1444 + 0xc))();
  *param_1 = iVar1 + 0x10;
  return param_1;
}

