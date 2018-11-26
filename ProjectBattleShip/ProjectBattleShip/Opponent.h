#ifndef OPPONENT_H_
#define OPPONENT_H_

#include "OpponentStates.h"
#include "BattleshipOpponent.h"
#include "ProbabilityAI.h"

ProbabilityAI * EnemyAI  = new ProbabilityAI(&OpponentStartState);

Carrier    OpponentCarrier;
BattleShip OpponentBattleShip;
Destroyer  OpponentCruiser;
Submarine  OpponentSub;
Patroller  OpponentPatrol;

std::map<int, std::pair<Ship*, bool>> OpponentShips = {
    {0, std::make_pair(&OpponentCarrier,    false)},
    {1, std::make_pair(&OpponentBattleShip, false)},
    {2, std::make_pair(&OpponentCruiser,    false)},
    {3, std::make_pair(&OpponentSub,        false)},
    {4, std::make_pair(&OpponentPatrol,     false)}
};

BattleShipOpponent * Opponent = new BattleShipOpponent(EnemyAI, OpponentShips, 1);

#endif
