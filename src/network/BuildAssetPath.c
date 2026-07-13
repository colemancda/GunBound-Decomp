/* BuildAssetPath - 0x004b3da0 in the original binary.
 *
 * DROPPED VARIADIC ARGUMENTS (bug pattern #1, variadic flavor): Ghidra's
 * decompilation only names two parameters (param_1 = dest buffer,
 * param_2 = first path segment), then reads all further segments via
 * `puVar4 = &param_2; ...; puVar4[1]; puVar4 = puVar4 + 1;` - i.e. it
 * takes the address of param_2's own stack slot and walks forward
 * through the caller's argument list one 4-byte slot at a time until it
 * hits a NULL sentinel. That's exactly how a stack-based __cdecl
 * variadic argument list looks once Ghidra fails to resolve it as real
 * parameters - confirmed at the call site: every one of this function's
 * 8 callers (grepped across src/) passes exactly
 * BuildAssetPath(dest, base, segment, 0) - a dest buffer, a base path,
 * one path-segment string, and a 0 (NULL) terminator - never just the
 * 2-argument form the old signature declared. Disassembly at
 * 0x004b3da0 confirms it: `lea edi,[esp+0x14]` takes the address of the
 * 2nd stack arg's slot, then `mov ecx,[edi+0x4]` / `add edi,0x4` walks
 * forward through subsequent pushed arguments each loop iteration -
 * this is a real variadic function, not a 2-arg one. Fixed by promoting
 * it to a proper `...` variadic (matches this codebase's established
 * _sprintf/_sscanf variadic shims in src/cxx/crt_shims_c.c) that
 * concatenates dest, then param_2, then each further NULL-terminated
 * char* segment, backslash-separated, collapsing any duplicate
 * backslashes at each segment boundary (both from the end of the
 * accumulated path and the start of the next segment) - preserving the
 * original's exact byte-for-byte behavior.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output otherwise - not
 * hand-verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>
#include <stdarg.h>


void BuildAssetPath(int param_1,char *param_2,...)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  va_list puVar4;

  iVar3 = 0;
  if (param_2 != (char *)0x0) {
    va_start(puVar4, param_2);
    do {
      if (0 < iVar3) {
        *(undefined1 *)(iVar3 + param_1) = 0x5c;
        iVar3 = iVar3 + 1;
        cVar2 = *param_2;
        while (cVar2 == '\\') {
          pcVar1 = param_2 + 1;
          param_2 = param_2 + 1;
          cVar2 = *pcVar1;
        }
      }
      cVar2 = *param_2;
      while (cVar2 != '\0') {
        *(char *)(iVar3 + param_1) = cVar2;
        pcVar1 = param_2 + 1;
        iVar3 = iVar3 + 1;
        param_2 = param_2 + 1;
        cVar2 = *pcVar1;
      }
      cVar2 = *(char *)(param_1 + -1 + iVar3);
      while (cVar2 == '\\') {
        pcVar1 = (char *)(param_1 + -2 + iVar3);
        iVar3 = iVar3 + -1;
        cVar2 = *pcVar1;
      }
      param_2 = va_arg(puVar4, char *);
    } while (param_2 != (char *)0x0);
    va_end(puVar4);
  }
  *(undefined1 *)(iVar3 + param_1) = 0;
  return;
}

