#ifndef BATTLESHIP_OPPONENT
#define BATTLESHIP_OPPONENT

#include "coord.h"
#include "BaseEntity.h"
#include "State.h"
#include <vector>
#include <map>

using std::vector;
using std::map;

template<typename owner_ty_, typename execution_ty_, typename update_ty_>
class AIModule;

class Start;
class Search;
class Attack;

class Ship;

enum ActionResult
{
      Miss   = 0
    , Hit    = 1
    , Sunk   = 2
    , Accept = 3
    , Begin  = 4
};

enum OpponentAction
{
      Ready      = 0x000
    , Fire       = 0x001
    , PlaceShip  = 0x10D
    , RotateShip = 0x120
    , MoveLeft   = 0x125
    , MoveUp     = 0x126
    , MoveRight  = 0x127
    , MoveDown   = 0x128
    , MoveFlag   = 0x100
};

class BattleShipOpponent : public BaseEntity
{
private:
    int ship_id;
    map<int, std::pair<Ship*, bool>> ships;
	vector<std::pair<OpponentAction, Coordinates>> action_sequence;
    AIModule<
        BattleShipOpponent,
        std::pair<OpponentAction,Coordinates>,
        ActionResult> * ai_module;

    std::vector<ActionResult> action_results;

    friend class Start;

protected:
    int placed_ships;

public:
    BattleShipOpponent(
        AIModule<BattleShipOpponent, std::pair<OpponentAction, Coordinates>, ActionResult>*,
        map<int, std::pair<Ship*, bool>>,
        int);

    virtual ~BattleShipOpponent();

    void ReadResult(ActionResult result);
    virtual std::pair<OpponentAction, Coordinates> GetAction();

    map<int, std::pair<Ship*, bool>> const & GetShips();
    vector<std::pair<OpponentAction, Coordinates>> const & GetActionSequence();
    void AddAction(OpponentAction action, Coordinates const & coordinate);
    
    int GetShipId();
};

#endif