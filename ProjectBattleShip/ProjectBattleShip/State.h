#ifndef PB_BASE_STATE_H_
#define PB_BASE_STATE_H_

#include <string>

template<class owner_ty_>
class State
{
protected:
    std::string id;

public:
    State(std::string id)
        : id(id) { }

    virtual ~State() {}

	virtual void Enter(owner_ty_*)=0;
	virtual void Execute(owner_ty_*)=0;
	virtual void Exit(owner_ty_*)=0;

    virtual std::string StateId() const final
    {
        return this->id;
    }
};

#endif