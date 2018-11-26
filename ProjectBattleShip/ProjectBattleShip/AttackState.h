#ifndef OPPONENT_ATTACK_STATE_H_
#define OPPONENT_ATTACK_STATE_H_

#include"HitProbability.h"
#include"State.h"
#include<vector>
#include<set>

class BattleShipOpponent;

constexpr char AttackStateId[] = "AttackState";

class Attack : public State<BattleShipOpponent>
{
private:
    std::shared_ptr<IProbability<int, Coordinates>> probability;

    std::vector<Coordinates> find_neighbors(
        Coordinates const & position,
        std::vector<Coordinates> const & hits,
        std::vector<Coordinates> const & traversed);

public:
    Attack(std::shared_ptr<IProbability<int, Coordinates>> probability)
        : State(AttackStateId)
    {
        this->probability = probability;
    }

    virtual ~Attack() {}

    Attack(const Attack&);
    Attack& operator=(const Attack&);

    virtual void Enter(BattleShipOpponent* entity);
    virtual void Execute(BattleShipOpponent* entity);
    virtual void Exit(BattleShipOpponent* entity);
};

#endif