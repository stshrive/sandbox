#ifndef AI_BASE_H_


class AI
{
public:
    enum ACTION
    {
        ATTACK
    };

    virtual void Update() abstract;
    virtual void Update(XY pos) abstract;
    virtual int  GetProbability(XY pos) abstract;
};

#endif // !AI_BASE_H_