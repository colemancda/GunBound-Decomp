/* FUN_004f72b0 - 0x004f72b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * RECOVERED (2026-07-19): the decode twin of FUN_004f7210 - it consumes
 * 16-byte cipher blocks and emits 12 plaintext bytes each, checking the
 * 4-byte tag against *(int *)(schedule + 0x20c). Ghidra dropped the EAX
 * register arg (the ciphertext byte count) and, at every call site, the ECX
 * one (the output pointer); it also failed to advance the input pointer.
 *   0x4f72b4 mov ebx,ecx         ; ECX = OUTPUT (param_1, advances 0xc @0x4f7341)
 *   0x4f72b6 mov ecx,eax         ; EAX = INPUTLEN (tested & 0x8000000f for a
 *                                ;   multiple of 16, then >>4 = block count)
 *   0x4f72bf mov ebp,[esp+0x20]  ; arg2 = param_3 = INPUT (advances 0x10 @0x4f733e)
 *   0x4f7300 mov eax,[esp+0x24]  ; arg1 = param_2 = key SCHEDULE
 *   0x4f72dd mov eax,[esp+0x28]  ; arg3 = param_4 = CAPACITY (vs blocks*0xc)
 * The DecodeCipherBlock call at 0x4f7300-0x4f730c is
 *   push eax(schedule) / lea ecx,[esp+0x14] / push ecx(out block)
 *   mov edx,ebp(input) / call 0x4f5e10
 * i.e. (dead ECX, source in EDX, output, schedule). The port passed only
 * (&local_10, schedule) as ECX/EDX, so the ciphertext pointer never arrived.
 */
#include "ghidra_types.h"


undefined4 __thiscall
FUN_004f72b0(undefined4 *param_1,int param_2,int param_3,int param_4,uint inputLen)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  /* COALESCED (2026-07-19): Ghidra's local_10/local_c/local_8/local_4 are the
   * ONE contiguous 16-byte plaintext block DecodeCipherBlock writes (the
   * original passes &[esp+0x10] and then reads +0x0/+0x4/+0x8/+0xc back at
   * 0x4f731e-0x4f7336). MSVC scatters separate locals, so they must be a
   * single array - same split-struct class as the SHA-1 context in
   * EncodeHandshakeBlock.c. */
  undefined4 outBlk [4];

  uVar2 = inputLen & 0x8000000f;
  bVar5 = uVar2 == 0;
  if ((int)uVar2 < 0) {
    bVar5 = (uVar2 - 1 | 0xfffffff0) == 0xffffffff;
  }
  if (!bVar5) {
    return 0;
  }
  iVar3 = (int)(inputLen + ((int)inputLen >> 0x1f & 0xfU)) >> 4;
  if (param_4 < iVar3 * 0xc) {
    return 0;
  }
  if (0 < iVar3) {
    iVar4 = 0;
    do {
      sVar1 = (short)DecodeCipherBlock(0,(uint *)param_3,(uint *)outBlk,param_2);
      if ((sVar1 != 1) || ((int)outBlk[0] != *(int *)(param_2 + 0x20c))) {
        return 0;
      }
      *param_1 = outBlk[1];
      iVar4 = iVar4 + 1;
      param_1[1] = outBlk[2];
      param_1[2] = outBlk[3];
      param_1 = param_1 + 3;
      param_3 = param_3 + 0x10;   /* orig 0x4f733e: add ebp,0x10 */
    } while (iVar4 < iVar3);
  }
  return 1;
}
