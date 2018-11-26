#ifndef OPPONENT_ATTACK_STATE_H_
#define OPPONENT_ATTACK_STATE_H_

#include "HitProbability.h"
#include "State.h"
#include <vector>

class BattleShipOpponent;

constexpr char AttackStateId[] = "AttackState";

class AttackState : public State<BattleShipOpponent>
{
private:
    std::shared_ptr<IProbability<int, Coordinates>> probability;

    std::vector<Coordinates> find_neighbors(
        Coordinates const & position,
        std::vector<Coordinates> const & hits,
        std::vector<Coordinates> const & traversed,
        std::vector<Coordinates> const & choices);

public:
    AttackState(std::shared_ptr<IProbability<int, Coordinates>> probability)
        : State(AttackStateId)
    {
        this->probability = probability;
    }

    virtual ~AttackState() {}

    AttackState(const AttackState&);
    AttackState& operator=(const AttackState&);

    virtual void Enter  (std::shared_ptr<BattleShipOpponent> entity);
    virtual void Execute(std::shared_ptr<BattleShipOpponent> entity);
    virtual void Exit   (std::shared_ptr<BattleShipOpponent> entity);
};

#endif