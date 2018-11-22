#ifndef PB_BASE_STATE_H_
#define PB_BASE_STATE_H_

//Base for all AI states implemented as part of a finite state Machine
template<class entity_type>
class State
{
public:
	virtual void Enter(entity_type*)=0;
	virtual void Execute(entity_type*)=0;
	virtual void Exit(entity_type*)=0;

	virtual ~State(){}
};

#endif