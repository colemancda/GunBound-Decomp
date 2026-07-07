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
    iVar2 = (*pFVar1)(param_1,0x800,&DAT_005573c8,&DAT_00674f68,0);
    if (-1 < iVar2) {
      /* LAB_004edc10 in Ghidra's output is the entry point of the
       * enumeration callback it split out separately as FUN_004edd10 -
       * same address range, just labeled differently at this call
       * site vs. its own decompilation. */
      iVar2 = (**(int (**)())(*DAT_00674f68 + 0x10))(DAT_00674f68,4,FUN_004edd10,0,1);
      return -1 < iVar2;
    }
  }
  return false;
}

