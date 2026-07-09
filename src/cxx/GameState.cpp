/* CGameState base bodies - the "shared plumbing" of the state machine.
 * See src/cxx/README.md and ARCHITECTURE.md.
 *
 * The key identification: the binary's CGameState_BaseDestructor
 * (0x426ac0, `*this = &vtable_00553fb0`) is simply the COMPILER-
 * GENERATED body of ~CGameState() - during base destruction MSVC
 * restores the base class's own vtable, so 0x553fb0 IS CGameState's
 * vtable, and the "null-object pattern" states 0/15 are plain base
 * instances whose virtuals are these no-op default bodies.
 * CGameState_ScalarDeletingDestructor (0x4e5320) is likewise the
 * compiler-generated scalar deleting destructor (dtor + conditional
 * free on the low flag bit). Declaring the virtual dtor is all it
 * takes to regenerate both. */
#include "GameState.h"

CGameState::~CGameState()                                   /* 0x426ac0 body; 0x4e5320 deleting form */
{
}

void CGameState::ProcessPacket(int, u16, u16 *)             /* 0x448430 CGameState_NoOpVirtual_A */
{
}

void CGameState::ProcessBattleAction(int, int)              /* 0x4fdef0 CGameState_NoOpVirtual_B */
{
}

void CGameState::v3()                                       /* NoOpVirtual_B binding */
{
}

void CGameState::v4()                                       /* NoOpVirtual_B binding */
{
}

void CGameState::OnKeyInput(int, int, int)
{
}

void CGameState::OnMouseInput(int, int, int)
{
}

void CGameState::OnEnter()
{
}

void CGameState::OnExit()
{
}

void CGameState::OnTick()
{
}
