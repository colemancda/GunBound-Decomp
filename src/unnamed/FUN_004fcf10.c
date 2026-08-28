/* FUN_004fcf10 - 0x004fcf10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): EDI is the 16-bit CBuddy2 peer
 * MESSAGE TYPE (the 0xc0xx type space).  It is read before it is written
 * here: `push edi` at 0x4fcf2a supplies FUN_004fe110's third stack
 * argument, and `mov eax,edi` at 0x4fcf40 feeds FUN_004fd030, which is
 * `movzx eax,ax / add eax,0xffff3fef / cmp eax,0x32` into a jump table
 * returning a bool - a WORD-wide classifier over 0xc011..0xc043.  On the
 * server-relay branch the same value goes to FUN_00502650 in EDX and is
 * stamped into the outgoing frame as a word (`mov word ptr [esp+0x11],dx`
 * at 0x502695).  So it is the message type, matching the 0xc0xx
 * peer-message space described in SendBuddyNameMessage.c.
 *
 * All seven binary call sites set it with a `mov edi,<imm>` inside the
 * calling basic block, so each site's witness is the immediate itself and
 * no site needs pairing by position.  Call site first, then the mov that
 * loads EDI a few instructions earlier in the same block:
 * 0x4fd639   mov edi,0xc051 at 0x4fd62b   in FUN_004fd590     ported
 * 0x4fd7a9   mov edi,0xc041 at 0x4fd7a4   in FUN_004fd730     ported
 * 0x4fd7e7   mov edi,0xc042 at 0x4fd7e0   in FUN_004fd7c0     ported
 * 0x4fd555   mov edi,0xc018 at 0x4fd54f   in the fn 0x4fd510  unported
 * 0x4fd584   mov edi,0xc011 at 0x4fd57e   in the fn 0x4fd510  unported
 * 0x4fd670   mov edi,0xc053 at 0x4fd66b   in the fn 0x4fd650  unported
 * 0x4fd86f   mov edi,0xc043 at 0x4fd866   in FUN_004fd810     unported
 * Those last three functions are absent from PROGRESS.csv: they sit in
 * the address gaps 0x4fd50f-0x4fd58f, 0x4fd647-0x4fd67f and
 * 0x4fd80f-0x4fd87f between ported entries, each with its own prologue
 * and its own ret.  That is exactly why the binary shows 7 sites where
 * count_call_args.py reports 3.
 *
 * STILL DROPPED, out of scope for this pass: EAX is the CBuddy2 session
 * object (`mov esi,eax` at 0x4fcf16; the +0x2c connection and the
 * +0x1a90 handler are derived from it) and EBX is the 16-byte peer name
 * (the relay branch spills it into the param_2 stack slot at 0x4fcf42
 * and hands FUN_00502650 that slot's address as a one-entry name array,
 * which that callee walks as `mov ecx,[eax+edi*4]` into a 0x10-byte
 * strncpy).  The body still dereferences an unassigned in_EAX after this
 * edit, so behaviour is unchanged, not fixed.
 *
 * ABI: `ret 8` at both 0x4fcf3d and 0x4fcf64 matches the two declared
 * stack parameters, so this is a clean append, not a re-slot.  param_1 is
 * the payload pointer and param_2 its length (FUN_004fe110 rejects
 * lengths above 0x173a, FUN_00502650 clamps to 0xff).  BEWARE that Ghidra
 * mis-modelled the virtual call at 0x4fcf1d as taking no arguments when
 * it actually consumes the EBX pushed at 0x4fcf1a and returns `ret 4` -
 * proved by the epilogue, which needs esp = entry-8 for `pop esi / pop
 * ebp / ret 8` to land on the return address, and by FUN_004fe110's own
 * `ret 0x14`.  That 4-byte frame error is where this body's
 * `unaff_retaddr` comes from - the real value at [esp+0xc] is param_1 -
 * and it is why `&stack0x00000004` is really the address of the param_2
 * slot that 0x4fcf42 has just overwritten with EBX.  Left alone: an
 * EBX/param question, not an EDI one.
 */
#include "ghidra_types.h"


undefined4 FUN_004fcf10(undefined4 param_1,undefined4 param_2,undefined4 regEdi)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000004;
  char cVar1;
  int *in_EAX;
  undefined4 unaff_EBX;
  undefined4 unaff_EDI = regEdi;
  undefined4 unaff_retaddr;
  
  cVar1 = (**(code **)(*in_EAX + 0x3c))();
  if (cVar1 != '\0') {
    FUN_004fe110(in_EAX + 0xb,unaff_EBX,unaff_EDI,unaff_retaddr,param_2);
    /* Ghidra emitted a bare `return;` in a value-returning function;
     * MSVC falls through with whatever's in EAX, gcc 14 rejects it
     * (-Wreturn-mismatch). This path's result is unused by callers -
     * return 0 to satisfy both toolchains without inventing a value. */
    return 0;
  }
  FUN_004fd030();
  FUN_00502650(in_EAX,1,&stack0x00000004,unaff_retaddr,param_2);
  /* Ghidra emitted a bare `return;` in a value-returning function;
   * MSVC falls through with whatever's in EAX, gcc 14 rejects it
   * (-Wreturn-mismatch). This path's result is unused by callers -
   * return 0 to satisfy both toolchains without inventing a value. */
  return 0;
}

