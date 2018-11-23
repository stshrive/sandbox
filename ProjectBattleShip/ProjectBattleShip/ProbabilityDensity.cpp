#include"ProbabilityDensity.h"

int Probability::_2[] = { 1,2,2,2,2,2,2,2,2,1 };
int Probability::_3[] = { 1,2,3,3,3,3,3,3,2,1 };
int Probability::_4[] = { 1,2,3,4,4,4,4,3,2,1 };
int Probability::_5[] = { 1,2,3,4,5,5,4,3,2,1 };

Probability::Probability()
{
	for(int i=0; i < 10; i++)
	{
		for(int j=i; j<10; j++)
		{
			ship_2_[i][j] = _2[i] + _2[j];
			ship_2_[j][i] = _2[i] + _2[j];

			ship_3a[i][j] = _3[i] + _3[j];
            ship_3a[j][i] = _3[i] + _3[j];

            ship_3b[i][j] = _3[i] + _3[j];
            ship_3b[j][i] = _3[i] + _3[j];

			ship_4_[i][j] = _4[i] + _4[j];
			ship_4_[j][i] = _4[i] + _4[j];

			ship_5_[i][j] = _5[i] + _5[j];
			ship_5_[j][i] = _5[i] + _5[j];
		}
	}

    this->Update();
}

Probability::~Probability() {}



void Probability::Update()
{
	for(int i = 0; i<10; i++){
		for(int j=0; j<10; j++)
			Master[i][j] = (
                  this->ship_2_[i][j]
                + this->ship_3a[i][j]
                + this->ship_3b[i][j]
                + this->ship_4_[i][j]
                + this->ship_5_[i][j]);
	}
}

void Probability::Update(XY position)
{
    if (position.x >= 0 && position.y >= 0)
    {
        this->ChangeProbability(ship_2_, _TWO  , position);
        this->ChangeProbability(ship_3a, _THREE, position);
        this->ChangeProbability(ship_3b, _THREE, position);
        this->ChangeProbability(ship_4_, _FOUR , position);
        this->ChangeProbability(ship_5_, _FIVE , position);
    }
    Update();
}

int Probability::GetProbability(XY position)
{
    return this->Master[position.y][position.x];
}

void Probability::ChangeProbability(int m[][10], const int Length, XY p)
{
	m[p.y][p.x] = 0;
	for(int i = 0; i < Length; i++)
	{
		if(p.y + i < 10)
        {
			m[p.y+i][p.x] -= (Length - i);
			if(m[p.y+i][p.x] < 0)
				m[p.y+i][p.x] = 0;
		}
		if(p.y - i >= 0)
        {
			m[p.y-i][p.x] -= (Length - i);
			if(m[p.y-i][p.x] < 0)
				m[p.y-i][p.x] = 0;
		}
		if(p.x + i < 10)
        {
			m[p.y][p.x+i] -= (Length - i);
			if(m[p.y][p.x+i] < 0)
				m[p.y][p.x+i] = 0;
		}
		if(p.y - i >= 0)
        {
			m[p.y][p.x-i] -= (Length - i);
			if(m[p.y][p.x-i] < 0)
				m[p.y][p.x-i] = 0;
		}
	}

}