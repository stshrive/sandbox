#include"Ships.h"

Carrier::Carrier()
{
	Source.Load(NULL, (LPCSTR) "tiles3.bmp");
	for(int i = 0; i < 5; i++)
		Graphic[0][i] = CARRIER1+i+15;
	for(int i = 0; i < 5; i++)
		Graphic[1][i] = CARRIER1+i+5;
	for(int i = 0; i < 5; i++)
		Graphic[2][i] = CARRIER1+i+10;
	for(int i = 0; i < 5; i++)
		Graphic[3][i] = CARRIER1+i;
	positioned = false;
	NWSE = 0;

}

void Carrier::SpecialAttack(){;}
void Carrier::SpecialAction(){;}

Position& Carrier::getpos()
{
	return pos;
}
void Carrier::initialize(int PlacementGrid[][11])
{
	int i, j;
	for(j=1; j < 11; ++j)
	{
		for(i=1; i < 11; ++i)
		{
			if(PlacementGrid[i][j] != WATER)
				continue;
			else
			{
				for(int k=i+1;k < 11&&k < (i+6)&&i < 7; ++k)
				{
					if(PlacementGrid[k][j] != WATER){
						i=k;
						continue;
					}
				}
				if(i<=6)
				{
					int I = i, k;
					pos.tl.x = j;
					pos.tl.y = I;
					for(I, k=0; k<5; k++, I++) 
						PlacementGrid[I][j] = Graphic[NWSE][k];
					pos.br.x = j;
					pos.br.y = I-1;
					vertical = true;
					return;
				}
				else continue;
			}
		}
	}
}

