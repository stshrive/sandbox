#include"HitProbability.h"
#include <vector>

int HitProbability::_2[] = { 1,2,2,2,2,2,2,2,2,1 };
int HitProbability::_3[] = { 1,2,3,3,3,3,3,3,2,1 };
int HitProbability::_4[] = { 1,2,3,4,4,4,4,3,2,1 };
int HitProbability::_5[] = { 1,2,3,4,5,5,4,3,2,1 };

HitProbability::HitProbability(unsigned mapsize)
{
    this->dimensions = mapsize;
    this->Init();
}

void HitProbability::Init()
{
	for(unsigned i=0; i < this->dimensions; i++)
	{
		for(unsigned j=i; j< this->dimensions; j++)
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

HitProbability::~HitProbability() {}

void HitProbability::Update()
{
	for(unsigned i = 0; i < this->dimensions; i++){
        for (unsigned j = 0; j < this->dimensions; j++)
        {
            this->update_lock.lock();

            Master[i][j] = (
                this->ship_2_[i][j]
                + this->ship_3a[i][j]
                + this->ship_3b[i][j]
                + this->ship_4_[i][j]
                + this->ship_5_[i][j]);

            this->update_lock.unlock();
        }
	}
}

void HitProbability::Update(XY position)
{
    if (position.x >= 0 && position.y >= 0)
    {
        this->ChangeProbability(ship_2_, _TWO  , position);
        this->ChangeProbability(ship_3a, _THREE, position);
        this->ChangeProbability(ship_3b, _THREE, position);
        this->ChangeProbability(ship_4_, _FOUR , position);
        this->ChangeProbability(ship_5_, _FIVE , position);
    }

    this->Update();
}

int HitProbability::GetProbability(XY position)
{
    if (position.x >= this->dimensions || position.y >= this->dimensions)
    {
        return 0;
    }
    else
    {
        return this->Master[position.y][position.x];
    }
}

void HitProbability::ChangeProbability(int m[][10], const unsigned Length, XY p)
{
	m[p.y][p.x] = 0;
	for(unsigned i = 0; i < Length; i++)
	{
		if(p.y + i < this->dimensions)
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
		if(p.x + i < this->dimensions)
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