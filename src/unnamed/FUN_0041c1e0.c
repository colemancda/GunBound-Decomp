/* FUN_0041c1e0 - 0x0041c1e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DECLARED ARGUMENTS FILLED.  `ret 0` puts nothing on the stack, so param_1
 * (ECX) and param_2 (EDX) are both registers, and the sole call site
 * (0x004e1421) passed neither.  ECX is never set there and never read here,
 * so param_1 is a PHANTOM and takes 0; EDX is loaded from [0x5b3484].
 *
 * param_2 = g_clientContext is corroborated by the body rather than only by
 * the call site: every write here is param_2 + 0x41344 and up, the
 * arena-relative form.  Clearing 0x340 dwords at a fixed context offset only
 * makes sense against the context base.
 *
 * EAX is also read before being written, so it is a further register argument
 * -- but Ghidra did not model it at all here, so there is no local to promote
 * and no way to express it without restructuring the body.
 */
#include "ghidra_types.h"


void __fastcall FUN_0041c1e0(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined1 *)(param_2 + 0x41344) = 0;
  puVar2 = (undefined4 *)(param_2 + 0x41345);
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x41445);
  for (iVar1 = 0x340; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x43548);
  for (iVar1 = 0x240; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x43e48);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = (undefined4 *)(param_2 + 0x44048);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

