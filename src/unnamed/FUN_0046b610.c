/* FUN_0046b610 - 0x0046b610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0046b610(int *param_1)

{
  (**(code **)(*param_1 + 0x18))();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x46b62c
   * (`lea edi,[esi+0x1c2c]`, esi = param_1 per `mov esi,ecx` at function
   * entry, confirmed by objdump of orig/GunBound.gme). param_1 is `int *`
   * (scales by 4), so the byte offset is taken via `(int)param_1 +
   * 0x1c2c`. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x1c2c, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  AdvanceSpriteAnimation((int)param_1);
  return;
}

