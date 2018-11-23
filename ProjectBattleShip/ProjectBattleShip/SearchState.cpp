#include "SearchState.h"

Search* Search::instance()
{
    static Search instance;
    return &instance;
}

void Search::Enter(BattleShipOpponent* entity)
{
}

void Search::Execute(BattleShipOpponent* entity)
{
}

void Search::Exit(BattleShipOpponent* entity)
{
}