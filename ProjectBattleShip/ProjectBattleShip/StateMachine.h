#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include"BaseState.h"
#include<assert.h>

#ifndef NULL
#define NULL 0
#endif

template<class entity_type>
class StateMachine
{
private:
	entity_type*        m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;

public:
	StateMachine(entity_type* owner):
		m_pOwner(owner),
		m_pCurrentState(NULL),
		m_pPreviousState(NULL),
		m_pGlobalState(NULL){};

	void SetCurrentState(State<entity_type>*  state){m_pCurrentState  = state;}
	void SetGlobalState(State<entity_type>*   state){m_pGlobalState   = state;}
	void SetPreviousState(State<entity_type>* state){m_pPreviousState = state;}

	void udate()const
	{
		if(m_pGlobalState) m_pGlobalState->Execute(m_pOwner);
		if(m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}

	void ChangeState(State<entity_type>* pNewState)
	{
		assert(pNewState && "<StateMachine::ChangeState>: trying to chanege to a NULL state");

		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}

	void RevertStates()
	{
		ChangeState(m_pPreviousState);
	}

	State<entity_type>* CurrentState() const {return m_pCurrentState;}
	State<entity_type>* PreviousState() const { return m_pPreviousState;}
	State<entity_type>* GlobalState() const {return m_pGlobalState;}
};

#endif