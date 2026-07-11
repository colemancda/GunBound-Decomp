/* InitDirectInput - 0x004edc50 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


bool InitDirectInput(undefined4 param_1)

{
  FARPROC pFVar1;
  int iVar2;
  
  DAT_00793544 = LoadLibraryA(s_dinput8_dll_00557428);
  if (DAT_00793544 != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(DAT_00793544,s_DirectInput8Create_00557414);
    /* FARPROC is a strict zero-arg prototype under gcc; DirectInput8Create
     * takes 5 args - cast through a matching pointer type to call it. */
    iVar2 = ((int (WINAPI *)(void *, int, void *, void *, void *))pFVar1)
                (param_1,0x800,&DAT_005573c8,&DAT_00674f68,0);
    if (-1 < iVar2) {
      /* LAB_004edc10 in Ghidra's output is the entry point of the
       * enumeration callback it split out separately as FUN_004edd10 -
       * same address range, just labeled differently at this call
       * site vs. its own decompilation.
       *
       * Dispatched through an explicit __stdcall cast, not the generic
       * `int (**)()` (K&R/unspecified-args) type: that defaults to __cdecl
       * under MSVC, so the compiler emits a caller-side stack cleanup on top
       * of the real __stdcall COM callee's own - see SetupZBuffer.c for the
       * full writeup of this bug class. */
      iVar2 = ((HRESULT (WINAPI *)(void *, DWORD, LPVOID, LPVOID, DWORD))
                   (*(void ***)DAT_00674f68)[4])
                  (DAT_00674f68, 4, FUN_004edd10, 0, 1);
      return -1 < iVar2;
    }
  }
  return false;
}

