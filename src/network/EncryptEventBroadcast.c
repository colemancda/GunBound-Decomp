/* EncryptEventBroadcast - 0x004e6df0 in the original binary.
 *
 * Seals one outgoing UDP battle/replay event: stamps the event header bytes
 * into the key block at 0x56dc90, checksums the event body, expands that key
 * into the schedule at ctx+0x44ff8, then encrypts the body in place 16 bytes
 * at a time back into ctx+0x44e0d.
 *
 * RECOVERED (2026-07-19): `ctx` arrives in EBX - a dropped register argument
 * Ghidra emitted as an uninitialised `int unaff_EBX`, so EVERY field access in
 * this function read garbage. The very first instruction of the original,
 * 0x4e6df0 `mov al, byte ptr [ebx + 0x44df4]`, reads EBX before anything
 * writes it, so it is genuinely incoming. Both call sites load it from their
 * own context register immediately before the call:
 *   0x4e6fc9  mov ebx, esi   / 0x4e6fcb  call 0x4e6df0   (BroadcastQueuedEvent)
 *   0x4e7144  mov ebx, esi   / 0x4e7146  call 0x4e6df0   (FUN_004e7140)
 * and in both, ESI was just set from EAX (`mov esi, eax` at 0x4e6fc6 and
 * 0x4e7142) - their own dropped-EAX context. Sweeping every call to those two
 * functions in the original shows that context is the global replay/event
 * struct: the overwhelming majority load it as an immediate, e.g. 0x4113a0
 * `mov eax, 0xe55ce0` before `call 0x4e6fc0`. 0xe55ce0 is g_replayContext, and
 * ctx+0x44ff8+0x210 (the end of the key schedule) is 0x45208 < its 0x454f9
 * size, so the schedule lives inside that global.
 *
 * RE-ENABLED (2026-07-19): the RijndaelSetKey call below had been NEUTRALISED
 * by an earlier session, because with `unaff_EBX` garbage a real key expansion
 * wrote ~0x210 bytes through a wild pointer (observed killing the Logo2->Title
 * transition). That was a symptom of the dropped EBX, which is now a real
 * parameter pointing into g_replayContext, so the call is restored. The key
 * block it reads also had to be un-split first - see g_eventKeyBlock in
 * globals.c: Ghidra had shattered the 16 contiguous bytes at 0x56dc90 into
 * separate one-byte globals AND lost their initialised contents.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


void EncryptEventBroadcast(int ctx)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_400 [256];

  DAT_0056dc97 = *(undefined1 *)(ctx + 0x44df4);
  DAT_0056dc95 = *(undefined1 *)(ctx + 0x44dee);
  DAT_0056dc9a = *(undefined1 *)(ctx + 0x44def);
  iVar3 = 0x21;
  cVar1 = *(char *)(ctx + 0x44dee) + *(char *)(ctx + 0x44def) +
          *(char *)(ctx + 0x44df4) + -0x34;
  if (0x21 < *(int *)(ctx + 0x44fec)) {
    do {
      cVar1 = cVar1 + *(char *)(ctx + 0x44dec + iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(ctx + 0x44fec));
  }
  *(char *)(ctx + 0x44df0) = cVar1;
  *(undefined1 *)(ctx + 0x44ff4) = 1;
  /* RECOVERED (2026-07-18) / RESTORED (2026-07-19), orig 0x4e6e4e-0x4e6e6d:
   *   0x4e6e4e  lea edi, [ebx + 0x44ff8]   <- ctx arg (the schedule)
   *   0x4e6e54  push 1                     <- mode arg
   *   0x4e6e56  mov edx, 0x10              <- key length, 16 CONTIGUOUS bytes
   *   0x4e6e5b  mov ecx, 0x56dc90          <- key base (g_eventKeyBlock+0)
   *   0x4e6e6d  call 0x4f48b0              <- RijndaelSetKey
   * The earlier session's "NOT ENABLED" note is resolved: EBX is a real
   * parameter now, and the key block is contiguous and correctly initialised
   * (g_eventKeyBlock), so both reasons for neutralising this are gone. */
  RijndaelSetKey((uint *)(g_eventKeyBlock + 0x00),0x10,1,(uint *)(ctx + 0x44ff8));
  iVar3 = *(int *)(ctx + 0x44fec) + -0x12;
  iVar5 = 0;
  if (0 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) {
    puVar4 = local_400;
    do {
      /* DROPPED ARGS (2026-07-19): the port passed only 2 of the 4 real
       * arguments and, critically, omitted the PLAINTEXT SOURCE entirely, so
       * it encrypted whatever was in the scratch buffer rather than the event
       * body. Orig 0x4e6e92-0x4e6ea2:
       *   0x4e6e92  lea edi, [ebx + 0x44e0d]   <- source, the event body
       *   0x4e6e98  lea eax, [ebx + 0x44ff8]   <- schedule
       *   0x4e6e9e  push eax                   <- 2nd stack arg = param_4/ctx
       *   0x4e6e9f  push ebp                   <- 1st stack arg = param_3/out
       *   0x4e6ea0  mov edx, edi               <- EDX = param_2/source
       *   0x4e6ea2  call 0x4f4d10              <- EncodeCipherBlock
       * ECX/param_1 is dead (see EncodeCipherBlock's own header). EDI (source)
       * and EBP (output) each advance 0x10 per iteration - 0x4e6ebd/0x4e6ec0. */
      EncodeCipherBlock(0,(uint *)(ctx + 0x44e0d + iVar5 * 0x10),(uint *)puVar4,
                        ctx + 0x44ff8);
      iVar3 = *(int *)(ctx + 0x44fec) + -0x12;
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar5 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4);
  }
  iVar3 = *(int *)(ctx + 0x44fec) + -0x12;
  uVar2 = ((int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) * 0x10;
  *(uint *)(ctx + 0x44fec) = uVar2 + 0x21;
  puVar4 = local_400;
  puVar6 = (undefined4 *)(ctx + 0x44e0d);
  for (uVar2 = (((int)uVar2 < 0) - 1 & uVar2) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  return;
}

