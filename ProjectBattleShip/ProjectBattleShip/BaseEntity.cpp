#include"BaseEntity.h"
#include <cassert>

int BaseEntity::m_iNextValidID = 0;

void BaseEntity::SetID(int value)
{
  assert( (value >= m_iNextValidID) && "<BaseEntity::SetID>: invalid ID");

  m_ID = value;
    
  m_iNextValidID = m_ID + 1;
}