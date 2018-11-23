#ifndef OPPONENT_START_STATE_H_
#define OPPONENT_START_STATE_H_

#include "State.h"

class BattleShipOpponent;

constexpr char StartStateId[] = "StartState";

class Start : public State<BattleShipOpponent>
{
public:
    Start() 
        : State(StartStateId)
    {}

    Start(const Start&);
    Start& operator=(const Start&);

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif