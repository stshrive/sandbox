#ifndef AI_STATE_MACHINE_H
#define AI_STATE_MACHINE_H

#include"AIModule.h"
#include<assert.h>

template <typename Ty_>
class State;

template<class owner_ty_, typename execution_ty_, typename update_ty_>
class AIStateMachine
    : public AIModule<owner_ty_, execution_ty_, update_ty_>
{
private:
	State<owner_ty_> * m_pCurrentState;
	State<owner_ty_> * m_pPreviousState;

protected:
	void SetCurrentState(State<owner_ty_>*  state)
    {
        m_pCurrentState = state;
    }

	void SetPreviousState(State<owner_ty_>* state)
    {
        m_pPreviousState = state;
    }

    void ChangeState(State<owner_ty_>* pNewState, owner_ty_ * owner)
    {
        assert(pNewState && "<AIStateMachine::ChangeState>: trying to change to a NULL state");

        m_pPreviousState = m_pCurrentState;
        m_pCurrentState->Exit(owner);
        m_pCurrentState = pNewState;
        m_pCurrentState->Enter(owner);
    }

    void RevertStates()
    {
        ChangeState(m_pPreviousState);
    }

public:
    AIStateMachine() :
        m_pCurrentState(nullptr),
        m_pPreviousState(nullptr)
    {
    }

    virtual execution_ty_ Execute(owner_ty_ *)   abstract;
    virtual void Update(update_ty_, owner_ty_ *) abstract;

public:
    State<owner_ty_> * GetCurrentState()
    {
        return this->m_pCurrentState;
    }
};

#endif