#ifndef _SHIPS
#define _SHIPS

#pragma once
#include<Windows.h>
#include"_BitMapObj.h"
#include"tiledefs.h"
//#include"ShipTiles.h"

struct Position
{
	POINT tl;//the top and left of a ship
	POINT br;//the bottom and right of a ship
};
#define VERTICAL 1
#define HORIZONTAL 0

class Plane
{
public:
    void Scout();
    void Return();
};

class Ship 
{
public:
    Ship(int size, int graphic_base);
    virtual ~Ship();
	virtual void Initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus() const;
	virtual bool GetDirection() const;
	virtual bool GetSunkStatus(int PlacementGrid[][11]) const;
	virtual Position const & GetPos() const;
    virtual int const GetSize() const;

    virtual void SpecialAttack() = 0;
    virtual void SpecialAction() = 0;

protected:
    int size;
    int graphic_base;
    Position pos;
    BitMapObj Source;
    bool positioned;
    bool vertical;
    int NWSE;
    int * SourceIds[4];
};

class Carrier : public Ship
{
public:
	Carrier();
	virtual void SpecialAttack();
	virtual void SpecialAction();
};

class BattleShip : public Ship
{
public:
	BattleShip();
	virtual void SpecialAttack();
	virtual void SpecialAction();
};

class Destroyer : public Ship
{
public:
	Destroyer();
	virtual void SpecialAttack();
	virtual void SpecialAction();
};

class Submarine : public Ship
{
public:
	Submarine();
	virtual void SpecialAttack();
	virtual void SpecialAction();
};

class Patroller : public Ship
{
public:
	Patroller();
	virtual void SpecialAttack();
	virtual void SpecialAction();
};

#endif