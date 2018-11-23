#include "StartState.h"
#include "BattleshipOpponent.h"

#include <random>
#include <vector>

void Start::Enter(BattleShipOpponent* entity)
{

}

void Start::Execute(BattleShipOpponent* entity)
{
    std::vector<OpponentAction> actions;
    for (int i = 2; i <= 64; i *= 2)
    {
        actions.push_back(static_cast<OpponentAction>(i));
    }

    std::random_shuffle(actions.begin(), actions.end());
    entity->AddAction(actions.front(), Coordinates());
}

void Start::Exit(BattleShipOpponent* entity)
{
}