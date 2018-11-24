#include "ProbabilityAI.h"
#include "OpponentStates.h"

ProbabilityAI::ProbabilityAI(State<BattleShipOpponent> * start)
    : AIStateMachine()
{
    this->SetCurrentState(start);
}

std::pair<OpponentAction, Coordinates> ProbabilityAI::Execute(BattleShipOpponent * owner)
{
    this->GetCurrentState()->Execute(owner);
    return owner->GetActionSequence().back();
}

void ProbabilityAI::Update(ActionResult result, BattleShipOpponent * owner)
{
    if (result == ActionResult::Hit)
    {
        if (this->GetCurrentState()->StateId() == SearchStateId)
        {
            this->ChangeState(&OpponentAttackState, owner);
        }
    }

    if (result == ActionResult::Begin)
    {
        if (this->GetCurrentState()->StateId() == StartStateId)
        {
            this->ChangeState(&OpponentSearchState, owner);
        }
    }

    if (result == ActionResult::Sunk)
    {
        if (this->GetCurrentState()->StateId() == AttackStateId)
        {
            this->ChangeState(&OpponentSearchState, owner);
        }
    }
}