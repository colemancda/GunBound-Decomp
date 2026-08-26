/* FUN_00401cb0 - 0x00401cb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS ANALYSED, NOT APPLIED.  `ret 0`, so param_1 (ECX) and ESI
 * are the whole input.  At the sole call site (0x00411c65):
 *
 *   ecx = [esp + 0x60]        <- a caller stack local
 *   esi = 0xe53e88            -> &DAT_00e53e88
 *
 * ESI is known; param_1 is a spill and is not.  Passing ESI's value alone
 * would land it in param_1, which is the wrong slot.
 *
 * ESI RECOVERED (2026-08-25): the DAT_00e53e88 object, appending a 0x18-byte
 * record -- text at +0xc + count*0x18, count at +0xc0c.
 *
 * The stride is what confirms the caller's side.  FUN_00411b40's frame
 * constant is -0x168, pinned by four slots the source already names
 * ([esp+0x68] = local_100, [esp+0x6c] = local_fc, [esp+0x70] = local_f8,
 * [esp+0x74] = local_f4), and under it `lea ecx,[esp+0x60]` is &local_108.
 * That local and the four above it are one 0x18-byte record the caller has
 * just filled -- the same 0x18 this function strides by.
 */
#include "ghidra_types.h"


void __fastcall FUN_00401cb0(char *param_1,int regEsi)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = (char *)(regEsi + 0xc + *(int *)(regEsi + 0xc0c) * 0x18);
  do {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  *(int *)(regEsi + 0xc0c) = *(int *)(regEsi + 0xc0c) + 1;
  return;
}

