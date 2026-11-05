/* LocalizedStrings_SetAt - 0x0043dd40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043dd40 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: Called by
 * LoadLocalizedStrings once per parsed Language.txt line (id, message,
 * table). It first looks the id up with FindLocalizedStringNode; on a hit
 * it overwrites the node's string at +4 with AssignStringBuffer, on a miss
 * it falls into LocalizedStrings_Insert. That is an assign-or-insert on
 * the id -> string table GetLocalizedString reads. SetAt is the MFC/ATL
 * map verb for that; the container itself is a custom tree, so the verb is
 * borrowed (LIKELY).
 *
 * Dropped-register-arg fix (confirmed against the 0x43dd40 disassembly):
 * Ghidra's per-call-site decompile only resolved the one stack-passed
 * arg (param_1, the map/tree root). The message pointer was dropped as
 * an uninitialized `in_EAX` read, and the id (real register ECX at
 * entry, `mov edi,ecx`) wasn't read at all by Ghidra's output even
 * though the caller (LoadLocalizedStrings, 0x43dc25-0x43dc2f) loads it
 * into ECX right before the call:
 *   mov edx,[ebp+0x8]   ; param_1 (table), pushed on the stack
 *   push edx
 *   lea eax,[esp+0x1c]  ; message pointer, passed in EAX
 *   mov ecx,edi         ; id, passed in ECX
 *   call 0x43dd40
 * Promoted to take id (ecx) and message (eax) as explicit params,
 * passed through unchanged to this function's own callees.
 */
#include "ghidra_types.h"


int LocalizedStrings_SetAt(int id,undefined4 param_1,char *message)

{
  char cVar1;
  int iVar2;
  char *pcVar3;

  /* orig 0x43dd4a `mov edx,ebp` = param_1 (the table, this function's
   * first STACK argument) and 0x43dd48 `mov edi,ecx` = id. */
  iVar2 = (int)FindLocalizedStringNode(0,(undefined4 *)param_1,id);
  if (iVar2 == 0) {
    iVar2 = FUN_0043de70(param_1,id,message);
    return iVar2;
  }
  pcVar3 = message;
  if (message != (char *)0x0) {
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    AssignStringBuffer(iVar2 + 4,message);
    return iVar2;
  }
  AssignStringBuffer(iVar2 + 4,0);
  return iVar2;
}

