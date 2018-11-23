#include "BattleshipOpponent.h"
#include "SearchState.h"
#include <vector>
#include <random>

void Search::Enter(BattleShipOpponent* entity)
{
}

void Search::Execute(BattleShipOpponent* entity)
{
    std::vector<Coordinates> choices;

    int high_probability = 0;
    int curr_probability = 0;

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            XY p;
            p.x = x;
            p.y = y;

            bool skip = false;

            for (XY coord : entity->GetAttackSequence())
            {
                if (coord == p) skip = true;
                if (skip) break;
            }

            if (skip)
            {
                continue;
            }

            curr_probability = this->probability->GetProbability(p);

            if (curr_probability > high_probability)
            {
                choices.clear();
                high_probability = curr_probability;
            }

            if (curr_probability == high_probability)
            {
                choices.push_back(p);
            }
        }
    }

    Coordinates choice = choices[Choose(choices)];
    this->probability->Update(choice);

    entity->AddAttackChoice(choice);
}

void Search::Exit(BattleShipOpponent* entity)
{
}

std::vector<Coordinates>::size_type Search::Choose(
    std::vector<Coordinates> choices)
{
    std::vector<Coordinates>::size_type size = choices.size();
    std::vector<Coordinates>::size_type divisor = (RAND_MAX + 1) / size;

    std::vector<Coordinates>::size_type position;
    do { position = std::rand() / divisor; } while (position > size);

    return position;
}