/* BattleAnnouncement_Construct - 0x004b3b10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence: its one caller, SpawnBattleAnnouncement, operator_new's 0x58
 * bytes and runs this on them (call at 0x4383ed), then stores its frame
 * index into the object at +0x44 and hands it to RegisterActiveObject.
 * SpawnBattleAnnouncement's header ties the object to class id 0x2e635 of
 * the battle entity registry, whose draw path (slot 3) feeds the
 * "yesoori.img" banner frames; this function stamps exactly that id at +4
 * and the vtable 0x5566c0 at +0, and zeroes the +0x14 kill byte, the
 * +0x44 frame cell and the +0x48/+0x4c/+0x50 rotation/size/alpha cells
 * the Tick and Draw use (+0x48 = 0x100). The noun is therefore the
 * battle announcement banner.
 *
 * Calling convention (checked at 0x4383e6-0x4383f2): the new object
 * arrives in EAX and is left there; the body never writes EAX, and the
 * caller continues with `mov edi,eax` and `mov [eax+0x44],esi`, so the
 * constructor returns the object. The port used to be void(void) with
 * the caller discarding the pointer (its object variable was never set on
 * the success path); it now takes the object and returns it.
 */
#include "ghidra_types.h"


undefined4 *BattleAnnouncement_Construct(undefined4 *in_EAX)

{
  in_EAX[1] = 0x2e635;
  in_EAX[2] = 0;
  in_EAX[3] = 0;
  in_EAX[4] = 0;
  *(undefined1 *)(in_EAX + 5) = 0;
  *(undefined1 *)((int)in_EAX + 0x15) = 0;
  in_EAX[6] = 0xffffffff;
  in_EAX[7] = 0;
  *(undefined1 *)(in_EAX + 8) = 0;
  in_EAX[10] = 0;
  in_EAX[0xb] = 0;
  in_EAX[9] = 0xffffffff;
  *in_EAX = &PTR_FUN_005566c0;
  in_EAX[0x11] = 0;
  in_EAX[0x12] = 0x100;
  in_EAX[0x13] = 0;
  in_EAX[0x14] = 0;
  in_EAX[0x15] = 0;
  in_EAX[0x10] = 0;
  return in_EAX;
}

