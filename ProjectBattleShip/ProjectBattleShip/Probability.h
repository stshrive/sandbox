#ifndef PROBABILITY_INTERFACE_H_
#define PROBABILITY_INTERFACE_H_

template<typename score_ty_, typename data_point_ty_>
class IProbability
{
public:
    virtual score_ty_ GetProbability(data_point_ty_) abstract;
    virtual void Update(data_point_ty_) abstract;
};

#endif