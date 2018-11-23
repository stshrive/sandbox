#ifndef OPPONENT_ATTACK_STATE_H_
#define OPPONENT_ATTACK_STATE_H_

#include"HitProbability.h"
#include"State.h"

class BattleShipOpponent;

constexpr char AttackStateId[] = "AttackState";

class Attack : public State<BattleShipOpponent>
{
public:
    Attack() 
        :State(AttackStateId)
    {}

    Attack(const Attack&);
    Attack& operator=(const Attack&);

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif