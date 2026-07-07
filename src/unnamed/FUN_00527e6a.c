/* FUN_00527e6a - 0x00527e6a in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _fabs
   
   Library: Visual Studio 2003 Release */

double __cdecl _fabs(double _X)

{
  undefined4 uVar1;
  int iVar2;
  float10 fVar3;
  
  uVar1 = __ctrlfp(0x133f,0xffff);
  if ((_X._6_2_ & 0x7ff0) == 0x7ff0) {
    iVar2 = __sptype(_X);
    if (iVar2 == 1) {
      __ctrlfp(uVar1,0xffff);
      fVar3 = (float10)_X;
    }
    else if (iVar2 == 2) {
      __ctrlfp(uVar1,0xffff);
      fVar3 = -(float10)_X;
    }
    else if (iVar2 == 3) {
      fVar3 = (float10)__handle_qnan1();
    }
    else {
      fVar3 = (float10)__except1(8,0x15,_X,_X + _DAT_00544e38,uVar1);
    }
  }
  else {
    __ctrlfp(uVar1,0xffff);
    fVar3 = (float10)ABS(_X);
  }
  return (double)fVar3;
}

