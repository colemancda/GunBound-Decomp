/* CommP2POwnerConnect - 0x004fd470 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28, verb LIKELY): the owner's connect entry point -
 * virtual slot 3 of the main vtable 0x5575c8 (the pointer sits at
 * .data 0x5575d4, per find_vtable_refs; it has no direct binary
 * caller, which is why callsite_regs finds zero sites). It keys the
 * two 0x284-byte cipher schedules at +0x1b20/+0x1da4 from the two
 * string arguments via FUN_005051e0, creates the bound socket, and -
 * unless the +0x1a70 flag routes the pre-bound arm through
 * FUN_005024a0 instead - resolves and connects to (param_2 = hostname,
 * param_3 = port) via ResolveHostAddress -> ConnectToHostPort, storing
 * the connection node at +0x1a74, the same field DestroyCommP2POwner
 * later shuts down. "Connect" describes the dominant arm; the
 * +0x1a70 != 0 arm skips the outbound connect.
 */
#include "ghidra_types.h"


undefined4 __thiscall
CommP2POwnerConnect(int param_1,undefined4 param_2,undefined4 param_3,char *param_4,char *param_5)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1a71) == '\0') {
    char *start4 = param_4;
    {
      do {
        cVar1 = *param_4;
        param_4 = param_4 + 1;
      } while (cVar1 != '\0');
      /* RECOVERED (2026-07-19), orig 0x4fd48f-0x4fd49b: `sub eax,edx` /
       * `mov ecx,eax` (ECX = the strlen just computed), `lea edx,[edi+0x1b20]`
       * (EDX = the crypto context), `mov eax,ebx` (EAX = the string base).
       * Ghidra kept the strlen loop but dropped all three arguments. */
      FUN_005051e0((int)(param_4 - start4) - 1,param_1 + 0x1b20,start4);
    }
    {
      char *start5 = param_5;
      do {
        cVar1 = *param_5;
        param_5 = param_5 + 1;
      } while (cVar1 != '\0');
      /* RECOVERED (2026-07-19), orig 0x4fd4b7-0x4fd4bf: same shape, with
       * `lea edx,[edi+0x1da4]` as the context. */
      FUN_005051e0((int)(param_5 - start5) - 1,param_1 + 0x1da4,start5);
    }
    /* DROPPED-REG FIX: orig 0x4fd4c4 `lea esi,[edi+0x2c]` (EDI = this)
       and 0x4fd4c7 `mov eax,ebx` (EBX = param_4's original base, hoisted
       above as start4; both survive the two FUN_005051e0 calls, whose
       epilogue 0x505299-0x50529c restores ebx/edi). */
    CreateBoundSocket(start4,param_1 + 0x2c);
    if (*(char *)(param_1 + 0x1a70) == '\0') {
      /* DROPPED-REG FIX 2026-08-28: the hostname is this function's
         param_2 - `mov eax,[esp+0x10]` at 0x4fd4f1, ONE push deep (the
         pending push of param_3 at 0x4fd4f0), reaches entry+4; the same
         textual [esp+0x10] one instruction earlier, at zero depth, is
         param_3. The pending-push term is the whole difference. */
      iVar2 = ResolveHostAddress(param_1 + 4,param_3,(char *)param_2);
      *(int *)(param_1 + 0x1a74) = iVar2;
      if (iVar2 == 0) {
        return 0;
      }
    }
    else {
      FUN_005024a0(0x1000);
    }
  }
  return 1;
}

