#include "OpponentStates.h"
#include "HitProbability.h"

#include "MapComponents.h"

std::shared_ptr<IProbability<int, Coordinates>> probability(
    new HitProbability(BOARDSIZE));

StartState  OpponentStartState;
SearchState OpponentSearchState(probability);
AttackState OpponentAttackState(probability);