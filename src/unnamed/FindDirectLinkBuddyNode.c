/* FindDirectLinkBuddyNode - 0x00401bb0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_00505580 below is now AddBuddyDialog_SubmitBuddyName.)
 *
 * NAMED AND KEY ARGUMENT RECOVERED (2026-10-27), HIGH. Walks the
 * doubly-linked list at param_1+4/+0x1c (the usual intrusive-list head
 * shape in this tree) and __stricmp's each live entry's +0x21 field
 * against the lookup key, returning the matching node or 0. `ret 4`
 * confirms exactly one STACK argument (the container); the key arrived
 * only in EBX (`unaff_EBX` pre-promotion), a register-only input never
 * cleaned by the callee, matching the dropped-register family
 * documented throughout this subsystem.
 *
 * UpsertDirectLinkBuddyNode.c and RemoveDirectLinkBuddyNode.c already
 * cite this exact address by name as "the same FUN_00401bb0 roster
 * lookup" / "looks the node up by name (FUN_00401bb0, ...)" - both now
 * updated to the name below. Seven call sites, all confirmed on the
 * same container &DAT_00e53e88 (the "lobby-connection object"):
 *
 *   UpsertDirectLinkBuddyNode (0x401d5d)   container=param_2, key=EBX=
 *       incoming EAX (`mov ebx,eax` at 0x401d58, 3 instructions before
 *       the call, EBX untouched in between) -- in_EAX in the source.
 *   RemoveDirectLinkBuddyNode (0x401eec)   container=param_1, key=
 *       EBX=ESI=incoming EAX (`mov esi,eax` at 0x401ee7, `mov
 *       ebx,esi` at 0x401eea) -- regEax in the source, the SAME key
 *       FUN_00401c50 is given two lines later.
 *   EnsureChatLogPanelForPeer (0x402601)   container=param_1 (`mov
 *       eax,[esp+0xc]`, the first stack arg once the 2 prologue pushes
 *       are accounted for), key=EBX=param_2 (`mov ebx,ebp` at
 *       0x4025e6, ebp=[esp+0x10]=param_2, preserved across the
 *       intervening PanelManager_FindByName call).
 *   DispatchDirectLinkPacket (0x40361f, case 0x1004)   container=
 *       param_2 (pushed `ebp`), key=EBX=EDI=this function's own
 *       regEax (`mov edi,eax` at entry 0x4032d2, dominates this
 *       block). param_2 traces to FUN_00403170's param_1, used
 *       elsewhere as param_1+0x1be4 -- the same RBTree offset every
 *       other &DAT_00e53e88 caller addresses -- confirming the
 *       container (see DispatchDirectLinkPacket.c's own note).
 *   UpdateBuddyStatus (0x401fa2)   container=regEax, key=regEcx (`mov
 *       ebx,ecx` at 0x401fa2, the file's own header already flagged
 *       this as "pass it through when FUN_00401bb0 is promoted").
 *   FUN_00505580 (0x5055f1)   container=literal &DAT_00e53e88, key=
 *       EBX=[ebp+0x50] (`mov ebx,[ebp+0x50]` at 0x5055e2) --
 *       *(char**)(param_1+0x50), the same buddy-name pointer the
 *       function re-reads right after.
 *   FUN_00403ae0 (0x403b0b)   container=param_1+-8 (this virtual's
 *       "this" sits 8 bytes into the owner object, same convention as
 *       its vtable twin FUN_00403d20), key=EBX=[esp+0x2c] = local_20,
 *       the nickname buffer FindNicknameByUserId just filled.
 */
#include "ghidra_types.h"


int FindDirectLinkBuddyNode(int param_1,char *key)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *unaff_EBX = key;
  int iVar4;

  iVar4 = *(int *)(*(int *)(param_1 + 4) + 0x1c);
  if (iVar4 != *(int *)(param_1 + 4)) {
    do {
      iVar2 = *(int *)(iVar4 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        iVar3 = __stricmp((char *)(iVar2 + 0x21),unaff_EBX);
        if (iVar3 == 0) {
          return iVar2;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
    } while (iVar4 != *(int *)(param_1 + 4));
  }
  return 0;
}

