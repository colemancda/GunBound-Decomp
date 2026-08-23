/* FUN_0040cf30 - 0x0040cf30 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED, EAX AND ESI RECOVERED.  `ret 4` gives one stack
 * argument: param_1 is ECX (a PHANTOM, written before any read, so 0),
 * param_2 is EDX, param_3 is the push, and EAX and ESI are two further
 * register inputs.  From 0x00447239-0x0044725c, two calls in one
 * straight-line run:
 *
 *   push 0 / xor esi,esi / edx=0x2710 / eax=0xe9c0fc   -> esi = 0
 *   push esi / mov esi,1 / edx=0x2710 / eax=0xe9c0fc   -> esi = 1
 *
 * The second site's `push esi` pushes ZERO -- esi is still 0 from the earlier
 * xor, and only set to 1 afterwards -- so param_3 is 0 at both sites.  Read as
 * esi's value at the CALL instead of at the PUSH it looks like 1, which is
 * what made this function appear to contradict itself earlier; the two source
 * lines passing 0 were right.  Pairing the two sites is safe here for the one
 * reason that is not an assumption: within a straight-line run, source order
 * must equal VA order.
 *
 * EAX is the registry the tree walk starts from (*(regEax + 4) + 0x1c).
 */
#include "ghidra_types.h"


void __fastcall FUN_0040cf30(undefined4 param_1,uint param_2,int param_3,int regEax,
                             uint regEsi)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= regEsi) {
      while (uVar1 != regEsi) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (regEsi < uVar1) {
          return;
        }
      }
      *(uint *)(iVar2 + 0x448) = (uint)(param_3 == '\0');
    }
  }
  return;
}

