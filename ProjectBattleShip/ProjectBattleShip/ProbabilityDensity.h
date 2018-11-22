#ifndef PB_PROBABILITY_DENSITY_H_
#define PB_PROBABILITY_DENSITY_H_

#include"coord.h"
#include"ai.h"

#define _TWO   2
#define _THREE 3
#define _FOUR  4
#define _FIVE  5

class Probability : public AI
{
private:
	int ship_2_[10][10];
	int ship_3a[10][10];
	int ship_3b[10][10];
	int ship_4_[10][10];
	int ship_5_[10][10];
    int Master[10][10];

    int AggressionModifier[10][10];

    static int _2[];
    static int _3[];
    static int _4[];
    static int _5[];
	
	void ChangeProbability(int m[][10], const int Length, XY p);
public:
    Probability();
   ~Probability();
    Probability(const Probability&);

    void Update();
	void Update(XY position);
    int  GetProbability(XY position);

};

#endif