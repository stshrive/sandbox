#include "ProbabilityAI.h"
#include "OpponentStates.h"

ProbabilityAI::ProbabilityAI(
    std::shared_ptr<State<BattleShipOpponent>> start,
    std::shared_ptr<State<BattleShipOpponent>> search,
    std::shared_ptr<State<BattleShipOpponent>> attack)
    : AIStateMachine()
{
    this->Start  = start;
    this->Search = search;
    this->Attack = attack;

    this->SetCurrentState(start);
}

std::pair<OpponentAction, Coordinates>
ProbabilityAI::Execute(std::shared_ptr<BattleShipOpponent> actor)
{
    this->GetCurrentState()->Execute(actor);
    return actor->GetActionSequence().back();
}

void ProbabilityAI::Update(ActionResult result, std::shared_ptr<BattleShipOpponent> actor)
{
    if (result == ActionResult::Hit)
    {
        if (this->GetCurrentState()->StateId() == SearchStateId)
        {
            this->ChangeState(this->Attack, actor);
            return;
        }
    }

    if (result == ActionResult::Begin)
    {
        if (this->GetCurrentState()->StateId() == StartStateId)
        {
            this->ChangeState(this->Search, actor);
            return;
        }
    }

    if (result == ActionResult::Sunk)
    {
        if (this->GetCurrentState()->StateId() == AttackStateId)
        {
            this->ChangeState(this->Search, actor);
            return;
        }
    }
}