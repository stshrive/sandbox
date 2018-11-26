#include "OpponentStates.h"
#include "HitProbability.h"

#include "MapComponents.h"

HitProbability probability(BOARDSIZE);

Start  OpponentStartState;
Search OpponentSearchState(&probability);
Attack OpponentAttackState(&probability);