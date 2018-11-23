#include "ProbabilityAI.h"
#include "OpponentStates.h"

ProbabilityAI::ProbabilityAI(State<BattleShipOpponent> * start)
    : AIStateMachine()
{
    this->SetCurrentState(start);
}

Coordinates ProbabilityAI::Execute(BattleShipOpponent * owner)
{
    this->GetCurrentState()->Execute(owner);
    return owner->GetAttackSequence().back();
}

void ProbabilityAI::Update(AttackResult result, BattleShipOpponent * owner)
{
    if (result == AttackResult::Hit)
    {
        if (this->GetCurrentState()->StateId() == SearchStateId)
        {
            this->ChangeState(&OpponentAttackState, owner);
        }
    }

    if (result == AttackResult::Miss)
    {

    }

    if (result == AttackResult::Sunk)
    {
        if (this->GetCurrentState()->StateId() == AttackStateId)
        {
            this->ChangeState(&OpponentSearchState, owner);
        }
    }
}