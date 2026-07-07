/* FUN_00524130 - 0x00524130 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __fastcall FUN_00524130(undefined4 param_1)

{
  _SYSTEMTIME local_10;
  
  GetLocalTime(&local_10);
  DAT_005b162c = (local_10._6_4_ & 0xffff) * (uint)local_10.wMonth * (uint)local_10.wYear ^ 0xdad53a
  ;
  return param_1;
}

