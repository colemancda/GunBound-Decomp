/* FUN_004f7210 - 0x004f7210 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * RECOVERED (2026-07-19): this is EncodePacketBlocks (0x4f70b0) minus the
 * opcode addend - the P2P/broker variant, whose per-block tag is just
 * *(int *)(schedule + 0x20c). Ghidra dropped BOTH register args:
 *   0x4f7214 mov ebx,ecx        ; ECX = INPUT   (advances 0xc, 0x4f7284)
 *   0x4f7216 cdq / 0x4f721c idiv ecx(=0xc)
 *                               ; EAX = INPUTLEN (block count -> edi)
 * Stack args (esp adjusted for the pushes live at each site):
 *   0x4f7240 mov eax,[esp+0x20] ; arg1 = param_1 = key SCHEDULE
 *   0x4f7244 mov ecx,[eax+0x20c]; the per-connection sequence tag
 *   0x4f721f mov ebp,[esp+0x20] ; arg2 = param_2 = OUTPUT (advances 0x10)
 *   0x4f722a mov eax,[esp+0x28] ; arg3 = param_3 = CAPACITY
 * Per block the original stages [4-byte tag][12 input bytes] in a stack
 * scratch and hands it to EncodeCipherBlock with (dead ECX, plaintext in EDX,
 * output, schedule) - orig 0x4f7255-0x4f7275:
 *   mov edx,ebx / mov eax,[edx] / mov ecx,[edx+4] / mov edx,[edx+8]
 *   ... push eax(schedule) / push ebp(output) / lea edx,[esp+0x18](block)
 *   call 0x4f4d10
 * Before this fix both the input pointer and the schedule were missing, so
 * the call compiled to EncodeCipherBlock(output, schedule) - the schedule
 * never reached param_4 and nothing was ever read from the payload.
 */
#include "ghidra_types.h"


undefined4 FUN_004f7210(undefined4 param_1,int param_2,int param_3,byte *input,int inputLen)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint tag;
  /* COALESCED: the staged block MUST be one contiguous 16 bytes - the
   * original builds it in [esp+0x10..0x1f] and passes &[esp+0x10] as the
   * plaintext pointer. */
  uint blk [4];

  iVar2 = inputLen / 0xc;
  if ((inputLen % 0xc == 0) && (iVar2 * 0x10 <= param_3)) {
    /* hoisted exactly as the original does at 0x4f7244, outside the loop */
    tag = *(uint *)((int)param_1 + 0x20c);
    iVar3 = 0;
    if (0 < iVar2) {
      do {
        blk[0] = tag;
        blk[1] = *(uint *)input;
        blk[2] = *(uint *)(input + 4);
        blk[3] = *(uint *)(input + 8);
        sVar1 = (short)EncodeCipherBlock(0,blk,(uint *)param_2,(int)param_1);
        if (sVar1 != 1) {
          return 0;
        }
        iVar3 = iVar3 + 1;
        input = input + 0xc;
        param_2 = param_2 + 0x10;
      } while (iVar3 < iVar2);
    }
    return 1;
  }
  return 0;
}
