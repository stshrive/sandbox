#ifndef BATTLESHIP_STATES
#define BATTLESHIP_STATES

#include"ProbabilityDensity.h"
#include"BaseState.h"

class BattleShipOpponent;

class Attack : public State<BattleShipOpponent>
{
private:
	Attack(){};
	Attack(const Attack&);
	Attack& operator=(const Attack&);

public:
	//~Attack();
	static Attack* instance();
	virtual void Enter(BattleShipOpponent* entity);
	virtual void Execute(BattleShipOpponent* entity);
	virtual void Exit(BattleShipOpponent* entity);
};

class Search : public State<BattleShipOpponent>
{
private:
	Search(){};
	Search(const Search&);
	Search& operator=(const Search&);

public:
	//~Search();
	static Search* instance();
	virtual void Enter(BattleShipOpponent* entity);
	virtual void Execute(BattleShipOpponent* entity);
	virtual void Exit(BattleShipOpponent* entity);
};

#endif