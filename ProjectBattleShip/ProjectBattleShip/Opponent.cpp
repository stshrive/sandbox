#include "MapComponents.h"
#include "ProbabilityAI.h"
#include "HitProbability.h"
#include "OpponentStates.h"
#include "Opponent.h"

std::shared_ptr<IProbability<int, Coordinates>> probability(
    new HitProbability(BOARDSIZE));

std::shared_ptr<StartState > OpponentStartState  = std::make_shared<StartState> ();
std::shared_ptr<SearchState> OpponentSearchState = std::make_shared<SearchState>(probability);
std::shared_ptr<AttackState> OpponentAttackState = std::make_shared<AttackState>(probability);

std::shared_ptr<ProbabilityAI> EnemyAI = std::make_shared<ProbabilityAI>(
        OpponentStartState,
        OpponentSearchState,
        OpponentAttackState);

std::map<int, std::pair<std::shared_ptr<Ship>, bool>> OpponentShips = {
   {0, std::make_pair(std::make_shared<Carrier>(),    false)},
   {1, std::make_pair(std::make_shared<BattleShip>(), false)},
   {2, std::make_pair(std::make_shared<Destroyer>(),  false)},
   {3, std::make_pair(std::make_shared<Submarine>(),  false)},
   {4, std::make_pair(std::make_shared<Patroller>(),  false)}
};


std::shared_ptr<BattleShipOpponent> Opponent = std::make_shared<BattleShipOpponent>(
    EnemyAI,
    OpponentShips,
    1);