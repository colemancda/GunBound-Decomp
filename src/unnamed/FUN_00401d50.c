/* FUN_00401d50 - 0x00401d50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * Find-or-create one named entry in the container param_2.  The dropped
 * EAX is the LOOKUP KEY: `mov ebx,eax` at 0x00401d58, before any write
 * to EAX, parks it in EBX; FUN_00401bb0 - called three instructions
 * later at 0x00401d5d with EBX still live - stricmps that pointer (its
 * `unaff_EBX`) against every entry's +0x21 field, and on a miss the
 * fresh 0x5c-byte node gets it strcpy'd to +0x21, a 13-byte field
 * holding 12 chars plus a NUL at the FUN_00411b40 sites.  param_1 (ECX)
 * is a separate 9-byte name copied to +0x18, param_7 a 27-byte string
 * copied to +0x41, param_5 + 4 lands in the short at +0x2e and param_6's
 * four dwords in +0x31..+0x40.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-27).  `ret 0x18` is six stack
 * dwords and the declared param_2..param_7 are exactly six, so the
 * DECLARATION was already right and every CALL SITE was short by one:
 * Ghidra emitted all three ported callers without the ECX `this`, so
 * &DAT_00e53e88 - really param_2 - sat in the char *param_1 and every
 * later argument was off by one.  Appending EAX would have landed the
 * key in param_7.  There was also no prototype at all in functions.h,
 * which is how the shifted lists survived.
 *
 * Five binary sites, three in ported callers.  0x0040396a and 0x004041b8
 * lie in address gaps between PROGRESS.csv entries (0x004038b3 ..
 * 0x00403ae0 and 0x00403fea .. 0x00404330, each int3 padding followed by
 * a fresh prologue at 0x004038c0 and 0x00403ff0) - unported code with no
 * source to fix; both nevertheless show the recovered shape, `lea
 * ecx,[rec+0x28]` for param_1 and `lea eax,[esp+0x58]` for the key.
 *
 * Site 0x004035df is DispatchDirectLinkPacket's `uVar2 == 0x1003` arm
 * (witness: the `sub eax,0x1001 / dec / dec` dispatch chain at
 * 0x00403564, and param_6 = &local_118, the six 0xffffffff stores the C
 * already shows).  EAX = EDI = that function's own regEax, set once at
 * 0x004032d2 and untouched on the only path into the arm.  ECX is a
 * 9-byte name buffer at entry-0x12c built from packet+8 and packet+0xc
 * that the port had dropped ENTIRELY - Ghidra folded those stores away
 * as dead once it lost the ECX argument - restored as local_12c[9]: the
 * same 8-char name, DBCS trailing-byte trim and NUL that FUN_00411b40
 * spells out as local_148 / local_144 / local_140.
 *
 * Sites 0x00411d50 and 0x00412107 are both in FUN_00411b40 (witnesses:
 * param_6 = local_108 with param_7 = &local_13c at the first, the
 * immediately preceding FUN_00401ce0 call whose result is param_4 =
 * uVar6 at the second).  Both take ECX = &local_148 and EAX =
 * &local_158; the frame base is entry-0x168 at each, pinned by several
 * known slots apiece.  Those two local groups are 9 and 13 bytes wide -
 * exactly the +0x18 and +0x21 fields of the node built here - but, like
 * the &local_13c the file already passes, they are separately declared
 * locals whose contiguity MSVC does not guarantee; coalescing them into
 * arrays is a follow-up.
 */
#include "ghidra_types.h"


void __thiscall
FUN_00401d50(char *param_1,int param_2,char param_3,undefined4 param_4,short param_5,
            undefined4 *param_6,char *param_7,char *regEax)

{
  int *piVar1;
  char cVar2;
  char *in_EAX = regEax;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  
  iVar3 = FUN_00401bb0(param_2);
  if (iVar3 == 0) {
    puVar4 = operator_new(0x5c);
    if (puVar4 != (undefined4 *)0x0) {
      puVar4[3] = 0;
      puVar4[4] = 0;
      puVar4[1] = param_4;
      puVar4[2] = 0xffffffff;
      *(undefined1 *)(puVar4 + 5) = 0;
      *(undefined1 *)((int)puVar4 + 0x15) = 0;
      *puVar4 = &PTR_FUN_00551cb4;
      *(undefined1 *)(puVar4 + 0xc) = 0;
      *(undefined4 *)((int)puVar4 + 0x31) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x35) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x39) = 0xffffffff;
      *(undefined4 *)((int)puVar4 + 0x3d) = 0xffffffff;
      iVar3 = 0x18 - (int)param_1;
      do {
        cVar2 = *param_1;
        param_1[(int)puVar4 + iVar3] = cVar2;
        param_1 = param_1 + 1;
      } while (cVar2 != '\0');
      iVar3 = 0x21 - (int)in_EAX;
      do {
        cVar2 = *in_EAX;
        in_EAX[(int)puVar4 + iVar3] = cVar2;
        in_EAX = in_EAX + 1;
      } while (cVar2 != '\0');
      iVar3 = 0x41 - (int)param_7;
      do {
        cVar2 = *param_7;
        param_7[(int)puVar4 + iVar3] = cVar2;
        param_7 = param_7 + 1;
      } while (cVar2 != '\0');
      *(short *)((int)puVar4 + 0x2e) = param_5 + 4;
      *(undefined4 *)((int)puVar4 + 0x31) = *param_6;
      *(undefined4 *)((int)puVar4 + 0x35) = param_6[1];
      *(undefined4 *)((int)puVar4 + 0x39) = param_6[2];
      *(undefined4 *)((int)puVar4 + 0x3d) = param_6[3];
      cVar2 = RegisterActiveObject(0, 0, (undefined4 *)0);
      if (cVar2 != '\0') {
        iVar3 = *(int *)(param_2 + 0xc10) + 1;
        *(int *)(param_2 + 0xc10) = iVar3;
        piVar5 = DAT_00e53c44;
        if (DAT_00e53c44 != (int *)0x0) {
          while( true ) {
            piVar1 = (int *)*piVar5;
            if ((*(int *)(piVar5[2] + 0x20) == 0) && (*(int *)(piVar5[2] + 0x24) == 20000)) break;
            piVar5 = piVar1;
            if (piVar1 == (int *)0x0) {
              return;
            }
          }
          Widget_SetChildRange(iVar3,7);
          return;
        }
      }
    }
  }
  else if (param_3 != '\0') {
    iVar6 = iVar3 - (int)param_1;
    do {
      cVar2 = *param_1;
      param_1[iVar6 + 0x18] = cVar2;
      param_1 = param_1 + 1;
    } while (cVar2 != '\0');
    iVar6 = iVar3 - (int)in_EAX;
    do {
      cVar2 = *in_EAX;
      in_EAX[iVar6 + 0x21] = cVar2;
      in_EAX = in_EAX + 1;
    } while (cVar2 != '\0');
    *(short *)(iVar3 + 0x2e) = param_5 + 4;
    *(undefined4 *)(iVar3 + 0x31) = *param_6;
    *(undefined4 *)(iVar3 + 0x35) = param_6[1];
    *(undefined4 *)(iVar3 + 0x39) = param_6[2];
    *(undefined4 *)(iVar3 + 0x3d) = param_6[3];
  }
  return;
}

