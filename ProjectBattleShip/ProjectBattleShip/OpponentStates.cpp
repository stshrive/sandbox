#include "OpponentStates.h"
#include "HitProbability.h"

#include "MapComponents.h"

std::shared_ptr<IProbability<int, Coordinates>> probability(
    new HitProbability(BOARDSIZE));

Start  OpponentStartState;
Search OpponentSearchState(probability);
Attack OpponentAttackState(probability);