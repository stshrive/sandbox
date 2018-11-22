#include"BattleshipOpponent.h"
#include"ProbabilityDensity.h"
#include"tiledefs.h"
#include"MapComponents.h"

#include <vector>

#include <random>

std::vector<XY>::size_type choose(std::vector<XY> choices);

BattleShipOpponent::BattleShipOpponent(AI * ai_module, int id):BaseEntity(id),
    m_iParity(2),
    m_iMaxAttacks(5),
    m_bOverMax(false),
    m_bHit(false)
{
    this->ai_module = ai_module;
    m_pStateMachine = new StateMachine<BattleShipOpponent>(this);
    m_pStateMachine->SetCurrentState(Search::instance());
}

BattleShipOpponent::~BattleShipOpponent()
{
    if (m_pStateMachine)
    {
        delete m_pStateMachine;
    }

    if (this->ai_module)
    {
        delete this->ai_module;
    }
}

void BattleShipOpponent::CheckProbability()
{
    std::vector<XY> choices;

    int highest  = 0;
    int tempProb = 0;

	for(int y=0;y<10; y++)
	{
		for(int x = 0;x<10;x++)
		{
            XY p;
            p.x = x;
            p.y = y;

            bool skip = false;

            for (XY coord : this->m_sPreviousAttacks)
            {
                if (coord == p) skip = true;
                if (skip) break;
            }

            if (skip)
            {
                continue;
            }
            
            tempProb = this->ai_module->GetProbability(p);
            if (tempProb > highest)
            {
                choices.clear();
                highest = tempProb;
            }

            if (tempProb == highest)
			{
                choices.push_back(p);
			}
		}
	}

    if (choices.size() > 1)
    {
        m_qAttackSequence.push(choices[choose(choices)]);
    }
    else
    {
        m_qAttackSequence.push(choices[0]);
    }
	
}

void BattleShipOpponent::ReadResult(AttackResult result)
{
}

void BattleShipOpponent::Update()
{
    std::vector<XY>::size_type previous = this->m_sPreviousAttacks.size();
    if (previous)
    {
        this->ai_module->Update(m_sPreviousAttacks.at(previous - 1));
    }
    else
    {
        this->ai_module->Update();
    }
}

XY BattleShipOpponent::GetChoice()
{
    this->CheckProbability();

    auto value = this->m_qAttackSequence.front();
    this->m_sPreviousAttacks.push_back(value);
    this->m_qAttackSequence.pop();

    return value;
}


std::vector<XY>::size_type choose(std::vector<XY> choices)
{
    std::vector<XY>::size_type size    = choices.size();
    std::vector<XY>::size_type divisor = (RAND_MAX + 1) / size;

    std::vector<XY>::size_type position;
    do { position = std::rand() / divisor; } while (position > size);

    return position;
}