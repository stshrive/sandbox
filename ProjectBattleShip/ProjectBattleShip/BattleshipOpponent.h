#ifndef BATTLESHIP_OPPONENT
#define BATTLESHIP_OPPONENT

#include"coord.h"
#include"BaseEntity.h"
#include"BaseState.h"
#include"BattleShipStates.h"
#include"StateMachine.h"
#include"ProbabilityDensity.h"
#include<stack>
#include<queue>
#include<vector>

using std::queue;
using std::stack;
using std::vector;

class AI;

//Beginner
//Easy
//Normal
//Hard

enum AttackResult
{
      Miss = 0
    , Hit  = 1
    , Sunk = 2
};

class BattleShipOpponent : public BaseEntity
{
private:
	StateMachine<BattleShipOpponent>* m_pStateMachine;
	queue<XY> m_qAttackSequence;
	vector<XY> m_sPreviousAttacks;
    AI * ai_module;

    StateMachine<BattleShipOpponent>* getStateMachine() { return m_pStateMachine; }
    virtual void Update();
    void CheckProbability();

public:
    BattleShipOpponent(AI * ai_module, int id);
    virtual ~BattleShipOpponent();

    void ReadResult(AttackResult result);
    virtual XY GetChoice();
};

#endif