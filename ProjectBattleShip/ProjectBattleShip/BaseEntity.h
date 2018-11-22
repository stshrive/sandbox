#ifndef PB_BASE_ENTITY_H_
#define PB_BASE_ENTITY_H_

//Base level Game entity for all game objects with AI
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
	virtual void Update()=0;

	int ID()const{return m_ID;}
};

#endif