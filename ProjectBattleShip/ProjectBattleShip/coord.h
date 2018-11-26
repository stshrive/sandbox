#ifndef COORD_XY
#define COORD_XY

typedef struct Coordinates
{
    Coordinates* operator=(int n)
    {
        this->x = 0;
        this->y = 0;
        return this;
    }
    Coordinates& operator-(int n)
    {
        this->x -= n;
        this->y -= n;
        return *this;
    }
    Coordinates& operator--(int)
    {
        this->x--;
        this->y--;
        return *this;
    }
    Coordinates& operator++(int)
    {
        this->x++;
        this->y++;
        return *this;
    }
    bool operator==(Coordinates const & other)
    {
        return this->x == other.x && this->y == other.y;
    }
    unsigned x;
    unsigned y;
} XY;
#endif