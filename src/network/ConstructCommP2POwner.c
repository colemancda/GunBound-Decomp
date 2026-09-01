/* ConstructCommP2POwner - 0x004fd0f0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the constructor of the 0x2028-byte comm owner
 * object - "the CCommP2P owner", the term InitCommP2PNotifyWindow.c's
 * header already uses for exactly this function. Its lone caller is
 * the operator_new(0x2028) factory FUN_004fd090. It stamps the
 * abstract-interface vtable 0x557610 (all sixteen slots are _purecall
 * 0x525acd) and then the four concrete vtables its destructor
 * re-installs in the same four slots - 0x5575c8 at +0, 0x5575b8 at +4
 * (the connection-list engine CommEngineCloseConnection and friends
 * receive), 0x5575ac at +0x2c (the CCommP2P sub-object, per the
 * "CCommP2P<> Notify Window" class string its base ctor registers),
 * 0x5575a8 at +0x2f4 - creates both notify windows, seeds two TT800
 * PRNG states and builds two CAtlMaps. The composite's original class
 * name is unknown; "CommP2POwner" is the tree's working handle for it.
 * Destructor: DestroyCommP2POwner (0x4fd230); deleting wrapper with
 * the +0x1a6c refcount: FUN_004fd3c0, vtable 0x5575c8 slot 1.
 */
#include "ghidra_types.h"


undefined4 * ConstructCommP2POwner(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537bc6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  *param_1 = &PTR_LAB_00557610;
  /* DROPPED-REG FIX: orig 0x4fd10d `lea esi,[ebp+4]` (EBP = param_1) -
   * the engine notify sub-object at +4, whose vtable slot line 42 below
   * re-stamps with the derived 0x5575b8. */
  CreateCommEngineNotifyWindow(param_1 + 1);
  /* orig 0x4fd11c `lea edi, [ebp + 0x2c]` (EBP = param_1) -
   * InitCommP2PNotifyWindow's recovered EDI `self` argument. */
  InitCommP2PNotifyWindow(param_1 + 0xb);
  param_1[0xbd] = &PTR_LAB_00557594;
  param_1[1] = &PTR_LAB_005575b8;
  *param_1 = &PTR_LAB_005575c8;
  param_1[0xb] = &PTR_LAB_005575ac;
  param_1[0xbd] = &PTR_FUN_005575a8;
  param_1[0x69b] = 1;
  *(undefined1 *)(param_1 + 0x69c) = 0;
  *(undefined1 *)((int)param_1 + 0x1a71) = 0;
  param_1[0x69d] = 0;
  param_1[0x69e] = 0;
  param_1[0x6a9] = 0;
  param_1[0x6aa] = 0;
  param_1[0x6ab] = 0;
  param_1[0x6ac] = param_2;
  param_1[0x6ad] = 0;
  param_1[0x6ae] = 0;
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,param_1 + 0x6b0);
  HashMap_Construct(0xa,0x3f400000,0x3e800000,0x40100000,0x11,param_1 + 0x6bc);
  *(undefined1 *)(param_1 + 0x74a) = 0;
  SeedTT800State(param_1 + 0x74b);
  param_1[0x767] = 0;
  param_1[0x768] = 0;
  *(undefined1 *)(param_1 + 0x7eb) = 0;
  SeedTT800State(param_1 + 0x7ec);
  param_1[0x808] = 0;
  param_1[0x809] = 0;
  return param_1;
}

