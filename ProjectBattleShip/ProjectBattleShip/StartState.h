#ifndef OPPONENT_START_STATE_H_
#define OPPONENT_START_STATE_H_

#include "State.h"

class BattleShipOpponent;

constexpr char StartStateId[] = "StartState";

class StartState : public State<BattleShipOpponent>
{
public:
    StartState() 
        : State(StartStateId)
    {}

    StartState(const StartState&);
    StartState& operator=(const StartState&);

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif