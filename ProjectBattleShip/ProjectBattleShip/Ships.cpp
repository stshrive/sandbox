#include"Ships.h"

Ship::Ship(int size, int graphic_base)
{
    this->size = size;
    this->graphic_base = graphic_base;

    for (int i = 0; i < 4; ++i)
    {
        this->SourceIds[i] = new int[this->size];
    }

    this->Source.Load(NULL, (LPCSTR) "tiles3.bmp");
    for (int i = 0; i < this->size; i++)
    {
        this->SourceIds[0][i] = this->graphic_base
            + i
            + this->size
            + 10;
    }

    for (int i = 0; i < this->size; i++)
    {
        this->SourceIds[1][i] = this->graphic_base
            + i
            + this->size;
    }

    for (int i = 0; i < this->size; i++)
    {
        this->SourceIds[2][i] = this->graphic_base + i + 10;
    }

    for (int i = 0; i < this->size; i++)
    {
        this->SourceIds[3][i] = this->graphic_base + i;
    }

    this->positioned = false;
    this->NWSE = 0;
}

Ship::~Ship()
{
    this->Source.Destroy();
    
    for (int i = 0; i < 4; ++i)
    {
        if (this->SourceIds[i])
        {
            delete[] this->SourceIds[i];
        }
    }
}

void Ship::Initialize(int PlacementGrid[][11])
{
    int i, j;
    for (j = 1; j < 11; ++j)
    {
        for (i = 1; i < 11; ++i)
        {
            if (PlacementGrid[i][j] != WATER)
                continue;
            else
            {
                for (int k = i + 1; k < 11 && k < (i + this->size + 1) && i < 7; ++k)
                {
                    if (PlacementGrid[k][j] != WATER) {
                        i = k;
                        continue;
                    }
                }
                if (i <= 6)
                {
                    int I = i, k;
                    pos.tl.x = j;
                    pos.tl.y = I;
                    for (I, k = 0; k < this->size; k++, I++)
                        PlacementGrid[I][j] = this->SourceIds[NWSE][k];
                    pos.br.x = j;
                    pos.br.y = I - 1;
                    vertical = true;
                    return;
                }
                else continue;
            }
        }
    }
}

void Ship::Rotate(int PlacementGrid[][11])
{
    int upper_pivot = (this->size - 1) / 2;
    int lower_pivot =
           (this->size - 1) / 2
        + ((this->size % 2 == 0) ? 1 : 0);

    int a, b, x, y;
    if (vertical)
    {
        a = pos.br.x + upper_pivot, b = pos.br.y - upper_pivot;
        x = pos.tl.x - lower_pivot, y = pos.tl.y + lower_pivot;
        for (int z = x; z <= a; z++) {
            if (z > 10)
                return;
            if (PlacementGrid[y][z] != WATER) {
                if (z == x + max(lower_pivot, upper_pivot))
                    continue;
                return;
            }
        }
        pos.br.x = a, pos.br.y = b;
        pos.tl.x = x, pos.tl.y = y;
        for (int i = y - lower_pivot; i <= b + upper_pivot; i++)
            PlacementGrid[i][x + lower_pivot] = WATER;
        int i = x, oi = i;
        NWSE = (NWSE + 1) % 4;
        for (i; i <= a; i++) {
            PlacementGrid[y][i] = this->SourceIds[NWSE][i - oi];
        }
        vertical = !vertical;
    }
    else
    {
        POINT temp;
        a = pos.br.x - upper_pivot, b = pos.br.y - upper_pivot;
        x = pos.tl.x + lower_pivot, y = pos.tl.y + lower_pivot;
        for (int z = b; z <= y; z++) {
            if (z > 10)
                return;
            if (PlacementGrid[z][x] != WATER) {
                if (z == y - max(lower_pivot, upper_pivot))
                    continue;
                return;
            }
        }

        pos.tl.x = x, pos.tl.y = y;
        pos.br.x = a, pos.br.y = b;
        temp = pos.tl;
        pos.tl = pos.br;
        pos.br = temp;
        for (int i = x - lower_pivot; i <= a + upper_pivot; i++)
            PlacementGrid[y - max(lower_pivot, upper_pivot)][i] = WATER;
        int i = b, oi = i;
        NWSE = (NWSE + 1) % 4;
        for (int i = b; i <= y; i++) {
            PlacementGrid[i][x] = this->SourceIds[NWSE][i - oi];
        }
        vertical = !vertical;
    }
}

