/* LZHUFInsertNode - 0x004e9e90 in the original binary.
 *
 * NAMED (batch 36). Classic LZSS InsertNode(r) (Okumura/Yoshizaki LZHUF):
 * inserts the string at ring position r into the binary match tree and
 * records the longest match. The LZHUF state is in EAX and the node r in
 * ESI (both dropped register arguments; every caller loads them).
 *
 * Evidence is outside the body. Its sibling LZHUFDeleteNode (0x4ea010) uses
 * the same state arrays - lson +0x104c, rson +0x5050, dad +0x9454, NIL =
 * 0x1000 - and EncodeLZHUFBlock drives them as the standard LZSS encoder
 * loop: the four call sites at 0x4ea952, 0x4ea966, 0x4eaadd and 0x4eab34
 * pass EAX = the state (ebp) and ESI = the ring position, first priming
 * the tree with r = 0xfc3 downward (N - F = 4096 - 60 - 1 down to 0xf88)
 * then once per consumed byte, with DeleteNode before the replacement.
 * Constants match LZHUF.C: N = 4096, F = 60 (0x3c, the compare limit),
 * THRESHOLD = 2, and match_position/match_length at state +0x1044/+0x1048.
 *
 * EAX (state) and ESI (node) are now the two parameters, in that order. All
 * four callers load them at the call (0x4ea950 mov eax,ebp / esi = the
 * 0xfc3..0xf88 counter; 0x4ea961 esi = 0xfc4; 0x4eaad3/0x4eaadd and
 * 0x4eab32/0x4eab34 mov eax,ebp / esi = the advanced ring position r).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void LZHUFInsertNode(int in_EAX,int unaff_ESI)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  bVar1 = *(byte *)(unaff_ESI + 8 + in_EAX);
  *(undefined4 *)(in_EAX + 0x104c + unaff_ESI * 4) = 0x1000;
  *(undefined4 *)(in_EAX + 0x5050 + unaff_ESI * 4) = 0x1000;
  iVar5 = 1;
  iVar3 = bVar1 + 0x1001;
  *(undefined4 *)(in_EAX + 0x1048) = 0;
  do {
    if (iVar5 < 0) {
      iVar5 = *(int *)(in_EAX + 0x104c + iVar3 * 4);
      if (iVar5 == 0x1000) {
        *(int *)(in_EAX + 0x104c + iVar3 * 4) = unaff_ESI;
        *(int *)(in_EAX + 0x9454 + unaff_ESI * 4) = iVar3;
        return;
      }
    }
    else {
      iVar5 = *(int *)(in_EAX + 0x5050 + iVar3 * 4);
      if (iVar5 == 0x1000) {
        *(int *)(in_EAX + 0x5050 + iVar3 * 4) = unaff_ESI;
        *(int *)(in_EAX + 0x9454 + unaff_ESI * 4) = iVar3;
        return;
      }
    }
    iVar3 = iVar5;
    uVar4 = 1;
    do {
      iVar5 = (uint)*(byte *)(uVar4 + unaff_ESI + 8 + in_EAX) -
              (uint)*(byte *)(iVar3 + 8 + in_EAX + uVar4);
      if (iVar5 != 0) break;
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < 0x3c);
    if (2 < (int)uVar4) {
      uVar2 = *(uint *)(in_EAX + 0x1048);
      if (*(uint *)(in_EAX + 0x1048) < uVar4) {
        *(uint *)(in_EAX + 0x1044) = (unaff_ESI - iVar3 & 0xfffU) - 1;
        *(uint *)(in_EAX + 0x1048) = uVar4;
        uVar2 = uVar4;
        if (0x3b < uVar4) {
          *(undefined4 *)(in_EAX + 0x9454 + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4);
          *(undefined4 *)(in_EAX + 0x104c + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x104c + iVar3 * 4);
          *(undefined4 *)(in_EAX + 0x5050 + unaff_ESI * 4) =
               *(undefined4 *)(in_EAX + 0x5050 + iVar3 * 4);
          *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x104c + iVar3 * 4) * 4) = unaff_ESI;
          *(int *)(in_EAX + 0x9454 + *(int *)(in_EAX + 0x5050 + iVar3 * 4) * 4) = unaff_ESI;
          iVar5 = *(int *)(in_EAX + 0x9454 + iVar3 * 4);
          if (*(int *)(in_EAX + 0x5050 + iVar5 * 4) != iVar3) {
            *(int *)(in_EAX + 0x104c + iVar5 * 4) = unaff_ESI;
            *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4) = 0x1000;
            return;
          }
          *(int *)(in_EAX + 0x5050 + iVar5 * 4) = unaff_ESI;
          *(undefined4 *)(in_EAX + 0x9454 + iVar3 * 4) = 0x1000;
          return;
        }
      }
      if ((uVar4 == uVar2) &&
         (uVar4 = (unaff_ESI - iVar3 & 0xfffU) - 1, uVar4 < *(uint *)(in_EAX + 0x1044))) {
        *(uint *)(in_EAX + 0x1044) = uVar4;
      }
    }
  } while( true );
}

