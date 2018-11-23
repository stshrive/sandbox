#ifndef OPPONENT_SEARCH_STATE_H_
#define OPPONENT_SEARCH_STATE_H_

#include"ProbabilityDensity.h"
#include"BaseState.h"

class BattleShipOpponent;

class Search : public State<BattleShipOpponent>
{
private:
    Search() {};
    Search(const Search&);
    Search& operator=(const Search&);

public:
    static Search* instance();
    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif