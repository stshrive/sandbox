#ifndef OPPONENT_H_
#define OPPONENT_H_

#include "BattleshipOpponent.h"
#include "ProbabilityAI.h"
#include "Ships.h"

extern std::shared_ptr<ProbabilityAI> EnemyAI;
extern std::map<int, std::pair<std::shared_ptr<Ship>, bool>> OpponentShips;
extern std::shared_ptr<BattleShipOpponent> Opponent;

#endif
