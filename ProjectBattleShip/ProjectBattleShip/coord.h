#ifndef COORD_XY
#define COORD_XY

#ifndef NULL
#define NULL 0
#endif

typedef struct Coordinates
{
    Coordinates* operator=(int n)
    {
        this->x = NULL;
        this->y = NULL;
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
    bool operator==(Coordinates const other)
    {
        return this->x == other.x && this->y == other.y;
    }
    unsigned x;
    unsigned y;
} XY;
#endif