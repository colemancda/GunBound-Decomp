/* FUN_004fcd50 - 0x004fcd50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * RECOVERED (2026-07-19): byte-for-byte the same shape as FUN_004fcd20 but
 * calling DecodeCipherBlock (0x4f5e10) instead. Ghidra dropped the EAX block
 * count and the EDX SOURCE pointer, collapsing source and destination:
 *   0x4fcd52 mov ebp,[esp+0xc]   ; arg1 = SCHEDULE
 *   0x4fcd57 mov ebx,eax         ; EAX = block COUNT
 *   0x4fcd5c mov edi,ecx         ; ECX = DEST   (advances 0x10 @0x4fcd71)
 *   0x4fcd5e mov esi,edx         ; EDX = SOURCE (advances 0x10 @0x4fcd6e)
 *   loop: push ebp / push edi / mov edx,esi / call 0x4f5e10
 */
#include "ghidra_types.h"


void __thiscall FUN_004fcd50(int param_1,int schedule,uint *source,int count)

{
  if (0 < count) {
    do {
      DecodeCipherBlock(0,source,(uint *)param_1,schedule);
      param_1 = param_1 + 0x10;
      source = source + 4;      /* 4 dwords = 0x10 bytes */
      count = count + -1;
    } while (count != 0);
  }
  return;
}
