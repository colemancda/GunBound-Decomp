/* FUN_00502500 - 0x00502500 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FRAME WRITER for the CBuddy2 messenger connection.  Gates on the session
 * flag [EBX+0x1a70] and the connection pointer [EBX+0x1a74], stamps the
 * keepalive clock [EBX+0x1abc] = time(0), and queues one wire frame on the
 * connection through FUN_00503840 (the send()/WSAEWOULDBLOCK queue loop,
 * ECX=length, EDX=frame, stack=connection).  See SendBuddyNameMessage.c's
 * header for the surrounding CBuddy2 map.
 *
 * DROPPED REGISTERS + DEAD-CODED HEADER RECOVERED (2026-09-01).  The raw
 * port declared the stack opcode as `int unaff_EBX`, dropped EBX (the
 * session/engine), copied the payload directly into a headerless buffer, and
 * called FUN_00503840 with a single argument.  Rebuilt faithfully from
 * 0x502500-0x50257f:
 *   - ECX (param_1) = payload length, EDX (param_2) = payload buffer, both
 *     already named by Ghidra.
 *   - [ebp+8] (opcode, ret 4) is the REAL stack parameter, not EBX; promoted
 *     to `ushort opcode`.
 *   - EBX is the session/engine base; promoted to the trailing `int regEbx`
 *     per repo convention.  Reads: +0x1a70 live flag (0x502510), +0x1a74
 *     connection pointer (0x50251c), +0x1abc keepalive clock (0x502561).
 *   - THE DEAD-CODED FRAME HEADER: 0x502534 `mov word[esp+0x10],ax` stores
 *     len+4 (the total frame size, dword at [esp+0xc]) as frame word 0, and
 *     0x502539/0x50253d `mov ax,[ebp+8] / mov word[esp+0x12],ax` stores the
 *     opcode as frame word 1; the payload copy (rep movsd/movsb) targets
 *     [esp+0x14].  So the frame is one contiguous buffer
 *     [len+4:u16][opcode:u16][payload], modeled here as a single `frame[]`
 *     (MSVC will not guarantee adjacency of separate locals).
 *   - THE SEND: 0x50255d `mov ecx,[esp+0x10]` reloads the len+4 DWORD (saved
 *     at [esp+0xc] before the copy loops corrupt ECX), 0x502571 `lea edx,
 *     [esp+0x14]` is &frame, 0x502567 `mov eax,[ebx+0x1a74]` is the
 *     connection; captured as `frameLen` before the loops so it survives.
 * All 12 call sites had bound the packet opcode into the ECX/length slot;
 * they are corrected alongside this promotion (see promoted_arity_audit).
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint __fastcall FUN_00502500(uint param_1,undefined4 *param_2,ushort opcode,int regEbx)

{
  __time32_t _Var1;
  uint uVar2;
  uint frameLen;
  undefined4 *puVar3;
  undefined1 frame [0x1770];
  undefined4 uStack_c;

  uStack_c = 0x502510;
  uVar2 = CONCAT31(0x17,*(char *)(regEbx + 0x1a70));
  if ((*(char *)(regEbx + 0x1a70) != '\0') && (uVar2 = 0, *(int *)(regEbx + 0x1a74) != 0)) {
    frameLen = param_1 + 4;
    uVar2 = frameLen;
    if ((int)uVar2 < 0x1771) {
      *(ushort *)frame = (ushort)frameLen;
      *(ushort *)(frame + 2) = opcode;
      puVar3 = (undefined4 *)(frame + 4);
      for (uVar2 = param_1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      for (param_1 = param_1 & 3; param_1 != 0; param_1 = param_1 - 1) {
        *(undefined1 *)puVar3 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
      _Var1 = FID_conflict___time32((__time32_t *)0x0);
      *(__time32_t *)(regEbx + 0x1abc) = _Var1;
      uVar2 = FUN_00503840(frameLen,(char *)frame,*(int *)(regEbx + 0x1a74));
      return uVar2;
    }
  }
  return uVar2 & 0xffffff00;
}
