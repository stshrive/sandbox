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

    virtual void Enter  (std::shared_ptr<BattleShipOpponent> entity);
    virtual void Execute(std::shared_ptr<BattleShipOpponent> entity);
    virtual void Exit   (std::shared_ptr<BattleShipOpponent> entity);
};

#endif