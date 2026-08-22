/* FUN_0044c460 - 0x0044c460 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SIGNATURE FULLY RECOVERED (both call sites read out of the original).
 * `ret 0x18` = 6 stack arguments, and the entry does `mov esi, eax`, so EAX
 * is an incoming register argument too; EDI is a second one.
 *
 * The port had been calling this with FOUR arguments against a SIX-parameter
 * definition -- param_5 and param_6 were simply absent, so the callee read
 * two slots of whatever the caller happened to leave on the stack.  That
 * mismatch survived because functions.h declared it K&R-empty ("void
 * FUN_0044c460();"), which in C accepts any argument list; the defect only
 * became visible once the declaration was given real parameters.  A missing
 * argument is invisible precisely where you would most want a compiler to
 * catch it.
 *
 * Both call sites live in FUN_0044a000 and decode completely:
 *
 *   0x0044aec9   push 4 / 0xa / 8 / &buf / 0x3c / lea eax,[ebp+0xe]
 *                mov eax,0x118   mov edi,0x1f4
 *   0x0044afea   push 4 / 0xa / 8 / &buf / 0x32 / lea eax,[ebp+0xe]
 *                mov eax,0x117   mov edi,0x1f4
 *
 * The param_2 literal (0x3c vs 0x32) pairs each binary site to its source
 * counterpart unambiguously, so no call-sequence fingerprinting was needed.
 * EDI is 0x1f4 at both -- which is how this function reached the uniform-value
 * batch in the first place -- while EAX differs per site and had to be read
 * individually.
 */
#include "ghidra_types.h"


void FUN_0044c460(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int regEax,uint regEdi)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  int local_8;
  int local_4;
  
  bVar3 = false;
  local_8 = 0;
  if (param_4 < 1) {
    return;
  }
  local_4 = param_4;
LAB_0044c490:
  if (local_4 % 3 == 0) {
    if ((((bVar3) && (DAT_0079352c != 0)) && (-1 < regEax)) && (iVar4 = FindSpriteFrame(), iVar4 != 0))
    {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped();
      }
    }
    param_1 = param_1 + param_6;
  }
  if (*(char *)(local_8 + param_3) != ' ') {
    uVar1 = *(char *)(local_8 + param_3) + -0x30 + param_2;
    bVar3 = true;
    if ((DAT_0079352c != 0) && (-1 < (int)uVar1)) {
      iVar4 = *(int *)(DAT_00ea0e1c + 0x1c);
      uVar2 = *(uint *)(iVar4 + 4);
      while (uVar2 <= regEdi) {
        if (uVar2 == regEdi) {
          iVar4 = *(int *)(iVar4 + 0x10);
          uVar2 = *(uint *)(iVar4 + 8);
          if (uVar2 <= uVar1) goto LAB_0044c53f;
          break;
        }
        iVar4 = *(int *)(iVar4 + 0x1c);
        uVar2 = *(uint *)(iVar4 + 4);
      }
    }
  }
  goto LAB_0044c56e;
  while( true ) {
    iVar4 = *(int *)(iVar4 + 0x10);
    uVar2 = *(uint *)(iVar4 + 8);
    if (uVar1 < uVar2) break;
LAB_0044c53f:
    if (uVar2 == uVar1) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(param_1);
      }
      else {
        BlitSpriteClipped(uVar1);
      }
      break;
    }
  }
LAB_0044c56e:
  param_1 = param_1 + param_5;
  local_8 = local_8 + 1;
  local_4 = local_4 + -1;
  if (param_4 <= local_8) {
    return;
  }
  goto LAB_0044c490;
}

