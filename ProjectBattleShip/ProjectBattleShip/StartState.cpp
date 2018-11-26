#include "StartState.h"
#include "BattleshipOpponent.h"

#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
#include <array>
#include <functional>

static std::vector<OpponentAction> actions = {
      OpponentAction::MoveDown
    , OpponentAction::MoveLeft
    , OpponentAction::MoveRight
    , OpponentAction::MoveUp
    , OpponentAction::RotateShip
    , OpponentAction::PlaceShip
};

using std::chrono::milliseconds;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

std::array<int, 653> seed_;
std::random_device rdev;
bool seeded = false;
static std::mt19937 generator;
std::uniform_int_distribution<int> distribution(1, actions.size());

OpponentAction ChooseAction();


void StartState::Enter(std::shared_ptr<BattleShipOpponent> entity)
{

}

void StartState::Execute(std::shared_ptr<BattleShipOpponent> entity)
{
    OpponentAction action = ChooseAction();
    if (action == OpponentAction::PlaceShip)
    {
        entity->placed_ships++;
    }
    entity->AddAction(action, Coordinates());
}

void StartState::Exit(std::shared_ptr<BattleShipOpponent> entity)
{
}

OpponentAction ChooseAction()
{
    if (!seeded)
    {
        std::generate_n(seed_.data(), seed_.size(), std::ref(rdev));
        std::seed_seq seed(std::begin(seed_), std::end(seed_));
        generator.seed(seed);
        seeded = true;
    }
    int choice = distribution(generator);
    return actions[choice - 1];
}