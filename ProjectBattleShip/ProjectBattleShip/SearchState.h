#ifndef OPPONENT_SEARCH_STATE_H_
#define OPPONENT_SEARCH_STATE_H_

#include "Probability.h"
#include "coord.h"
#include "State.h"

#include <memory>
#include <vector>

constexpr char SearchStateId[] = "SearchState";

class SearchState : public State<BattleShipOpponent>
{
private:
    std::shared_ptr<IProbability<int, Coordinates>> probability;

    std::vector<Coordinates>::size_type Choose(
        std::vector<Coordinates> choices);

public:
    SearchState(std::shared_ptr<IProbability<int, Coordinates>> probability)
        : State(SearchStateId)
    {
        this->probability = probability;
    }

    virtual ~SearchState() {}

    virtual void Enter  (std::shared_ptr<BattleShipOpponent> entity);
    virtual void Execute(std::shared_ptr<BattleShipOpponent> entity);
    virtual void Exit   (std::shared_ptr<BattleShipOpponent> entity);
};

#endif