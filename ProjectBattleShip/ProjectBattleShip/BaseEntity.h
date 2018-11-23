#ifndef PB_BASE_ENTITY_H_
#define PB_BASE_ENTITY_H_

class BaseEntity
{
private:
	unsigned m_ID;
	static int m_iNextValidID;
	void SetID(int value);
public:
	BaseEntity(int id)
	{
		SetID(id);
	}

	virtual ~BaseEntity(){;}

	int ID()const{return m_ID;}
};

#endif