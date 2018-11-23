#ifndef PROBABILITY_AI_H_
#define PROBABILITY_AI_H_

#include "AIStateMachine.h"
#include "BattleShipOpponent.h"

class ProbabilityAI
    : public AIStateMachine<BattleShipOpponent, Coordinates, AttackResult>
{
public:
    ProbabilityAI(State<BattleShipOpponent> * start);

    virtual Coordinates Execute(BattleShipOpponent *);
    virtual void Update(AttackResult, BattleShipOpponent *);
};

#endif