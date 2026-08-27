/* FUN_0040cdf0 - 0x0040cdf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DECLARED ARGUMENTS FILLED.  `ret 0` puts nothing on the stack, so param_1
 * (ECX) and param_2 (EDX) are both registers, and every call site passed
 * neither.  ECX is a PHANTOM -- the entry writes it (`mov ecx,[eax+4]`)
 * before any read -- so it takes 0; EDX is 0x2710 at every site.
 *
 * ESI and EDI are also read before being written here, so they are further
 * register arguments Ghidra did not declare.  ESI genuinely varies per site
 * (0 and 1), so it stays open rather than being guessed at.
*
 * DROPPED REGISTERS RECOVERED (2026-08-27): ESI is the inner key compared
 * against each node's +8, and EDI is the container -- &g_activeObjectRegistry2
 * (0xe9c0fc) at all six sites, loaded once per pair and left live across both
 * calls.  ESI is 0 on the first call of each pair and 1 on the second.
 *
 * The three call pairs are pinned by their own blocks rather than by order:
 * FUN_00445450's is preceded by the address-bearing label LAB_00445543, and
 * 0x445543 really is that block (`xor edx,edx / mov edi,0xe9be90 /
 * call 0x405fb0 / xor esi,esi / mov edx,0x2710 / mov edi,0xe9c0fc`).  The
 * other two carry a call-sequence fingerprint plus a store the source also
 * shows.
 *
 * Note the failure mode this change buys: __fastcall decorates as
 * @FUN_0040cdf0@N with N the stack-byte count, so widening 8 to 16 renames
 * the symbol and any missed call site becomes a LINK error rather than a
 * silent garbage read.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cdf0(undefined4 param_1,uint param_2,uint regEsi,int regEdi)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI = regEsi;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(*(int *)(unaff_EDI + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while (uVar2 <= param_2) {
    if (uVar2 == param_2) {
      puVar3 = *(undefined4 **)(iVar1 + 0x10);
      uVar2 = puVar3[2];
      if (uVar2 <= unaff_ESI) goto LAB_0040ce15;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  goto LAB_0040ce21;
  while( true ) {
    puVar3 = (undefined4 *)puVar3[4];
    uVar2 = puVar3[2];
    if (unaff_ESI < uVar2) break;
LAB_0040ce15:
    if (uVar2 == unaff_ESI) goto LAB_0040ce23;
  }
LAB_0040ce21:
  puVar3 = (undefined4 *)0x0;
LAB_0040ce23:
  if (puVar3 == *(undefined4 **)(unaff_EDI + 8)) {
    *(undefined4 *)(unaff_EDI + 8) = 0;
  }
  if (puVar3 != (undefined4 *)0x0) {
    *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
    *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
    (**(code **)*puVar3)(1);
  }
  return;
}

