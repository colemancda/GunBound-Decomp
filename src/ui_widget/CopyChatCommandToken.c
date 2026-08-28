/* CopyChatCommandToken - 0x00421870 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ARGUMENTS RE-SLOTTED AND EBX RECOVERED (2026-08-27).  All six call sites
 * passed NOTHING to this two-parameter __fastcall, so param_1 and param_2
 * were reading stale ECX/EDX and unaff_EBX was an uninitialised destination.
 *
 * Every site sets the same three registers in the same order: `lea ebx,
 * [esp+0x94 or 0x114]`, `mov ecx,1` (twice via edi/esi), `lea edx,
 * [esp+0x134]`.  So param_1 is 1 and param_2 is one address at all six.
 *
 * The frame is anchored by this caller's own strcpy: the C writes through
 * `(int)local_ff + (-1 - (int)param_2)`, i.e. base E-0x100, and the binary's
 * matching `lea edx,[esp+0x12c]` fixes esp at E-0x22c.  That makes the call
 * sites' [esp+0x134] E-0xf8 -- eight bytes into the length-prefixed command
 * buffer whose length byte is local_100 -- and [esp+0x94] / [esp+0x114]
 * E-0x198 / E-0x118, which land INSIDE local_1a0[116] and local_120[32] at
 * offset 8 rather than on any declared local of their own.
 *
 * Only one of the six writes to the local_120 buffer, and the source names it
 * without any ordering assumption: that site is followed by `_atol(local_120)`
 * while the other five sit beside local_1a0 uses -- matching the single
 * * binary site that uses `lea ebx,[esp+0x114]` instead of `+0x94`.
 *
 * Reads the token at `param_1` (0-based) out of the packed
 * length-prefixed token chain at `param_2`, copies its bytes to
 * `regEbx` and NUL-terminates.  ECX/EDX/EBX in, nothing out: a same-TU
 * static of ParseChatSlashCommand (0x4218c0), its only caller, six
 * times.
 *
 * The chain is built in place by FUN_00421820 (0x421820), which
 * overwrites the leading '/' and every separating space with the
 * length of the token that follows -- "/kick someone" becomes
 * [4]"kick"[7]"someone" -- and returns the token count.  The caller
 * uses that count as an argc: `!= 1` means "no arguments", `== 2`
 * means "exactly one", and the two loop sites (0x421d50, 0x421f20)
 * run the index from 1 to count-1.  So index 0 is the command word
 * and every call here asks for one of its arguments.
 *
 * Index 0 is done INLINE by the caller at 0x421963-0x42199c -- same
 * clamped length byte, same rep movsd + rep movsb, same NUL at
 * dst[len] -- copying token 0 into local_220, which is then the
 * subject of every command-word __stricmp: "h" (0x5535f0), "help"
 * (0x5535e8), "guide" (0x5535e0), "to" (0x5535dc), "message"
 * (0x5535d0), "m" (0x5535cc), "kick" (0x5535c4), "key" (0x5535c0),
 * "quit" (0x5535b8), "exit" (0x5535b0), "go" (0x5535ac), "mute"
 * (0x5535a4), "mutelist" (0x553598), "loud" (0x553588), and a long
 * tail of dev commands running down to 0x552cbc.  That inline twin is
 * what fixes the index space.
 *
 * Where the extracted token lands, per site.  0x422e82 compares it
 * with the local nickname at g_clientContext+0x23330, then hands it to
 * FUN_00402720 as a whisper target along with the rest of the line
 * (the message text's offset comes from an inlined copy of this
 * function's own walk at 0x422e60).  That path resolves the target
 * with GB_OP_USER_REQUEST 0x1020 when it is not already cached and
 * routes the text itself; it never writes 0x5100
 * GB_OP_CLIENT_COMMAND, which belongs to the unrecognised-command
 * branch -- that one forwards the whole raw line and never calls here.
 * 0x421aa7 searches the room's eight 0xd-stride roster names at
 * g_clientContext+0x457f1 and stores the matching slot index as the
 * one payload byte of GB_OP_ROOM_KICK_USER_REQUEST 0x3150 -- the
 * single UInt8 playerID of the server's RoomKickUserRequest.  0x421d50
 * ("mute", 0x5535a4) and 0x421f20 ("loud", 0x553588) length-check it
 * at <= 12 and hand it to FUN_00425840 / FUN_004258e0: the first
 * stricmps it against that same nickname and then adds it with
 * AppendWordFilterEntry, the second drops the matching entry with
 * AtlArray_RemoveAt_CString.  0x421bc6 and 0x422c76 push it through
 * _atol: a room-list page for 0x2100, and the primary/secondary Mobile
 * bytes of GB_OP_ROOM_SELECT_TANK_REQUEST 0x3200.
 *
 * FRAME (supersedes the note previously here, which was 8 bytes late):
 * ParseChatSlashCommand's esp sits 0x234 below its return-address slot
 * once `push ebp` (0x421953) and `push edi` (0x421977) join the
 * prologue's `sub esp,0x224` + push ebx + push esi.  So the uniform
 * `lea edx,[esp+0x134]` at all six sites is &local_100 exactly,
 * `lea ebx,[esp+0x94]` is local_1a0 and `[esp+0x114]` is local_120.
 * Cross-checked by the caller's own inlined walk at 0x422e61,
 * `movsx edx,[esp+esi+0x134]`, which the C already writes against
 * `(int)local_ff + iVar3 + -1` -- i.e. &local_100.
 *
 * STILL WRONG IN THE PORT, AT ALL SIX SITES: ParseChatSlashCommand.c
 * passes `(int)&local_100 + 8` and `local_1a0 + 8` / `local_120 + 8`,
 * so the walk starts in the middle of a token and the copy lands eight
 * bytes past the buffer the caller then reads back.  Two of the six
 * are wrong twice over: 0x421d50 and 0x421f20 take the index from a
 * loop counter (`mov ecx,edi` / `mov ecx,esi`, running 1..count-1),
 * not the constant 1 the C passes at both loop sites, so "/mute a b c"
 * re-fetches "a" three times.
 *
 * Faithful quirk, not a port bug: the terminator offset at 0x4218aa is
 * re-read with movsx and is NOT clamped, so a length byte >= 0x80
 * copies nothing but writes the NUL below dst.  The inline twin at
 * 0x42198f does the same; leave it.
 */
#include "ghidra_types.h"


void __fastcall CopyChatCommandToken(int param_1,int param_2,undefined4 *regEbx)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *unaff_EBX = regEbx;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    iVar1 = iVar1 + 1 + (int)*(char *)(iVar1 + param_2);
  }
  if (unaff_EBX != (undefined4 *)0x0) {
    if (*(char *)(iVar1 + param_2) < '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = (uint)*(char *)(iVar1 + param_2);
    }
    puVar4 = (undefined4 *)(iVar1 + 1 + param_2);
    puVar5 = unaff_EBX;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    *(undefined1 *)((int)*(char *)(iVar1 + param_2) + (int)unaff_EBX) = 0;
  }
  return;
}

