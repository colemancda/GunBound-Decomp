/* FUN_004fcd20 - 0x004fcd20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * RECOVERED (2026-07-19): a plain ECB encrypt loop over `count` 16-byte
 * blocks. Ghidra dropped the EAX (block count) and - the real bug - the EDX
 * SOURCE pointer, collapsing source and destination onto param_1:
 *   0x4fcd22 mov ebp,[esp+0xc]   ; arg1 = SCHEDULE
 *   0x4fcd27 mov ebx,eax         ; EAX = block COUNT
 *   0x4fcd2c mov edi,ecx         ; ECX = DEST   (advances 0x10 @0x4fcd41)
 *   0x4fcd2e mov esi,edx         ; EDX = SOURCE (advances 0x10 @0x4fcd3e)
 *   loop: push ebp / push edi / mov edx,esi / call 0x4f4d10
 * i.e. EncodeCipherBlock(dead ECX, source in EDX, dest, schedule) per block.
 */
#include "ghidra_types.h"


void __thiscall FUN_004fcd20(int param_1,int schedule,uint *source,int count)

{
  if (0 < count) {
    do {
      EncodeCipherBlock(0,source,(uint *)param_1,schedule);
      param_1 = param_1 + 0x10;
      source = source + 4;      /* 4 dwords = 0x10 bytes */
      count = count + -1;
    } while (count != 0);
  }
  return;
}
