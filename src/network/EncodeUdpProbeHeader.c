/* EncodeUdpProbeHeader - 0x004e6d10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * (FUN_004e6160.c in the notes below is now
 * src/network/ProcessUdpProbeDatagram.c.)
 *
 * NAMED (2026-09-21), LIKELY. Zeroes a fixed 0x40-byte buffer (`param_2`),
 * writes a fixed length field `0x24` at its head, then fills it with a
 * per-connection sequence counter (`param_1+0x45204`, post-incremented)
 * and three fields copied straight from the connection context. Both
 * callers (FUN_004e6160.c, part of the same UDP subsystem as the named
 * BeginUdpSessionProbe.c / QueueBroadcastEvent.c) pass the freshly-built
 * buffer straight into SendUdpDatagram - i.e. this builds the header of
 * an outgoing UDP session-probe datagram. The exact bit-level meaning of
 * each field is not confirmed, hence LIKELY rather than CERTAIN.
 *
 * DROPPED-ARG / EAX-FIRST FIX (2026-09-21). Disasm 0x4e6d10-0x4e6d20 and
 * epilogue 0x4e6da4: ECX=param_1 (a context pointer, dereferenced at
 * +0x14c/+0x45204/+0x15d/+0x161/+0x165), EDX=param_2 (the output buffer,
 * written throughout), `ret 8` = 2 real stack args (param_3/param_4,
 * already correctly declared) - but EAX is ALSO a genuine incoming value
 * (Ghidra's `in_EAX`, never assigned before use), read as both a byte
 * stored at +6 and a slot index (`param_1 + (in_EAX*3+0xf)*8`). Promoted
 * to a real trailing parameter (`param_5`), same idiom as
 * InitTextBoxWidget/BlitSpriteAttached (6e574c4a). Both call sites
 * (FUN_004e6160.c) were missing param_1/param_2 entirely - see that
 * file's own header note.
 */
#include "ghidra_types.h"


void __fastcall EncodeUdpProbeHeader(int param_1,undefined4 *param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 *puVar3;

  puVar3 = param_2;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)((int)param_2 + 2) = 0;
  *(undefined2 *)param_2 = 0x24;
  uVar1 = *(undefined1 *)(param_1 + 0x14c);
  *(undefined1 *)((int)param_2 + 7) = 0;
  *(undefined1 *)((int)param_2 + 5) = uVar1;
  *(char *)((int)param_2 + 6) = (char)param_5;
  *(undefined1 *)(param_2 + 2) = *(undefined1 *)(param_1 + 0x45204);
  *(char *)(param_1 + 0x45204) = *(char *)(param_1 + 0x45204) + '\x01';
  *(undefined4 *)((int)param_2 + 9) = *(undefined4 *)(param_1 + 0x15d);
  *(undefined4 *)((int)param_2 + 0xd) = *(undefined4 *)(param_1 + 0x161);
  *(undefined4 *)((int)param_2 + 0x11) = *(undefined4 *)(param_1 + 0x165);
  puVar3 = (undefined4 *)(param_1 + (param_5 * 3 + 0xf) * 8);
  *(undefined4 *)((int)param_2 + 0x15) = *puVar3;
  *(undefined4 *)((int)param_2 + 0x19) = puVar3[1];
  *(undefined4 *)((int)param_2 + 0x1d) = puVar3[2];
  *(undefined2 *)((int)param_2 + 0x21) = param_3;
  *(char *)((int)param_2 + 0x23) = param_4;
  *(char *)(param_2 + 1) =
       *(char *)((int)param_2 + 0x22) + *(char *)(param_2 + 2) + param_4 +
       *(char *)((int)param_2 + 0x21) + -0x34;
  return;
}

