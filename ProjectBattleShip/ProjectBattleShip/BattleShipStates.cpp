#include"BattleShipStates.h"
#include"BattleshipOpponent.h"
#include"MapComponents.h"

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
    entity->CheckProbability();
    XY choice = entity->GetChoice();

}

void Search::Exit(BattleShipOpponent* entity)
{
}