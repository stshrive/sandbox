#include "AttackState.h"
#include "BattleshipOpponent.h"
#include <queue>
#include <vector>

void AttackState::Enter(std::shared_ptr<BattleShipOpponent> entity)
{

}

void AttackState::Execute(std::shared_ptr<BattleShipOpponent> entity)
{
    std::queue<Coordinates> candidates;

    for (decltype(entity->action_results)::size_type i = entity->action_results.size()-1;
        i < entity->action_results.size();
        --i)
    {
        ActionResult result = entity->action_results[i];

        if (result == ActionResult::Hit)
        {
            candidates.push(entity->action_sequence[i].second);
            break;
        }
    }

    std::vector<Coordinates> choices;
    std::vector<Coordinates> hits;
    std::vector<Coordinates> traversed;

    for (decltype(entity->action_results)::size_type i = entity->action_results.size() - 1;
        i < entity->action_results.size();
        --i)
    {
        ActionResult result = entity->action_results[i];

        if (result == ActionResult::Hit)
        {
            hits.push_back(entity->action_sequence[i].second);
        }
    }

    while (!candidates.empty())
    {
        Coordinates current = candidates.front();
        candidates.pop();
        traversed.push_back(current);

        if (this->probability->GetProbability(current))
        {
            choices.push_back(current);
        }
        else
        {
            for (Coordinates neighbor : this->find_neighbors(current, hits, traversed, choices))
            {
                candidates.push(neighbor);
            }
        }
    }

    std::random_shuffle(choices.begin(), choices.end());
    Coordinates choice = choices.front();

    this->probability->Update(choice);
    entity->AddAction(OpponentAction::Fire, choice);
}

void AttackState::Exit(std::shared_ptr<BattleShipOpponent> entity)
{
}


std::vector<Coordinates> AttackState::find_neighbors(
    Coordinates const & position,
    std::vector<Coordinates> const & hits,
    std::vector<Coordinates> const & traversed,
    std::vector<Coordinates> const & choices)
{
    std::vector<Coordinates> neighbors;
    unsigned x_start = (position.x - 1 > position.x) ? 0 : position.x - 1;
    unsigned y_start = (position.y - 1 > position.y) ? 0 : position.y - 1;

    for (unsigned x = x_start; x <= position.x + 1; ++x)
    {
        for (unsigned y = y_start; y <= position.y + 1; ++y)
        {
            if ((x == position.x || y == position.y)
                && !(x == position.x && y == position.y))
            {
                Coordinates neighbor;
                neighbor.x = x;
                neighbor.y = y;
                if (this->probability->GetProbability(neighbor))
                {
                    neighbors.push_back(neighbor);
                }
                else if (choices.empty())
                {
                    bool seen = false;
                    for (size_t i = 0; i < traversed.size(); ++i)
                    {
                        if (traversed[i].x == neighbor.x && traversed[i].y == neighbor.y)
                        {
                            seen = true;
                            break;
                        }
                    }

                    for (size_t i = 0; i < hits.size() && !seen; ++i)
                    {
                        if (hits[i].x == neighbor.x && hits[i].y == neighbor.y)
                        {
                            neighbors.push_back(neighbor);
                            break;
                        }
                    }
                }
            }
        }
    }

    return neighbors;
}