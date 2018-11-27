#ifndef PROBABILITY_AI_H_
#define PROBABILITY_AI_H_

#include "AIStateMachine.h"
#include "BattleShipOpponent.h"

#include <memory>

class ProbabilityAI
    : public AIStateMachine
    < BattleShipOpponent,
      std::pair<OpponentAction, Coordinates>,
      ActionResult>
{
private:
    std::shared_ptr<State<BattleShipOpponent>> Start;
    std::shared_ptr<State<BattleShipOpponent>> Search;
    std::shared_ptr<State<BattleShipOpponent>> Attack;
public:
    ProbabilityAI(
        std::shared_ptr<State<BattleShipOpponent>> start,
        std::shared_ptr<State<BattleShipOpponent>> search,
        std::shared_ptr<State<BattleShipOpponent>> attack);

    virtual std::pair<OpponentAction, Coordinates> Execute(
        std::shared_ptr<BattleShipOpponent> actor);
    
    virtual void Update(
        ActionResult result,
        std::shared_ptr<BattleShipOpponent> actor);
};

#endif