void Ship::Move(int up_down, int left_right, int PlacementGrid[][11])
{
    if (up_down != 0 || left_right != 0)
    {
        if (GetDirection() == VERTICAL) {
            if (up_down < 0 && 1 <= (pos.tl.y + up_down) && (pos.tl.y + up_down) <= 10 &&
                PlacementGrid[pos.tl.y + up_down][pos.tl.x] == WATER) {
                for (int i = pos.tl.y + up_down, k = pos.tl.x; i < pos.br.y; i++)
                    PlacementGrid[i][k] = PlacementGrid[i + 1][k];
                PlacementGrid[pos.br.y][pos.br.x] = WATER;
                pos.tl.y = pos.tl.y + up_down;
                pos.br.y = pos.br.y + up_down;
            }
            if (up_down > 0 && 1 <= (pos.br.y + up_down) && (pos.br.y + up_down) <= 10 &&
                PlacementGrid[pos.br.y + up_down][pos.br.x] == WATER) {
                for (int i = pos.br.y + up_down, k = pos.br.x; i > pos.tl.y; i--)
                    PlacementGrid[i][k] = PlacementGrid[i - 1][k];
                PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
                pos.tl.y = pos.tl.y + up_down;
                pos.br.y = pos.br.y + up_down;
            }
            if (left_right < 0 || left_right > 0
                && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10) {
                for (int i = pos.tl.y; i <= pos.br.y; i++)
                    if (PlacementGrid[i][pos.tl.x + left_right] != WATER)
                        return;
                for (int i = pos.tl.y; i <= pos.br.y; i++) {
                    PlacementGrid[i][pos.tl.x + left_right] = PlacementGrid[i][pos.tl.x];
                    PlacementGrid[i][pos.tl.x] = WATER;
                }
                pos.tl.x = pos.tl.x + left_right;
                pos.br.x = pos.br.x + left_right;
            }
        }
        if (GetDirection() == HORIZONTAL) {
            if (up_down < 0 || up_down > 0
                && 1 <= (pos.tl.y + up_down) && (pos.br.y + up_down) <= 10) {
                for (int i = pos.tl.x; i <= pos.br.x; i++)
                    if (PlacementGrid[pos.tl.y + up_down][i] != WATER)
                        return;
                for (int i = pos.tl.x; i <= pos.br.x; i++) {
                    PlacementGrid[pos.tl.y + up_down][i] = PlacementGrid[pos.tl.y][i];
                    PlacementGrid[pos.tl.y][i] = WATER;
                }
                pos.tl.y = pos.tl.y + up_down;
                pos.br.y = pos.br.y + up_down;
            }
            if (left_right < 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
                PlacementGrid[pos.tl.y][pos.tl.x + left_right] == WATER) {
                for (int i = pos.tl.x + left_right, k = pos.tl.y; i < pos.br.x; i++)
                    PlacementGrid[k][i] = PlacementGrid[k][i + 1];
                PlacementGrid[pos.br.y][pos.br.x] = WATER;
                pos.tl.x = pos.tl.x + left_right;
                pos.br.x = pos.br.x + left_right;
            }
            if (left_right > 0 && 1 <= (pos.tl.x + left_right) && (pos.br.x + left_right) <= 10 &&
                PlacementGrid[pos.br.y][pos.br.x + left_right] == WATER) {
                for (int i = pos.br.x + left_right, k = pos.br.y; i > pos.tl.x; i--)
                    PlacementGrid[k][i] = PlacementGrid[k][i - 1];
                PlacementGrid[pos.tl.y][pos.tl.x] = WATER;
                pos.tl.x = pos.tl.x + left_right;
                pos.br.x = pos.br.x + left_right;
            }
        }
    }
}

inline void Ship::SetPositionedStatus()
{
    positioned = !positioned;
}

inline bool Ship::GetPositionedStatus() const
{
    return positioned;
}

inline bool Ship::GetDirection() const
{
    return vertical;
}

Position const & Ship::GetPos() const
{
    return this->pos;
}

int const Ship::GetSize() const
{
    return this->size;
}

bool Ship::GetSunkStatus(int PlacementGrid[][11]) const
{

    if (this->GetPositionedStatus())
    {
        long start_p;
        long end_p;

        if (this->GetDirection() == VERTICAL)
        {
            start_p = min(this->GetPos().tl.y, this->GetPos().tl.y);
            end_p = max(this->GetPos().tl.y, this->GetPos().tl.y);
        }
        else
        {
            start_p = min(this->GetPos().tl.x, this->GetPos().tl.x);
            end_p = max(this->GetPos().tl.x, this->GetPos().tl.x);
        }

        for (long point = start_p; point <= end_p; point++)
        {
            int id = 0;
            if (this->GetDirection() == VERTICAL)
            {
                id = PlacementGrid[point][this->GetPos().tl.x];
            }
            else
            {
                id = PlacementGrid[this->GetPos().tl.y][point];
            }

            bool found = false;
            for (int i = 0; i < 4 && !found; i++)
            {
                for (int j = 0; j < this->GetSize() && !found; j++)
                {
                    if (id == this->SourceIds[i][j])
                        found = true;
                }
            }

            if (!found) return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

Carrier::Carrier()
    : Ship(5, CARRIER1)
{
}

void Carrier::SpecialAttack(){;}
void Carrier::SpecialAction(){;}

BattleShip::BattleShip()
    : Ship(4, BTLSHIP1)
{
}

void BattleShip::SpecialAction(){;}
void BattleShip::SpecialAttack(){;}


Destroyer::Destroyer()
    : Ship (3, CRUISER1)
{
}

void Destroyer::SpecialAction(){;}
void Destroyer::SpecialAttack(){;}

Submarine::Submarine() 
    : Ship(3, SUBMARINE1)
{
}

void Submarine::SpecialAction(){;}
void Submarine::SpecialAttack(){;}

Patroller::Patroller()
    : Ship(2, PATROLLER1)
{
}

void Patroller::SpecialAction(){;}
void Patroller::SpecialAttack(){;}