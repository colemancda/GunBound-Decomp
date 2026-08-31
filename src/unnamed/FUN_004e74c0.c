/* FUN_004e74c0 - 0x004e74c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28), a RE-SLOT shifted left by two. The
 * three values both callers passed were real, but they are the three
 * STACK arguments (param_3/4/5); what belongs in the two register slots
 * is a word read from the caller's +0x4589c table (ECX = param_1) and
 * the replay context (EDX = param_2 = &g_replayContext, the literal
 * 0xe55ce0 at both sites). Two more registers were dropped outright:
 * EAX is the SLOT INDEX (guarded `in_EAX < 8`, and every field write
 * indexes by it) and EDI a value from the caller's +0x4585c table,
 * stored at +0x18+idx*4 and compared against param_3 - when
 * (EDI,param_1) equals (param_3,param_4) the record's param_3 field is
 * forced to -1, i.e. "same as self".
 *
 * The body registers slot idx into the g_replayContext-side table:
 * sets bit idx in +0x140 / clears it in +0x138, stores EDI at
 * +0x18+idx*4, param_1 at +0x58+idx*2, param_3 at +0x38+idx*4, param_4
 * at +0x68+idx*2, zeroes the three per-slot bytes at +0x3c0 / +0x3c8 /
 * +0x454e4, and copies the name into +0x78 + idx*0x18.
 *
 * Both sites read their values from the same per-slot arrays at
 * +0x4585c / +0x4587c / +0x4589c / +0x458ac off g_clientContext, and at
 * the WriteReplayEventRecord site the C had already reassigned its
 * index local local_d70 on the line before the call - the iVar12/iVar20
 * scaled copies kept the old value, so the cursor update now follows
 * the call, matching the binary's order.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e74c0(int param_1,int param_2,int param_3,int param_4,char *param_5,
                             uint regEax,int regEdi)

{
  uint *puVar1;
  char cVar2;
  uint in_EAX = regEax;
  int iVar3;
  uint uVar4;
  int unaff_EDI = regEdi;
  
  if ((int)in_EAX < 8) {
    if (7 < in_EAX) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    uVar4 = 1 << ((byte)in_EAX & 0x1f);
    iVar3 = (in_EAX >> 5) * 4;
    puVar1 = (uint *)(iVar3 + 0x140 + param_2);
    *puVar1 = *puVar1 | uVar4;
    puVar1 = (uint *)(iVar3 + 0x138 + param_2);
    *puVar1 = *puVar1 & ~uVar4;
    *(int *)(param_2 + 0x18 + in_EAX * 4) = unaff_EDI;
    *(short *)(param_2 + 0x58 + in_EAX * 2) = param_1;
    if ((unaff_EDI == param_3) && (param_1 == param_4)) {
      param_3 = -1;
    }
    *(int *)(param_2 + 0x38 + in_EAX * 4) = param_3;
    *(short *)(param_2 + 0x68 + in_EAX * 2) = param_4;
    *(undefined1 *)(in_EAX + 0x3c0 + param_2) = 0;
    *(undefined1 *)(in_EAX + 0x3c8 + param_2) = 0;
    *(undefined1 *)(in_EAX + 0x454e4 + param_2) = 0;
    iVar3 = (param_2 + (in_EAX * 3 + 0xf) * 8) - (int)param_5;
    do {
      cVar2 = *param_5;
      param_5[iVar3] = cVar2;
      param_5 = param_5 + 1;
    } while (cVar2 != '\0');
  }
  return;
}

