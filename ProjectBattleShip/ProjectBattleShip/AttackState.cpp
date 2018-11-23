#include "AttackState.h"

Attack* Attack::instance()
{
    static Attack instance;
    return &instance;
}

void Attack::Enter(BattleShipOpponent* entity)
{

}

void Attack::Execute(BattleShipOpponent* entity)
{

}

void Attack::Exit(BattleShipOpponent* entity)
{
}