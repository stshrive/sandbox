#ifndef BATTLESHIP_OPPONENT
#define BATTLESHIP_OPPONENT

#include "coord.h"
#include "BaseEntity.h"
#include "State.h"
#include "Ships.h"

#include <memory>
#include <vector>
#include <map>
#include <mutex>

template<typename actor_ty_, typename execution_ty_, typename update_ty_>
class AIModule;

class StartState;
class SearchState;
class AttackState;

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

class BattleShipOpponent
    : public BaseEntity
    , public std::enable_shared_from_this<BattleShipOpponent>
{
private:
    int ship_id;
    
    std::mutex critical_section;

    std::map<int, std::pair<std::shared_ptr<Ship>, bool>> ships;
	std::vector<std::pair<OpponentAction, Coordinates>> action_sequence;
    
    std::shared_ptr<AIModule<BattleShipOpponent,
            std::pair<OpponentAction,Coordinates>,
            ActionResult>> ai_module;

    std::vector<ActionResult> action_results;

    friend class StartState;
    friend class AttackState;

protected:
    int placed_ships;

public:
    BattleShipOpponent(
        std::shared_ptr<
            AIModule<BattleShipOpponent,
                std::pair<OpponentAction, Coordinates>,
                ActionResult>>,
        std::map<int, std::pair<std::shared_ptr<Ship>, bool>>,
        int);

    BattleShipOpponent(BattleShipOpponent const &);
    BattleShipOpponent(BattleShipOpponent &&);

    virtual ~BattleShipOpponent();

    void ReadResult(ActionResult result);
    virtual std::pair<OpponentAction, Coordinates> GetAction();

    std::map<int, std::pair<std::shared_ptr<Ship>, bool>> const & GetShips();
    std::vector<std::pair<OpponentAction, Coordinates>> const & GetActionSequence();
    void AddAction(OpponentAction action, Coordinates const & coordinate);
    
    int GetShipId();
};

#endif