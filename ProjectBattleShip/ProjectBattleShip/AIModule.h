#ifndef AI_MODULE_H_
#define AI_MODULE_H_

#include <memory>

template<typename actor_ty_, typename execution_ty_, typename update_ty_>
class AIModule
{
public:
    virtual execution_ty_ Execute(  std::shared_ptr<actor_ty_> actor) abstract;
    virtual void Update(update_ty_, std::shared_ptr<actor_ty_> actor) abstract;
};

#endif //