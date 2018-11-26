#include"BattleshipOpponent.h"
#include"tiledefs.h"
#include"MapComponents.h"
#include"AIModule.h"

#include "Ships.h"

#include <map>

BattleShipOpponent::BattleShipOpponent(
    AIModule<BattleShipOpponent, std::pair<OpponentAction, Coordinates>, ActionResult> * ai_module,
    map<int, std::pair<Ship*, bool>> ships,
    int id)
    : BaseEntity(id)
{
    this->ships        = ships;
    this->ai_module    = ai_module;
    this->ship_id      = 0;
    this->placed_ships = 0;
}

BattleShipOpponent::~BattleShipOpponent()
{
    if (this->ai_module)
    {
        delete this->ai_module;
    }
}

void BattleShipOpponent::ReadResult(ActionResult result)
{
    this->action_results.push_back(result);
    this->ai_module->Update(result, this);
}

std::pair<OpponentAction, Coordinates> BattleShipOpponent::GetAction()
{
    return this->ai_module->Execute(this);
}

map<int, std::pair<Ship*, bool>> const & BattleShipOpponent::GetShips()
{
    return this->ships;
}

vector<std::pair<OpponentAction, Coordinates>> const & BattleShipOpponent::GetActionSequence()
{
    return this->action_sequence;
}

void BattleShipOpponent::AddAction(
    OpponentAction action, Coordinates const & coordinates)
{
    this->action_sequence.push_back(std::make_pair(action, coordinates));
}

int BattleShipOpponent::GetShipId()
{
    if (this->placed_ships == this->ships.size())
    {
        return -1;
    }

    return placed_ships;
}