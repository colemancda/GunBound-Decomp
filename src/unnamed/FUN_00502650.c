/* FUN_00502650 - 0x00502650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ABI (2026-11-05), from the disassembly: `ret 0x14` with the stack
 * arguments read at [ebp+8..+0x18] = (session, name count, name array,
 * payload, payload length), plus two REGISTER arguments Ghidra dropped:
 * CL (0x502689 `mov [esp+0x10],cl`) is the frame's byte 0, and DX (0x502695
 * `mov [esp+0x11],dx`) is its word at +1; the clamped payload length is
 * the word at +3 (0x50268d `mov [esp+0x13],ax`) and the payload starts at
 * +5 (0x5026a1 `lea edi,[esp+0x15]`). Every caller sets them just before
 * the call (0x4fcf59/0x4fcf5b, 0x4fd019/0x4fd01b, 0x504848/0x50484a):
 * `mov cl,al` (AL = FUN_004fd030's classifier result for the message type)
 * and `mov edx,<message type>`. They are promoted to trailing parameters
 * regEcx and regEdx, the header is now actually written (the old port left
 * those five bytes uninitialised), and the staged packet is a real byte
 * array instead of a pointer reached through `&local_2ee3 - 5`.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint FUN_00502650(int param_1,int param_2,int param_3,undefined4 *param_4,uint param_5,
                  unsigned char regEcx,unsigned short regEdx)

{
  uint uVar1;
  uint uVar2;
  char *_Dest;
  undefined4 *puVar3;
  int iVar4;
  unsigned char frame[0x800];  /* 5 header bytes + payload (<= 0xff) + count + names */
  undefined1 local_1778 [5996];
  undefined4 uStack_c;
  
  uStack_c = 0x502660;
  if (0xff < (ushort)param_5) {
    param_5 = 0xff;
  }
  if (0 < param_2) {
    if (100 < param_2) {
      param_2 = 100;
    }
    uVar1 = param_5 & 0xffff;
    frame[0] = regEcx;
    *(unsigned short *)(frame + 1) = regEdx;
    *(unsigned short *)(frame + 3) = (unsigned short)param_5;
    puVar3 = (undefined4 *)(frame + 5);
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = *param_4;
      param_4 = param_4 + 1;
      puVar3 = puVar3 + 1;
    }
    for (param_5 = param_5 & 3; param_5 != 0; param_5 = param_5 - 1) {
      *(undefined1 *)puVar3 = *(undefined1 *)param_4;
      param_4 = (undefined4 *)((int)param_4 + 1);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
    *(short *)(frame + 5 + uVar1) = (short)param_2;
    _Dest = (char *)(frame + 5 + uVar1 + 2);
    if (0 < param_2) {
      iVar4 = 0;
      do {
        _strncpy(_Dest,*(char **)(param_3 + iVar4 * 4),0x10);
        _Dest = _Dest + 0x10;
        iVar4 = iVar4 + 1;
      } while (iVar4 < param_2);
    }
    /* RECOVERED (2026-07-19), orig 0x5026da-0x502714. The staged packet starts
     * at [esp+0x10] (frame anchored on `lea edi,[esp+0x15]` at 0x5026a1 =
     * the staged payload, so the struct base is 5 bytes earlier - the port's
     * Ghidra locals did not name the 5 header bytes at [esp+0x10..0x14];
     * it is now the `frame` array):
     *   push 0x1770 / lea eax,[esp+0x1784] / push eax ; capacity, output=local_1778
     *   push ecx (=[ebx+0x1a78])                      ; schedule
     *   lea ecx,[esp+0x1c]                            ; ECX = INPUT = struct base
     *   lea edx,[esp+0x10] / sub esi,edx / add esi,0xb / imul 0x2aaaaaab
     *                                                 ; EAX = INPUTLEN =
     *                                                 ;   ((esi-base+0xb)/0xc)*0xc
     * where esi is the running write cursor - the port's `_Dest`. */
    param_5 = EncodeP2PPacketBlocks(*(undefined4 *)(param_1 + 0x1a78),(int)local_1778,6000,
                           frame,
                           (((int)(_Dest - (char *)frame) + 0xb) / 0xc) * 0xc);
    if ((char)param_5 != '\0') {
      /* opcode -> stack param; EDX=local_1778 (the ciphertext just written),
       * EBX=param_1 (the session, reloaded `mov ebx,[ebp+8]` at 0x5026da),
       * and ECX = the ENCODED length = blockcount*0x10 where blockcount =
       * ((_Dest - framebase) + 0xb)/0xc - the same plaintext span the encode
       * rounded to *0xc above, re-expanded 12->16 per cipher block.
       * orig 0x50272b-0x50273c: mov ecx,esi / shl ecx,4 / push 0x2020. */
      uVar1 = CommP2POwner_SendFrame((((int)(_Dest - (char *)frame) + 0xb) / 0xc) * 0x10,
                           (undefined4 *)local_1778,0x2020,param_1);
      return uVar1;
    }
  }
  return param_5 & 0xffffff00;
}

