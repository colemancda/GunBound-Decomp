/* FUN_004e6f20 - 0x004e6f20 in the original binary.
 *
 * The decrypt counterpart of EncryptEventBroadcast: expands the SECOND event
 * key (0x56dca0, mode 2) into the same schedule slot at ctx+0x44ff8, then
 * decrypts param_1's body in place, 16 bytes at a time, via a 0x400 scratch.
 *
 * RECOVERED (2026-07-19): `ctx` arrives in EAX - a dropped register argument
 * Ghidra emitted as an uninitialised `int in_EAX`. It is read before any write
 * at 0x4e6f28 `mov edi, eax` (immediately turned into the schedule pointer by
 * 0x4e6f2a `add edi, 0x44ff8`), so it is genuinely incoming. Both call sites
 * load it from their own context immediately before the call:
 *   0x4e6373  mov eax, ebx / 0x4e6375  call 0x4e6f20  (FUN_004e6160, ebx = its
 *                                                      own param_1)
 *   0x4e7e9b  mov eax, ebp / 0x4e7ea3  call 0x4e6f20  (FUN_004e7de0, ebp = its
 *                                                      own param_1 - confirmed
 *                                                      by 0x4e7e88 `lea eax,
 *                                                      [ebp+0x452c2]`, which is
 *                                                      the buffer argument this
 *                                                      port already passes as
 *                                                      `param_1 + 0x452c2`)
 *
 * RE-ENABLED (2026-07-19): the RijndaelSetKey call below had been NEUTRALISED
 * for the same reason as EncryptEventBroadcast's - a real key expansion through
 * a garbage `in_EAX` corrupted memory. With EAX now a real parameter (and the
 * key block coalesced into g_eventKeyBlock, see globals.c) both reasons are
 * gone, so the call is restored.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output otherwise, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e6f20(undefined4 *param_1,uint param_2,int ctx)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_400 [256];
  
  /* RECOVERED / RESTORED (2026-07-19), orig 0x4e6f28-0x4e6f3c:
   *   0x4e6f28  mov edi, eax               <- ctx (dropped EAX arg)
   *   0x4e6f2a  add edi, 0x44ff8           <- ctx arg (the schedule)
   *   0x4e6f30  push 2                     <- mode arg (vs mode 1 when sealing)
   *   0x4e6f32  mov edx, 0x10              <- key length, 16 CONTIGUOUS bytes
   *   0x4e6f37  mov ecx, 0x56dca0          <- key base (g_eventKeyBlock+0x10)
   *   0x4e6f3c  call 0x4f48b0              <- RijndaelSetKey */
  RijndaelSetKey((uint *)(g_eventKeyBlock + 0x10),0x10,2,(uint *)(ctx + 0x44ff8));
  iVar1 = (int)(param_2 + ((int)param_2 >> 0x1f & 0xfU)) >> 4;
  if (0 < iVar1) {
    puVar3 = param_1;
    do {
      /* DROPPED ARGS (2026-07-19): the port passed only 2 of the 4 real
       * arguments, collapsing the output pointer into the first slot and
       * losing the ciphertext SOURCE. Orig 0x4e6f5a-0x4e6f77:
       *   0x4e6f5a  mov esi, [esp+0x40c]  <- param_1, the buffer
       *   0x4e6f62  lea ebx, [esp+0xc]    }  ebx = local_400 - param_1,
       *   0x4e6f67  sub ebx, esi          }  computed ONCE outside the loop
       *   0x4e6f70  lea eax, [ebx + esi]  <- the local_400 slice
       *   0x4e6f73  push edi              <- 2nd stack arg = param_4/ctx
       *   0x4e6f74  push eax              <- 1st stack arg = param_3/out
       *   0x4e6f75  mov edx, esi          <- EDX = param_2/ciphertext source
       *   0x4e6f77  call 0x4f5e10         <- DecodeCipherBlock
       * ECX/param_1 is dead (see DecodeCipherBlock's own header). */
      DecodeCipherBlock(0,puVar3,
                        (uint *)(((int)local_400 - (int)param_1) + (int)puVar3),
                        ctx + 0x44ff8);
      puVar3 = puVar3 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  param_2 = param_2 & ((int)param_2 < 0) - 1;
  puVar3 = local_400;
  for (uVar2 = param_2 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  for (param_2 = param_2 & 3; param_2 != 0; param_2 = param_2 - 1) {
    *(undefined1 *)param_1 = *(undefined1 *)puVar3;
    puVar3 = (undefined4 *)((int)puVar3 + 1);
    param_1 = (undefined4 *)((int)param_1 + 1);
  }
  return;
}

