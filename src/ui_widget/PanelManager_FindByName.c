/* PanelManager_FindByName - 0x00509730 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-10-30): the name being searched for arrives in
 * EBX. The body pushes it unchanged as the second _stricmp argument
 * (`push ebx` / `push ecx` / `call 0x52b507` at 0x509764-0x509766, ECX =
 * panel+0x90) and never writes EBX. The port read an unassigned
 * unaff_EBX, so every comparison ran against garbage. callsite_regs.py
 * finds six binary call sites, all with EAX = 0xe53c40
 * (g_uiPanelManager). EBX at each one:
 *   0x4024a1, 0x4024be  DisplayIncomingWhisper: `mov ebx,eax` at 0x402416,
 *                       the sender name it takes in EAX (regEax)
 *   0x402577, 0x4025a4  FUN_004024f0: `mov ebx,eax` at 0x4024ff, its own
 *                       EAX name (regEax)
 *   0x4025ed            EnsureChatLogPanelForPeer: `mov ebx,ebp` at
 *                       0x4025e6, ebp = [esp+0x10] = its peer-name param_2
 *   0x505cc4            CBuddyPanel's slot 4 (0x505c90): `lea ebx,[edi+0x21]`
 *                       at 0x505cbc, the selected buddy node's name
 * Promoted to a trailing parameter.
 */
#include "ghidra_types.h"


int PanelManager_FindByName(int regEax,char *regEbx)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  char *unaff_EBX = regEbx;
  
  puVar1 = *(undefined4 **)(regEax + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((((*(int *)(iVar2 + 0x20) != 0) || (*(int *)(iVar2 + 0x24) != 0x4e21)) ||
           (*(int *)(iVar2 + 0x4c) != 0)) ||
          (iVar3 = __stricmp((char *)(iVar2 + 0x90),unaff_EBX), iVar3 != 0));
  return iVar2;
}

