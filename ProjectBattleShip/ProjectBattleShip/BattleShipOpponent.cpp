#include"BattleshipOpponent.h"
#include"tiledefs.h"
#include"MapComponents.h"
#include"AIModule.h"

#include <vector>

BattleShipOpponent::BattleShipOpponent(
    AIModule<BattleShipOpponent, Coordinates, AttackResult>  * ai_module,
    int id
) : BaseEntity(id)
{
    this->ai_module = ai_module;
}

BattleShipOpponent::~BattleShipOpponent()
{
    if (this->ai_module)
    {
        delete this->ai_module;
    }
}

void BattleShipOpponent::ReadResult(AttackResult result)
{
    this->ai_module->Update(result, this);
}

XY BattleShipOpponent::GetChoice()
{
    return this->ai_module->Execute(this);
}

vector<Coordinates> const & BattleShipOpponent::GetAttackSequence()
{
    return this->attack_sequence;
}

void BattleShipOpponent::AddAttackChoice(Coordinates const & coordinates)
{
    this->attack_sequence.push_back(coordinates);
}