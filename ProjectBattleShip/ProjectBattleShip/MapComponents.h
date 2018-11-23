#ifndef PB_MAP_COMPONENTS_H_
#define PB_MAP_COMPONENTS_H_

const int MAPWIDTH = 29;
const int MAPHEIGHT = 16;
const int GRIDSIZE = 11;
const int TILESIZE = 32;

static int MapGrid[MAPHEIGHT][MAPWIDTH];
static int OpponentGrid[GRIDSIZE][GRIDSIZE];
static int PlayerPosGrid[GRIDSIZE][GRIDSIZE];

#endif