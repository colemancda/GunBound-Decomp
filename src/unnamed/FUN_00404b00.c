/* FUN_00404b00 - 0x00404b00 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): EBX is the name-keyed lookup
 * tree this function searches - the container that lives at (owner object
 * base + 0x1be4).  It is read before any write: 0x404b00 `mov
 * eax,[ebx+0x14]` is the very first instruction, and nothing in the body
 * ever assigns EBX.  Two of its fields are used - *EBX is the root node
 * (0x404b09 `mov esi,[ebx]`) and EBX[5] at +0x14 is the nil/end sentinel
 * that terminates the descent - while the nodes hold a char key pointer
 * at +0x00 (compared with __mbsicmp) and children at +0x108 and +0x10c.
 * EBX is also handed straight to FUN_00405040 as its stack argument
 * (`push ebx` at 0x404b4b, `mov eax,edi`, `call 0x405040`), the tree's
 * in-order successor, so the tail loop walks forward and returns the LAST
 * node whose key still matches.
 *
 * `ret 4` at 0x404b48 and 0x404b85 matches the one declared stack
 * parameter exactly, so this is a clean APPEND, not a re-slot.
 *
 * All 13 ported call sites carry the same object field, in three shapes.
 * Ten sit in callers that hold the object base directly: four do
 * `add ebx,0x1be4` (0x40285a, 0x402a24, 0x402c46, 0x4032a3), four do
 * `lea ebx,[base+0x1be4]` (0x402dc1, 0x402f43, 0x4045b1, 0x4047f3), and
 * two do `mov ebx,esi` where ESI was formed by `add esi,0x1be4` at
 * 0x403185 and reloaded from its spill slot at 0x403218 (0x40318c,
 * 0x403242).  The other three - FUN_00403ae0, FUN_00403d20 and
 * FUN_00404330 - are __thiscall on a pointer 8 bytes into that same
 * object and do `lea ebx,[this+0x1bdc]` (0x403b61, 0x403d78, 0x404383),
 * which is the identical address.
 *
 * The +8 relation is not assumed, it is measured.  FUN_004026a0
 * post-increments a sequence counter at (its EBX + 0x1be0), and it is
 * reached with `lea ebx,[ebp-8]` from the this-based FUN_00403ae0
 * (0x403be7) but with `mov ebx,ebp` from the base-holding FUN_00402cf0
 * (0x402e47).  So base + 0x1be0 == this - 8 + 0x1be0, hence this ==
 * base + 8 and this + 0x1bdc == base + 0x1be4.  The neighbouring field
 * confirms the layout too: base + 0x1bdc is the listener interface the
 * BASE-holding callers null-check, at 0x402d7f, 0x4029d4, 0x40456a and
 * 0x4047ab - not a field the three this-based callers touch.
 *
 * The other 3 of the 16 binary sites (0x403e8b, 0x4040a6, 0x4041fc) fall
 * in address gaps between PROGRESS.csv entries (0x403e07-0x403f30 and
 * 0x403fea-0x404330), i.e. in code that is not ported, so 16 = 13 + 3
 * reconciles.
 *
 * Two callers had to gain a parameter of their own first.  Both have ZERO
 * call sites in the ported tree (FUN_00403d20 has none in the binary
 * either; its lone PROGRESS.csv xref is a data reference), so widening
 * them cannot break a caller:
 * FUN_00403270 - `ret 4` at 0x4032b8 against a declared list holding
 * only the ECX parameter, so one stack argument was dropped; it is
 * read at 0x40329a as `mov ebx,[esp+0x20]`, which with frame 0x1c
 * (sub esp,0x18 + push ebx) is entry_esp+4.  Added as param_2.  Under
 * MSVC __fastcall that lands in EDX rather than on the stack as in the
 * original - unobservable with no callers, but a future porter of
 * 0x403c80 must not assume the positions mirror the original.  Its
 * EAX (the name string, in_EAX) is still missing - separate item.
 * FUN_00403d20 - ECX is a live-in: `mov ebp,ecx` at 0x403d2e, before
 * ECX is reloaded at 0x403d30.  It is the `this` of the __thiscall
 * twin FUN_00404330, which Ghidra typed correctly.  Added as a
 * trailing regEcx.  Its `ret 0xc` also implies a third stack
 * parameter at entry+0xc that no instruction reads (both +4 and +8
 * are read, at 0x403d26 and 0x403d42 / 0x403de5); left undeclared.
 */
#include "ghidra_types.h"


undefined4 * FUN_00404b00(uchar *param_1,int *regEbx)

{
  int iVar1;
  undefined4 *puVar2;
  int *unaff_EBX = regEbx;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar2 = (undefined4 *)*unaff_EBX;
  puVar3 = (undefined4 *)0x0;
  if (puVar2 != (undefined4 *)unaff_EBX[5]) {
    do {
      puVar4 = puVar3;
      if (puVar3 != (undefined4 *)0x0) goto LAB_00404b4b;
      iVar1 = __mbsicmp(param_1,(uchar *)*puVar2);
      puVar4 = puVar2;
      if (iVar1 != 0) {
        if (iVar1 < 0) {
          puVar2 = (undefined4 *)puVar2[0x42];
          puVar4 = puVar3;
        }
        else {
          puVar2 = (undefined4 *)puVar2[0x43];
          puVar4 = puVar3;
        }
      }
      puVar3 = puVar4;
    } while (puVar2 != (undefined4 *)unaff_EBX[5]);
    if (puVar4 != (undefined4 *)0x0) {
LAB_00404b4b:
      puVar2 = (undefined4 *)FUN_00405040(unaff_EBX,puVar4);
      while ((puVar3 = puVar2, puVar3 != (undefined4 *)0x0 &&
             (iVar1 = __mbsicmp(param_1,(uchar *)*puVar3), iVar1 == 0))) {
        puVar2 = (undefined4 *)FUN_00405040(unaff_EBX,puVar3);
        puVar4 = puVar3;
      }
      return puVar4;
    }
  }
  return (undefined4 *)0x0;
}

