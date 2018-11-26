#ifndef OPPONENT_SEARCH_STATE_H_
#define OPPONENT_SEARCH_STATE_H_

#include"HitProbability.h"
#include"State.h"

#include <vector>

class BattleShipOpponent;

constexpr char SearchStateId[] = "SearchState";

class Search : public State<BattleShipOpponent>
{
private:
    IProbability<int, Coordinates> * probability;

    std::vector<Coordinates>::size_type Choose(
        std::vector<Coordinates> choices);

public:
    Search(IProbability<int, Coordinates> * probability)
        : State(SearchStateId)
    {
        this->probability = probability;
    }

    virtual ~Search() {}

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif