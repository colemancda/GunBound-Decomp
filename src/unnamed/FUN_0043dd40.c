/* FUN_0043dd40 - 0x0043dd40 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
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


int FUN_0043dd40(int id,undefined4 param_1,char *message)

{
  char cVar1;
  int iVar2;
  char *pcVar3;

  iVar2 = FUN_0043e060();
  if (iVar2 == 0) {
    iVar2 = FUN_0043de70(param_1);
    return iVar2;
  }
  pcVar3 = message;
  if (message != (char *)0x0) {
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    FUN_004056c0(iVar2 + 4,message);
    return iVar2;
  }
  FUN_004056c0(iVar2 + 4,0);
  return iVar2;
}

