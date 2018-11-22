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

class Ship 
{
public:
	virtual void SpecialAttack() = 0;
	virtual void SpecialAction() = 0;
	virtual void initialize(int PlacementGrid[][11]) = 0;
	virtual void Rotate(int PlacementGrid[][11]) = 0;
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]) = 0;
	virtual void SetPositionedStatus() = 0;
	virtual bool GetPositionedStatus() = 0;
	virtual bool GetDirection() = 0;
	//virtual bool GetSunkStatus() = 0;
	virtual Position& getpos() = 0;

};

class Carrier : public Ship
{
public:
	Carrier();
	virtual void SpecialAttack();
	virtual void SpecialAction();
	virtual void initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus();
	virtual bool GetDirection();
	//virtual bool GetSunkStatus();
	virtual Position& getpos();
private:
	class Plane
	{
	public:
		void Scout();
		void Return();
	};
	Position pos;
	BitMapObj Source;
	bool positioned;
	bool vertical;
	int Graphic[4][5];
	int NWSE;
	bool SunkStatus;
};

class BattleShip : public Ship
{
public:
	BattleShip();
	virtual void SpecialAttack();
	virtual void SpecialAction();
	virtual void initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus();
	virtual bool GetDirection();
	//virtual bool GetSunkStatus();
	virtual Position& getpos();
private:
	Position pos;
	BitMapObj Source;
	bool positioned;
	bool vertical;
	int Graphic[4][4];
	int NWSE;
	bool SunkStatus;
};

class Destroyer : public Ship
{
public:
	Destroyer();
	virtual void SpecialAttack();
	virtual void SpecialAction();
	virtual void initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus();
	virtual bool GetDirection();
	//virtual bool GetSunkStatus();
	virtual Position& getpos();
private:
	Position pos;
	BitMapObj Source;
	bool positioned;
	bool vertical;
	int Graphic[4][3];
	int NWSE;//North West South East 0,1,2,3
	bool SunkStatus;
};

class Submarine : public Ship
{
public:
	Submarine();
	virtual void SpecialAttack();
	virtual void SpecialAction();
	virtual void initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus();
	virtual bool GetDirection();
	//virtual bool GetSunkStatus();
	virtual Position& getpos();
private:
	Position pos;
	BitMapObj Source;
	bool positioned;
	bool vertical;
	int Graphic[4][3];
	int NWSE;
	bool SunkStatus;
};

class Patroller : public Ship
{
public:
	Patroller();
	virtual void SpecialAttack();
	virtual void SpecialAction();
	virtual void initialize(int PlacementGrid[][11]);
	virtual void Rotate(int PlacementGrid[][11]);
	virtual void Move(int up_down, int left_right, int PlacementGrid[][11]);
	virtual void SetPositionedStatus();
	virtual bool GetPositionedStatus();
	virtual bool GetDirection();
	//virtual bool GetSunkStatus();
	virtual Position& getpos();
private:
	Position pos;
	BitMapObj Source;
	bool positioned;
	bool vertical;
	int Graphic[4][2];
	int NWSE;
	bool SunkStatus;
};


#endif