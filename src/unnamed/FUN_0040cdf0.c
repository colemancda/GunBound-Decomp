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
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cdf0(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI;
  int unaff_EDI;
  
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

