#ifndef AI_STATE_MACHINE_H
#define AI_STATE_MACHINE_H

#include"AIModule.h"
#include<assert.h>
#include<memory>

template <typename Ty_>
class State;

template<class actor_ty_, typename execution_ty_, typename update_ty_>
class AIStateMachine
    : public AIModule<actor_ty_, execution_ty_, update_ty_>
{
private:
	std::shared_ptr< State<actor_ty_> > m_pCurrentState;
	std::shared_ptr< State<actor_ty_> > m_pPreviousState;

protected:
	void SetCurrentState(std::shared_ptr<State<actor_ty_>> state)
    {
        m_pCurrentState = state;
    }

	void SetPreviousState(std::shared_ptr<State<actor_ty_>> state)
    {
        m_pPreviousState = state;
    }

    void ChangeState(
        std::shared_ptr<State<actor_ty_>> pNewState,
        std::shared_ptr<actor_ty_>        actor)
    {
        assert(pNewState && "<AIStateMachine::ChangeState>: trying to change to a NULL state");

        m_pPreviousState = m_pCurrentState;
        m_pCurrentState->Exit(actor);
        m_pCurrentState = pNewState;
        m_pCurrentState->Enter(actor);
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

    virtual execution_ty_ Execute(  std::shared_ptr<actor_ty_> actor) abstract;
    virtual void Update(update_ty_, std::shared_ptr<actor_ty_> actor) abstract;

public:
    std::shared_ptr<State<actor_ty_>> GetCurrentState()
    {
        return this->m_pCurrentState;
    }
};

#endif