void Carrier::Rotate(int PlacementGrid[][11])
{
	int a,b,x,y;
	if(vertical)
	{
		a = pos.br.x+2, b = pos.br.y-2;
		x = pos.tl.x-2, y = pos.tl.y+2;
		for(int z = x; z <= a; z++){
			if(z > 10)
				return;
			if(PlacementGrid[y][z] != WATER){
				if(z == x+2)
					continue;
				return;
			}
		}
		pos.br.x = a, pos.br.y = b;
		pos.tl.x = x, pos.tl.y = y;
		for(int i = y-2; i<=b+2; i++)
			PlacementGrid[i][x+2] = WATER;
		int i = x, oi = i;
		NWSE = (NWSE+1)%4;
		for(i; i <= a; i++){
			PlacementGrid[y][i] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
	else
	{
		a = pos.br.x-2, b = pos.br.y-2;
		x = pos.tl.x+2, y = pos.tl.y+2;
		for(int z = b; z <= y; z++){
			if(z > 10)
				return;
			if(PlacementGrid[z][x] != WATER){
				if(z == y-2)
					continue;
				return;
			}
		}
		pos.br.x = x, pos.br.y = y;
		pos.tl.x = a, pos.tl.y = b;
		for(int i = x-2; i<=a+2; i++)
			PlacementGrid[y-2][i] = WATER;
		int i = b, oi = i;
		NWSE = (NWSE+1)%4;
		for(int i = b; i <= y; i++){
			PlacementGrid[i][x] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
}

void Carrier::Move(int up_down, int left_right, int PlacementGrid[][11])
{
	if(up_down != 0 || left_right != 0)
	{
		if(GetDirection() == VERTICAL){
			if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
				PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER){
				for(int i = pos.tl.y+up_down, k = pos.tl.x; i < pos.br.y; i++)
					PlacementGrid[i][k] = PlacementGrid[i+1][k];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
				PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER){
				for(int i = pos.br.y+up_down, k = pos.br.x; i > pos.tl.y; i--)
					PlacementGrid[i][k] = PlacementGrid[i-1][k];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if(left_right < 0 || left_right > 0 
				&& 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10){
				for(int i = pos.tl.y; i <= pos.br.y; i++)
					if(PlacementGrid[i][pos.tl.x + left_right] != WATER)
						return;
				for(int i = pos.tl.y; i <= pos.br.y; i++){
					PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
					PlacementGrid[i][pos.tl.x] = WATER;
				}
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
		if(GetDirection() == HORIZONTAL){
			if(up_down < 0 || up_down > 0 
				&& 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10){
				for(int i = pos.tl.x; i <= pos.br.x; i++)
					if(PlacementGrid[pos.tl.y + up_down][i] != WATER)
						return;
				for(int i = pos.tl.x; i <= pos.br.x; i++){
					PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
					PlacementGrid[pos.tl.y][i] = WATER;
				}
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER){
				for(int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
					PlacementGrid[k][i] = PlacementGrid[k][i+1];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
			if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER){
				for(int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
					PlacementGrid[k][i] = PlacementGrid[k][i-1];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
	}
}

inline void Carrier::SetPositionedStatus()
{
	positioned = !positioned;
}

inline bool Carrier::GetPositionedStatus()
{
	return positioned;
}

inline bool Carrier::GetDirection()
{
	return vertical;
}

BattleShip::BattleShip()
{
	Source.Load(NULL,(LPCSTR)"tiles3.bmp");
	for(int i = 0; i < 4; i++)
		Graphic[0][i] = BTLSHIP1 + i + 14;
	for(int i = 0; i < 4; i++)
		Graphic[1][i] = BTLSHIP1 + i + 4;
	for(int i = 0; i < 4; i++)
		Graphic[2][i] = BTLSHIP1 + i + 10;
	for(int i = 0; i < 4; i++)
		Graphic[3][i] = BTLSHIP1 + i;
	positioned = false;
	NWSE = 0;
}

void BattleShip::SpecialAction(){;}
void BattleShip::SpecialAttack(){;}

Position& BattleShip::getpos()
{
	return this->pos;
}

void BattleShip::initialize(int PlacementGrid[][11])
{
	int i, j;
	for(j=1; j < 11; ++j)
	{
		for(i=1; i < 11; ++i)
		{
			if(PlacementGrid[i][j] != WATER)
				continue;
			else
			{
				for(int k=i+1;k < 11&&k < (i+5)&&i < 8; ++k)
				{
					if(PlacementGrid[k][j] != WATER){
						i=k;
						continue;
					}
				}
				if(i<=7 && PlacementGrid[i][j] == WATER)
				{
					int I = i, k;
					pos.tl.x = j;
					pos.tl.y = I;
					for(I, k=0; k<4; k++, I++) 
						PlacementGrid[I][j] = Graphic[NWSE][k];
					pos.br.x = j;
					pos.br.y = I-1;
					vertical = true;
					return;
				}
				else continue;
			}
		}
	}
}

void BattleShip::Rotate(int PlacementGrid[][11])
{
	int a,b,x,y;
	if(vertical)
	{
		a = pos.br.x+1, b = pos.br.y-1;
		x = pos.tl.x-2, y = pos.tl.y+2;
		for(int z = x; z <= a; z++){
			if(z > 10)
				return;
			if(PlacementGrid[y][z] != WATER){
				if(z == x+2)
					continue;
				return;
			}
		}
		pos.br.x = a, pos.br.y = b;
		pos.tl.x = x, pos.tl.y = y;
		for(int i = y-2; i<=b+1; i++)
			PlacementGrid[i][x+2] = WATER;
		int i = x, oi = i;
		NWSE = (NWSE+1)%4;
		for(i; i <= a; i++){
			PlacementGrid[y][i] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
	else
	{
		POINT temp;
		a = pos.br.x-1, b = pos.br.y-1;
		x = pos.tl.x+2, y = pos.tl.y+2;
		for(int z = b; z <= y; z++){
			if(z > 10)
				return;
			if(PlacementGrid[z][x] != WATER){
				if(z == y-2)
					continue;
				return;
			}
		}
		pos.tl.x = x, pos.tl.y = y;
		pos.br.x = a, pos.br.y = b;
		temp = pos.tl;
		pos.tl = pos.br;
		pos.br = temp;
		for(int i = x-2; i<=a+1; i++)
			PlacementGrid[y-2][i] = WATER;
		int i = b, oi = i;
		NWSE = (NWSE+1)%4;
		for(int i = b; i <= y; i++){
			PlacementGrid[i][x] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
}

void BattleShip::Move(int up_down, int left_right, int PlacementGrid[][11])
{
	if(up_down != 0 || left_right != 0)
	{
		if(GetDirection() == VERTICAL){
			if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
				PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER){
				for(int i = pos.tl.y+up_down, k = pos.tl.x; i < pos.br.y; i++)
					PlacementGrid[i][k] = PlacementGrid[i+1][k];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
				PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER){
				for(int i = pos.br.y+up_down, k = pos.br.x; i > pos.tl.y; i--)
					PlacementGrid[i][k] = PlacementGrid[i-1][k];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if(left_right < 0 || left_right > 0 
				&& 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10){
				for(int i = pos.tl.y; i <= pos.br.y; i++)
					if(PlacementGrid[i][pos.tl.x + left_right] != WATER)
						return;
				for(int i = pos.tl.y; i <= pos.br.y; i++){
					PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
					PlacementGrid[i][pos.tl.x] = WATER;
				}
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
		if(GetDirection() == HORIZONTAL){
			if(up_down < 0 || up_down > 0 
				&& 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10){
				for(int i = pos.tl.x; i <= pos.br.x; i++)
					if(PlacementGrid[pos.tl.y + up_down][i] != WATER)
						return;
				for(int i = pos.tl.x; i <= pos.br.x; i++){
					PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
					PlacementGrid[pos.tl.y][i] = WATER;
				}
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER){
				for(int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
					PlacementGrid[k][i] = PlacementGrid[k][i+1];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
			if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER){
				for(int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
					PlacementGrid[k][i] = PlacementGrid[k][i-1];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
	}
}

void BattleShip::SetPositionedStatus()
{
	positioned = !positioned;
}

inline bool BattleShip::GetPositionedStatus()
{
	return positioned;
}

inline bool BattleShip::GetDirection()
{
	return vertical;
}

Destroyer::Destroyer()
{
	Source.Load(NULL,(LPCSTR)"tiles3.bmp");
	for(int i = 0; i < 3; i++)
		Graphic[0][i] = CRUISER1 + i + 13;
	for(int i = 0; i < 3; i++)
		Graphic[1][i] = CRUISER1 + i + 3;
	for(int i = 0; i < 3; i++)
		Graphic[2][i] = CRUISER1 + i + 10;
	for(int i = 0; i < 3; i++)
		Graphic[3][i] = CRUISER1 + i;
	positioned = false;
	NWSE = 0;
}

void Destroyer::SpecialAction(){;}
void Destroyer::SpecialAttack(){;}

Position& Destroyer::getpos()
{
	return this->pos;
}

void Destroyer::initialize(int PlacementGrid[][11])
{
	int i, j;
	for(j=1; j < 11; ++j)
	{
		for(i=1; i < 11; ++i)
		{
			if(PlacementGrid[i][j] != WATER)
				continue;
			else
			{
				for(int k=i+1;k < 11&&k < (i+4)&&i < 9; ++k)
				{
					if(PlacementGrid[k][j] != WATER){
						i=k;
						continue;
					}
				}
				if(i<=8 && PlacementGrid[i][j] == WATER)
				{
					int I = i, k;
					pos.tl.x = j;
					pos.tl.y = I;
					for(I, k=0; k<3; k++, I++) 
						PlacementGrid[I][j] = Graphic[NWSE][k];
					pos.br.x = j;
					pos.br.y = I-1;
					vertical = true;
					return;
				}
				else continue;
			}
		}
	}
}

void Destroyer::Rotate(int PlacementGrid[][11])
{
	int a,b,x,y;
	if(vertical)
	{
		a = pos.br.x+1, b = pos.br.y-1;
		x = pos.tl.x-1, y = pos.tl.y+1;
		for(int z = x; z <= a; z++){
			if(z > 10)
				return;
			if(PlacementGrid[y][z] != WATER){
				if(z == x+1)
					continue;
				return;
			}
		}
		pos.br.x = a, pos.br.y = b;
		pos.tl.x = x, pos.tl.y = y;
		for(int i = y-1; i<=b+1; i++)
			PlacementGrid[i][x+1] = WATER;
		int i = x, oi = i;
		NWSE = (NWSE+1)%4;
		for(i; i <= a; i++){
			PlacementGrid[y][i] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
	else
	{
		POINT temp;
		a = pos.br.x-1, b = pos.br.y-1;
		x = pos.tl.x+1, y = pos.tl.y+1;
		for(int z = b; z <= y; z++){
			if(z > 10)
				return;
			if(PlacementGrid[z][x] != WATER){
				if(z == y-1)
					continue;
				return;
			}
		}
		pos.tl.x = x, pos.tl.y = y;
		pos.br.x = a, pos.br.y = b;
		temp = pos.tl;
		pos.tl = pos.br;
		pos.br = temp;
		for(int i = x-1; i<=a+1; i++)
			PlacementGrid[y-1][i] = WATER;
		int i = b, oi = i;
		NWSE = (NWSE+1)%4;
		for(int i = b; i <= y; i++){
			PlacementGrid[i][x] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
}

void Destroyer::Move(int up_down, int left_right, int PlacementGrid[][11])
{
	if(up_down != 0 || left_right != 0)
	{
		if(GetDirection() == VERTICAL){
			if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
				PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER){
				for(int i = pos.tl.y+up_down, k = pos.tl.x; i < pos.br.y; i++)
					PlacementGrid[i][k] = PlacementGrid[i+1][k];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
				PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER){
				for(int i = pos.br.y+up_down, k = pos.br.x; i > pos.tl.y; i--)
					PlacementGrid[i][k] = PlacementGrid[i-1][k];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if(left_right < 0 || left_right > 0 
				&& 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10){
				for(int i = pos.tl.y; i <= pos.br.y; i++)
					if(PlacementGrid[i][pos.tl.x + left_right] != WATER)
						return;
				for(int i = pos.tl.y; i <= pos.br.y; i++){
					PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
					PlacementGrid[i][pos.tl.x] = WATER;
				}
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
		if(GetDirection() == HORIZONTAL){
			if(up_down < 0 || up_down > 0 
				&& 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10){
				for(int i = pos.tl.x; i <= pos.br.x; i++)
					if(PlacementGrid[pos.tl.y + up_down][i] != WATER)
						return;
				for(int i = pos.tl.x; i <= pos.br.x; i++){
					PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
					PlacementGrid[pos.tl.y][i] = WATER;
				}
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER){
				for(int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
					PlacementGrid[k][i] = PlacementGrid[k][i+1];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
			if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER){
				for(int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
					PlacementGrid[k][i] = PlacementGrid[k][i-1];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
	}
}

void Destroyer::SetPositionedStatus()
{
	positioned = !positioned;
}

inline bool Destroyer::GetPositionedStatus()
{
	return positioned;
}

inline bool Destroyer::GetDirection()
{
	return vertical;
}

Submarine::Submarine()
{
	Source.Load(NULL,(LPCSTR)"tiles3.bmp");
	for(int i = 0; i < 3; i++)
		Graphic[0][i] = SUBMARINE1 + i + 13;
	for(int i = 0; i < 3; i++)
		Graphic[1][i] = SUBMARINE1 + i + 3;
	for(int i = 0; i < 3; i++)
		Graphic[2][i] = SUBMARINE1 + i + 10;
	for(int i = 0; i < 3; i++)
		Graphic[3][i] = SUBMARINE1 + i;
	positioned = false;
	NWSE = 0;
}

void Submarine::SpecialAction(){;}
void Submarine::SpecialAttack(){;}

Position& Submarine::getpos()
{
	return this->pos;
}

void Submarine::initialize(int PlacementGrid[][11])
{
	int i, j;
	for(j=1; j < 11; ++j)
	{
		for(i=1; i < 11; ++i)
		{
			if(PlacementGrid[i][j] != WATER)
				continue;
			else
			{
				for(int k=i+1;k < 11&&k < (i+4)&&i < 9; ++k)
				{
					if(PlacementGrid[k][j] != WATER){
						i=k;
						continue;
					}
				}
				if(i<=8 && PlacementGrid[i][j] == WATER)
				{
					int I = i, k;
					pos.tl.x = j;
					pos.tl.y = I;
					for(I, k=0; k<3; k++, I++) 
						PlacementGrid[I][j] = Graphic[NWSE][k];
					pos.br.x = j;
					pos.br.y = I-1;
					vertical = true;
					return;
				}
				else continue;
			}
		}
	}
}

void Submarine::Rotate(int PlacementGrid[][11])
{
	int a,b,x,y;
	if(vertical)
	{
		a = pos.br.x+1, b = pos.br.y-1;
		x = pos.tl.x-1, y = pos.tl.y+1;
		for(int z = x; z <= a; z++){
			if(z > 10)
				return;
			if(PlacementGrid[y][z] != WATER){
				if(z == x+1)
					continue;
				return;
			}
		}
		pos.br.x = a, pos.br.y = b;
		pos.tl.x = x, pos.tl.y = y;
		for(int i = y-1; i<=b+1; i++)
			PlacementGrid[i][x+1] = WATER;
		int i = x, oi = i;
		NWSE = (NWSE+1)%4;
		for(i; i <= a; i++){
			PlacementGrid[y][i] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
	else
	{
		POINT temp;
		a = pos.br.x-1, b = pos.br.y-1;
		x = pos.tl.x+1, y = pos.tl.y+1;
		for(int z = b; z <= y; z++){
			if(z > 10)
				return;
			if(PlacementGrid[z][x] != WATER){
				if(z == y-1)
					continue;
				return;
			}
		}
		pos.tl.x = x, pos.tl.y = y;
		pos.br.x = a, pos.br.y = b;
		temp = pos.tl;
		pos.tl = pos.br;
		pos.br = temp;
		for(int i = x-1; i<=a+1; i++)
			PlacementGrid[y-1][i] = WATER;
		int i = b, oi = i;
		NWSE = (NWSE+1)%4;
		for(int i = b; i <= y; i++){
			PlacementGrid[i][x] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
}

void Submarine::Move(int up_down, int left_right, int PlacementGrid[][11])
{
	if(up_down != 0 || left_right != 0)
	{
		if(GetDirection() == VERTICAL){
			if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
				PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER){
				for(int i = pos.tl.y+up_down, k = pos.tl.x; i < pos.br.y; i++)
					PlacementGrid[i][k] = PlacementGrid[i+1][k];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
				PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER){
				for(int i = pos.br.y+up_down, k = pos.br.x; i > pos.tl.y; i--)
					PlacementGrid[i][k] = PlacementGrid[i-1][k];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if(left_right < 0 || left_right > 0 
				&& 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10){
				for(int i = pos.tl.y; i <= pos.br.y; i++)
					if(PlacementGrid[i][pos.tl.x + left_right] != WATER)
						return;
				for(int i = pos.tl.y; i <= pos.br.y; i++){
					PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
					PlacementGrid[i][pos.tl.x] = WATER;
				}
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
		if(GetDirection() == HORIZONTAL){
			if(up_down < 0 || up_down > 0 
				&& 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10){
				for(int i = pos.tl.x; i <= pos.br.x; i++)
					if(PlacementGrid[pos.tl.y + up_down][i] != WATER)
						return;
				for(int i = pos.tl.x; i <= pos.br.x; i++){
					PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
					PlacementGrid[pos.tl.y][i] = WATER;
				}
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER){
				for(int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
					PlacementGrid[k][i] = PlacementGrid[k][i+1];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
			if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER){
				for(int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
					PlacementGrid[k][i] = PlacementGrid[k][i-1];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
	}
}

void Submarine::SetPositionedStatus()
{
	positioned = !positioned;
}

inline bool Submarine::GetPositionedStatus()
{
	return positioned;
}

inline bool Submarine::GetDirection()
{
	return vertical;
}

Patroller::Patroller()
{
	Source.Load(NULL,(LPCSTR)"tiles3.bmp");
	for(int i = 0; i < 2; i++)
		Graphic[0][i] = PATROLLER1 + i + 12;
	for(int i = 0; i < 2; i++)
		Graphic[1][i] = PATROLLER1 + i + 2;
	for(int i = 0; i < 2; i++)
		Graphic[2][i] = PATROLLER1 + i + 10;
	for(int i = 0; i < 2; i++)
		Graphic[3][i] = PATROLLER1 + i;
	positioned = false;
	NWSE = 0;
}

void Patroller::SpecialAction(){;}
void Patroller::SpecialAttack(){;}

Position& Patroller::getpos()
{
	return this->pos;
}

void Patroller::initialize(int PlacementGrid[][11])
{
	int i, j;
	for(j=1; j < 11; ++j)
	{
		for(i=1; i < 11; ++i)
		{
			if(PlacementGrid[i][j] != WATER)
				continue;
			else
			{
				for(int k=i+1;k < 11&&k < (i+3)&&i < 10; ++k)
				{
					if(PlacementGrid[k][j] != WATER){
						i=k;
						continue;
					}
				}
				if(i<=9 && PlacementGrid[i][j] == WATER)
				{
					int I = i, k;
					pos.tl.x = j;
					pos.tl.y = I;
					for(I, k=0; k<2; k++, I++) 
						PlacementGrid[I][j] = Graphic[NWSE][k];
					pos.br.x = j;
					pos.br.y = I-1;
					vertical = true;
					return;
				}
				else continue;
			}
		}
	}
}

void Patroller::Rotate(int PlacementGrid[][11])
{
	int a,b,x,y;
	if(vertical)
	{
		a = pos.br.x,   b = pos.br.y;
		x = pos.tl.x-1, y = pos.tl.y+1;
		for(int z = x; z <= a; z++){
			if(z > 10)
				return;
			if(PlacementGrid[y][z] != WATER){
				if(z == x+1)
					continue;
				return;
			}
		}
		pos.br.x = a, pos.br.y = b;
		pos.tl.x = x, pos.tl.y = y;
		for(int i = y-1; i<=b; i++)
			PlacementGrid[i][x+1] = WATER;
		int i = x, oi = i;
		NWSE = (NWSE+1)%4;
		for(i; i <= a; i++){
			PlacementGrid[y][i] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
	else
	{
		POINT temp;
		a = pos.br.x,   b = pos.br.y;
		x = pos.tl.x+1, y = pos.tl.y+1;
		for(int z = b; z <= y; z++){
			if(z > 10)
				return;
			if(PlacementGrid[z][x] != WATER){
				if(z == y-1)
					continue;
				return;
			}
		}
		pos.tl.x = x, pos.tl.y = y;
		pos.br.x = a, pos.br.y = b;
		temp = pos.tl;
		pos.tl = pos.br;
		pos.br = temp;
		for(int i = x-1; i<=a; i++)
			PlacementGrid[y-1][i] = WATER;
		int i = b, oi = i;
		NWSE = (NWSE+1)%4;
		for(int i = b; i <= y; i++){
			PlacementGrid[i][x] = Graphic[NWSE][i-oi];
		}
		vertical = !vertical;
	}
}

void Patroller::Move(int up_down, int left_right, int PlacementGrid[][11])
{
	if(up_down != 0 || left_right != 0)
	{
		if(GetDirection() == VERTICAL){
			if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
				PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER){
				for(int i = pos.tl.y+up_down, k = pos.tl.x; i < pos.br.y; i++)
					PlacementGrid[i][k] = PlacementGrid[i+1][k];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
				PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER){
				for(int i = pos.br.y+up_down, k = pos.br.x; i > pos.tl.y; i--)
					PlacementGrid[i][k] = PlacementGrid[i-1][k];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if(left_right < 0 || left_right > 0 
				&& 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10){
				for(int i = pos.tl.y; i <= pos.br.y; i++)
					if(PlacementGrid[i][pos.tl.x + left_right] != WATER)
						return;
				for(int i = pos.tl.y; i <= pos.br.y; i++){
					PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
					PlacementGrid[i][pos.tl.x] = WATER;
				}
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
		if(GetDirection() == HORIZONTAL){
			if(up_down < 0 || up_down > 0 
				&& 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10){
				for(int i = pos.tl.x; i <= pos.br.x; i++)
					if(PlacementGrid[pos.tl.y + up_down][i] != WATER)
						return;
				for(int i = pos.tl.x; i <= pos.br.x; i++){
					PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
					PlacementGrid[pos.tl.y][i] = WATER;
				}
				pos.tl.y = pos.tl.y + up_down;
				pos.br.y = pos.br.y + up_down;
			}
			if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER){
				for(int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
					PlacementGrid[k][i] = PlacementGrid[k][i+1];
				PlacementGrid[pos.br.y][pos.br.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
			if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
				PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER){
				for(int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
					PlacementGrid[k][i] = PlacementGrid[k][i-1];
				PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
				pos.tl.x = pos.tl.x + left_right;
				pos.br.x = pos.br.x + left_right;
			}
		}
	}
}

void Patroller::SetPositionedStatus()
{
	positioned = !positioned;
}

inline bool Patroller::GetPositionedStatus()
{
	return positioned;
}

inline bool Patroller::GetDirection()
{
	return vertical;
}

