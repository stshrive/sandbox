#include"BattleshipOpponent.h"
#include"tiledefs.h"
#include"MapComponents.h"
#include"AIModule.h"

#include "Ships.h"

#include <map>

BattleShipOpponent::BattleShipOpponent(
    std::shared_ptr<AIModule<BattleShipOpponent, std::pair<OpponentAction, Coordinates>,
        ActionResult>> ai_module,
    std::map<int, std::pair<std::shared_ptr<Ship>, bool>> ships,
    int id)
    : BaseEntity(id)
{
    this->ships        = ships;
    this->ai_module    = ai_module;
    this->ship_id      = 0;
    this->placed_ships = 0;
}

BattleShipOpponent::BattleShipOpponent(BattleShipOpponent const &other)
{
    this->ships        = other.ships;
    this->ai_module    = other.ai_module;
    this->ship_id      = other.ship_id;
    this->placed_ships = other.placed_ships;
}

BattleShipOpponent::BattleShipOpponent(BattleShipOpponent && other)
{ 
    this->ships        = std::move(other.ships);
    this->ai_module    = std::move(other.ai_module);
    this->ship_id      = std::move(other.ship_id);
    this->placed_ships = std::move(other.placed_ships);
}

BattleShipOpponent::~BattleShipOpponent()
{
}

void BattleShipOpponent::ReadResult(ActionResult result)
{
    this->action_results.push_back(result);
    this->ai_module->Update(
        result,
        std::shared_ptr<BattleShipOpponent>(this->shared_from_this()));
}

std::pair<OpponentAction, Coordinates> BattleShipOpponent::GetAction()
{
    auto value = this->ai_module->Execute(this->shared_from_this());

    return value;
}

std::map<int, std::pair<std::shared_ptr<Ship>, bool>> const & BattleShipOpponent::GetShips()
{
    return this->ships;
}

std::vector<std::pair<OpponentAction, Coordinates>> const & BattleShipOpponent::GetActionSequence()
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