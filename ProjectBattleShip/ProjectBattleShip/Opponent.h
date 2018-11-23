#ifndef OPPONENT_H_
#define OPPONENT_H_

#include "OpponentStates.h"
#include "BattleshipOpponent.h"
#include "ProbabilityAI.h"

ProbabilityAI * EnemyAI = new ProbabilityAI(&OpponentStartState);

#endif
