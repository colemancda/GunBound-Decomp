/* BuildSystemInfoBlob - 0x0040d260 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* param_2 (the second output blob) arrives via a dropped ESI register in the
 * original - both call sites (WinMain.c) set up a SEPARATE local stack buffer
 * for it (esi = &local, distinct from param_1's own storage), not an offset
 * of param_1. Promoted to an explicit parameter; callers now pass their own
 * local buffer's address. */
void BuildSystemInfoBlob(undefined4 *param_1, undefined4 *param_2)

{
  undefined4 *unaff_ESI = param_2;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c [8];
  /* COALESCED (2026-07-18): the Rijndael key SCHEDULE is 0x20c bytes, not 520 -
   * RijndaelSetKey writes a 2-bit mode byte at ctx[0x82] (byte offset 0x208),
   * which Ghidra split off as a SEPARATE trailing local. Confirmed in the
   * original: BuildSystemInfoBlob does `mov byte [esp+0x264],0` with the
   * schedule at [esp+0x5c] - 0x264-0x5c = 0x208 exactly. With the buffer left
   * at 520 (=0x208) bytes that write lands one byte PAST it and corrupts the
   * stack (observed as a wild write killing the Logo2->Title transition once
   * the key expansion actually started running). Same split-struct class as
   * the SHA-1 context. */
  undefined1 local_20c [0x20c];
  
  local_20c[0x208] = 0;   /* the schedule's mode byte (ctx[0x82]) */
  /* RECOVERED (2026-07-18), orig 0x40d26f-0x40d2d6: the launcher-token key is
   * 16 bytes built byte-by-byte on the stack (Ghidra dropped those writes
   * entirely), passed as ECX with EDX=0x10 and EDI=[esp+0x5c] (= local_20c,
   * the schedule the DecodeCipherBlock calls below use). */
  {
    static const unsigned char kTokenKey[0x10] = {
      0xfa,0xee,0x85,0xf2,0x40,0x73,0xd9,0x16,
      0x13,0x90,0x19,0x7f,0x6e,0x56,0x2a,0x67
    };
    RijndaelSetKey((uint *)kTokenKey,0x10,2,(uint *)local_20c);
  }
  /* DecodeCipherBlock's 3 calls were missing param_2 (the ciphertext
   * source) entirely, and had their other 2 (now-visible) arguments
   * mispositioned relative to the real ABI (see DecodeCipherBlock.c's
   * header) - the existing args are param_3/output and param_4/ctx,
   * not param_1/param_2. Confirmed via objdump at 0x40d2e8/0x40d2fa/
   * 0x40d30c: EDX is the literal address 0x5b3440/0x5b3450/0x5b3460 -
   * three consecutive 16-byte AES blocks of the session-key buffer
   * DAT_005b3440 (see WinMain.c's sscanf into it). */
  DecodeCipherBlock(0,(uint *)&DAT_005b3440,&local_24c,(int)local_20c);
  DecodeCipherBlock(0,(uint *)(&DAT_005b3440 + 0x10),&local_23c,(int)local_20c);
  DecodeCipherBlock(0,(uint *)(&DAT_005b3440 + 0x20),local_22c,(int)local_20c);
  *param_1 = local_24c;
  param_1[1] = local_248;
  param_1[2] = local_244;
  param_1[3] = local_240;
  *(undefined1 *)(param_1 + 4) = 0;
  *unaff_ESI = local_23c;
  unaff_ESI[1] = local_238;
  unaff_ESI[2] = local_234;
  unaff_ESI[3] = local_230;
  unaff_ESI[4] = local_22c[0];
  *(undefined1 *)(unaff_ESI + 5) = 0;
  return;
}

