#ifndef BATTLESHIP_OPPONENT
#define BATTLESHIP_OPPONENT

#include "coord.h"
#include "BaseEntity.h"
#include "State.h"
#include <vector>

using std::vector;

template<typename owner_ty_, typename execution_ty_, typename update_ty_>
class AIModule;

enum AttackResult
{
      Miss = 0
    , Hit  = 1
    , Sunk = 2
};

class BattleShipOpponent : public BaseEntity
{
private:
	vector<Coordinates> attack_sequence;
    AIModule<BattleShipOpponent, Coordinates, AttackResult> * ai_module;

public:
    BattleShipOpponent(AIModule<BattleShipOpponent, Coordinates, AttackResult>  * ai_module, int id);
    virtual ~BattleShipOpponent();

    void ReadResult(AttackResult result);
    virtual Coordinates GetChoice();

    vector<Coordinates> const & GetAttackSequence();
    void AddAttackChoice(Coordinates const & coordinate);
};

#endif