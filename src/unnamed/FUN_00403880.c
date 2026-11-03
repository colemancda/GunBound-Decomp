/* FUN_00403880 - 0x00403880 in the original binary.
 *
 * CARVED (2026-11-03). Never carved by Ghidra: its only reference is the
 * .data word at 0x551cb8, SLOT 0 of the messenger's notify interface
 * 0x551cb8 (the table the messenger puts at +8, 0x401948). Extent
 * 0x403880-0x403884 (5 bytes, then int3 padding to 0x403890).
 *
 * `mov al,1 / ret 0x14`: __thiscall with FIVE stack words that it never
 * reads, always answering true. The one dispatch of this slot,
 * DispatchP2PMessage's `(**vtbl)(listener,p4,p5,p6,p2,p1)`, passes
 * exactly this + five. Left unnamed. Erased __thiscall: this first.
 */
#include "ghidra_types.h"


char FUN_00403880(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6)

{
  return 1;
}
