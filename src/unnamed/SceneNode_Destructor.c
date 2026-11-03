/* SceneNode_Destructor - 0x004f33b0 in the original binary.
 *
 * NAMING (batch 22, was FUN_004f33b0): Stamps the SceneNode base vtable
 * 0x557538 then 0x55752c; called by SceneNode_ScalarDtor (slot 0 of
 * 0x557538) and by the derived destructor 0x4e9ba0.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIX (2026-11-03): the child-list delete dropped the node. 0x4f3410-0x4f341a
 * is `mov eax,[ecx] / mov esi,[ecx+0xd8] / push 1 / call [eax]` with ECX =
 * the node (first node [this+0xd4]); it is now (node, 1) through the cdecl
 * ListNodeVirtualFn (erased __thiscall).
 */
#include "ghidra_types.h"

typedef void (*ListNodeVirtualFn)(void *thisPtr, undefined4 a1);


void __fastcall SceneNode_Destructor(undefined4 *param_1)

{
  void *_Memory;
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537818) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_FUN_00557538;
  local_4 = 0;
  if ((*(char *)(param_1 + 0x82) != '\0') &&
     (_Memory = (void *)param_1[0x83], _Memory != (void *)0x0)) {
    FUN_004f2a10();
    _free(_Memory);
  }
  puVar1 = (undefined4 *)param_1[0x35];
  *(undefined1 *)(param_1 + 0x82) = 0;
  while (puVar1 != (undefined4 *)0x0) {
    puVar2 = puVar1;
    puVar1 = (undefined4 *)puVar1[0x36];
    (*(ListNodeVirtualFn *)*puVar2)(puVar2,1);
  }
  *param_1 = &PTR_LAB_0055752c;
  return;
}

