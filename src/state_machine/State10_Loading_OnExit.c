/* State10_Loading_OnExit - 0x0043eff0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>

/* DESTRUCTOR DISPATCH FIXED (2026-10-30): each g_spriteRegistry layer walk
 * called slot 0 as `(*(code *)*obj)(1)` with obj = the node's VTABLE value,
 * so `this` was dropped and the vtable was passed in its place. The
 * original loads the layer from [0xea0e1c] and walks it as
 * `mov ecx,[layer+0x10]` / loop { mov edx,[ecx] / mov edi,[ecx+0x10] /
 * push 1 / call [edx] / mov ecx,edi }: ECX is the node itself and the
 * flag is pushed. Sites: 0x43f027, 0x43f067, 0x43f0b7.
 * The nodes are sprite frames (vtable 0x557524) whose slot 0 is
 * FUN_004f14c0, a raw-C port with __thiscall erased to cdecl, so `this`
 * and the flag both go on the stack - the same idiom as
 * State06_Logo2_OnExit.c (commits 4ac78dd1, 4cce0728). */
typedef void (*ListNodeVirtualFn)(void *thisPtr, undefined4 a1);


void State10_Loading_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  if (uVar1 < 0x2711) {
LAB_0043f004:
    if (uVar1 != 10000) goto code_r0x0043f006;
    puVar2 = (undefined4 *)puVar5[4];
    while (puVar2 != puVar5) {
      puVar3 = puVar2;
      puVar2 = (undefined4 *)puVar2[4];
      (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
    }
    puVar5[3] = puVar5;
    puVar5[4] = puVar5;
  }
LAB_0043f035:
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (0x2711 < uVar1) goto LAB_0043f075;
    if (uVar1 == 0x2711) break;
    puVar5 = (undefined4 *)puVar5[7];
    uVar1 = puVar5[1];
  }
  puVar2 = (undefined4 *)puVar5[4];
  while (puVar2 != puVar5) {
    puVar3 = puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
  }
  puVar5[3] = puVar5;
  puVar5[4] = puVar5;
LAB_0043f075:
  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (0x2712 < uVar1) {
      *(undefined4 *)(g_clientContext + 0x621e4) = 0;
      return;
    }
    if (uVar1 == 0x2712) break;
    puVar5 = (undefined4 *)puVar5[7];
    uVar1 = puVar5[1];
  }
  puVar2 = (undefined4 *)puVar5[4];
  iVar4 = g_clientContext;
  while (g_clientContext = iVar4, puVar2 != puVar5) {
    puVar3 = puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(ListNodeVirtualFn *)*puVar3)(puVar3, 1);
    iVar4 = g_clientContext;
  }
  puVar5[3] = puVar5;
  puVar5[4] = puVar5;
  *(undefined4 *)(iVar4 + 0x621e4) = 0;
  return;
code_r0x0043f006:
  puVar5 = (undefined4 *)puVar5[7];
  uVar1 = puVar5[1];
  if (10000 < uVar1) goto LAB_0043f035;
  goto LAB_0043f004;
}

