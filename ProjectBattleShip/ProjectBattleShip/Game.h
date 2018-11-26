#ifndef GAME_H_
#define GAME_H_

#include <map>
#include "BitMapObj.h"

class Ship;
enum Movement;
typedef struct ButtonSpecs mButton;

bool GameInitialize();
bool Setup(std::map<int, std::pair<Ship*, bool>> &ships);
bool MoveShip(Ship * ship, int map[][11], Movement movement);

void NewGame();
void EnemyTurn();
void MoveCursor(Coordinates cursor, int map[][11], Movement movement);
void DrawTile(BitMapObj &BmoDestination, BitMapObj &BmoSource, int x, int y, int TILE);
void RenderMap(bool hide);
void mCreateButton_xy(mButton &button, int x, int y);

POINT FindBitMapPos(int TILE);

enum GameStatus
{
    RUNNING,
    AIWINS,
    PLAYERWINS
};

GameStatus CheckVictoryStatus(
    std::map<int, std::pair<Ship*, bool>> const &player_ships,
    std::map<int, std::pair<Ship*, bool>> const &opponent_ships);

#endif