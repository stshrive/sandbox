#ifndef AI_MODULE_H_
#define AI_MODULE_H_

template<typename owner_ty_, typename execution_ty_, typename update_ty_>
class AIModule
{
public:
    virtual execution_ty_ Execute(owner_ty_ *) abstract;
    virtual void Update(update_ty_, owner_ty_ *) abstract;
};

#endif //