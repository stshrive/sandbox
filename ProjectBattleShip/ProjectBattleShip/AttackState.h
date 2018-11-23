#ifndef OPPONENT_ATTACK_STATE_H_
#define OPPONENT_ATTACK_STATE_H_

#include"ProbabilityDensity.h"
#include"BaseState.h"

class BattleShipOpponent;

class Attack : public State<BattleShipOpponent>
{
private:
    Attack() {};
    Attack(const Attack&);
    Attack& operator=(const Attack&);

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif