#ifndef PROBABILITY_AI_H_
#define PROBABILITY_AI_H_

#include "AIStateMachine.h"
#include "BattleShipOpponent.h"

#include <utility>

class ProbabilityAI
    : public AIStateMachine
    < BattleShipOpponent,
      std::pair<OpponentAction, Coordinates>,
      AttackResult>
{
public:
    ProbabilityAI(State<BattleShipOpponent> * start);

    virtual std::pair<OpponentAction, Coordinates> Execute(
        BattleShipOpponent *);
    
    virtual void Update(AttackResult, BattleShipOpponent *);
};

#endif