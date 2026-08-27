/* FUN_00406400 - 0x00406400 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is the INNER key.  The
 * body is the same two-level registry lookup as SetWidgetReadyState and
 * FUN_0040cdf0 -- outer list walked by +0x1c and keyed at +4 against param_2,
 * then the matched node's inner list walked by +0x10 and keyed at +8 against
 * ESI -- so ESI is a widget key, and the values found (1, 3, 5, 0x10) sit in
 * the same small-key band those functions use.
 *
 * Pairing is unambiguous without any ordering assumption: each of the four
 * ported callers contains exactly ONE site, and each loads a distinct literal
 * (`mov esi,5` at 0x428c21, `mov esi,3` at 0x4b82f7, `mov esi,0x10` at
 * 0x4b9d04, `mov esi,1` at 0x4d626c), all read individually off the
 * disassembly.
 *
 * There is a FIFTH binary site, 0x447671 in FUN_004475c0 with `mov esi,0xf`,
 * which has no C counterpart and should not: PROGRESS.csv marks
 * FUN_004475c0 TODO, i.e. not ported.  That is why count_call_args.py reports
 * four where callsite_regs.py reports five.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00406400(undefined4 param_1,uint param_2,int regEax,uint regEsi)

{
  uint uVar1;
  uint uVar2;
  uint unaff_ESI = regEsi;
  
  uVar2 = *(uint *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(uVar2 + 4);
  do {
    if (param_2 < uVar1) {
LAB_00406419:
      return uVar2 & 0xffffff00;
    }
    if (uVar1 == param_2) {
      uVar2 = *(uint *)(uVar2 + 0x10);
      uVar1 = *(uint *)(uVar2 + 8);
      if (uVar1 <= unaff_ESI) {
        while (uVar1 != unaff_ESI) {
          uVar2 = *(uint *)(uVar2 + 0x10);
          uVar1 = *(uint *)(uVar2 + 8);
          if (unaff_ESI < uVar1) {
            return uVar2 & 0xffffff00;
          }
        }
        if (*(int *)(uVar2 + 0x24) != 3) {
          return CONCAT31((int3)(uVar2 >> 8),1);
        }
      }
      goto LAB_00406419;
    }
    uVar2 = *(uint *)(uVar2 + 0x1c);
    uVar1 = *(uint *)(uVar2 + 4);
  } while( true );
}

