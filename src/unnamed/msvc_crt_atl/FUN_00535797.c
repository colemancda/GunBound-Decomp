/* FUN_00535797 - 0x00535797 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    _strncnt
   
   Library: Visual Studio 2003 Release */

size_t __cdecl _strncnt(char *_String,size_t _Cnt)

{
  char *pcVar1;
  char *in_EAX;
  
  pcVar1 = _String;
  for (; (pcVar1 != (char *)0x0 && (*in_EAX != '\0')); in_EAX = in_EAX + 1) {
    pcVar1 = pcVar1 + -1;
  }
  return (size_t)(_String + (-1 - (int)(pcVar1 + -1)));
}

