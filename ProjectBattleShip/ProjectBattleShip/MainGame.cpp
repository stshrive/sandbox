///==================================================================
/// Project Created By: Steven Shriver
/// Date March 2012
/// Enjoy and feel free to report all bugs/comments/ideas/fixes
///==================================================================

#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<stdlib.h>
#include<DShow.h>
#include"MapComponents.h"
#include"BitMapObj.h"
#include"Ships.h"
#include"Opponent.h"
#include"Game.h"

#include<map>

#define WINDOWCLASS "Battling Ships"
#define WINDOWTITLE "BATTLEFIELD"

CHAR  WarningMessage[] = "You are about to exit the game!\nAre you sure this is what you want to do?";

//The Buttons----------------------------------------------------------------
int Id = 100;//start id for the buttons
typedef struct ButtonSpecs
{
	HWND Button;
	int ID;
	int xCoordinate;
	int yCoordinate;
}mButton;

mButton GridButtons[GRIDSIZE-1][GRIDSIZE-1];

//Ship Declarations ------------------------------------------------------------------------------
Carrier    PlayerCarrier;
BattleShip PlayerBattleShip;
Destroyer  PlayerCruiser;
Submarine  PlayerSub;
Patroller  PlayerPatrol;

std::map<int, std::pair<Ship*, bool>> ships = {
    {0, std::make_pair(&PlayerCarrier, false)},
    {1, std::make_pair(&PlayerBattleShip, false)},
    {2, std::make_pair(&PlayerCruiser, false)},
    {3, std::make_pair(&PlayerSub, false)},
    {4, std::make_pair(&PlayerPatrol, false)}
};


std::map<int, std::pair<Ship*, bool>>::size_type INVALID = 1000;
std::map<int, std::pair<Ship*, bool>>::size_type ShipId;
std::map<int, std::pair<Ship*, bool>>::size_type SHIPCOUNT = 5;

enum Movement
{
      Set    = VK_RETURN
    , Rotate = VK_SPACE
    , Left   = VK_LEFT
    , Up     = VK_UP
    , Right  = VK_RIGHT
    , Down   = VK_DOWN
};

//Some Booleans For GamePlay
bool PLAYERTURN = false;
bool GameStarted = false;
bool HideOpponent = true;

//The Main Window and Its Instance-------------------------------------------
HINSTANCE hInstanceMain = NULL;
HWND      hWndMain      = NULL;

//BitMapObjects for holding the Graphics-------------------------------------
BitMapObj GameWindow;
BitMapObj GraphicSource;

Coordinates Cursor;

//The Window Procedure-------------------------------------------------------
LRESULT CALLBACK WindowProcedure(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
	switch(uMsg)
	{
		case WM_CREATE:
			{
				return 0;
			}break;

		case WM_LBUTTONUP:
			{	
				RenderMap(HideOpponent);
			}break;

		//Check Which button has been clicked on and change graphic accordingly
		case WM_COMMAND:
			{
				if(GameStarted == false)
					return 0;
			
				int i = 0, j = 0;
				while(LOWORD(wParam) != GridButtons[i][j].ID)
				{
					i++;
					if(i % BOARDSIZE == 0)
						j++;
					i %= BOARDSIZE;
					j %= BOARDSIZE;
				}

                int x = GridButtons[i][j].xCoordinate + 1;
                int y = GridButtons[i][j].yCoordinate + 1;
                
                if (OpponentGrid[y][x] != WATER && OpponentGrid[y][x] != MISS)
                {
                    OpponentGrid[y][x] = HIT;
                }
                else
                {
                    OpponentGrid[y][x] = MISS;
                }

				SendMessage(GridButtons[i][j].Button,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,TRANSPARENT);
				EnableWindow(GridButtons[i][j].Button,FALSE);
				ShowWindow(GridButtons[i][j].Button,SW_HIDE);

                PLAYERTURN = false;

				RenderMap(HideOpponent);
				return 0;
			}break;

		case WM_KEYDOWN:
			{
				if(wParam == VK_ESCAPE){
					if(MessageBox(NULL,WarningMessage,"Leave Game?",MB_ICONEXCLAMATION|MB_YESNOCANCEL)==IDYES)
						DestroyWindow(hWndMain);
					return 0;
				}
                else if (!GameStarted)
                {
                    if (ShipId < ships.size())
                    {
                        MoveShip(ships[ShipId].first, PlayerPosGrid, (Movement)wParam);
                    }

					RenderMap(HideOpponent);
					return 0;
				}
                else
                {
                    MoveCursor(Cursor, OpponentGrid, (Movement)wParam);
                }
			}break;

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;;
			}break;

		case BM_SETIMAGE:
			{
				PAINTSTRUCT BtnPaint;
				HDC BtnHdc;
				int i=0, j=0;
				int lprm = LOWORD(lParam);
				while(LOWORD(lParam) != GridButtons[i][j].ID)
				{
					i++;
					if(i % BOARDSIZE == 0)
						j++;
					i %= BOARDSIZE;
					j %= BOARDSIZE;
				}
				BtnHdc = BeginPaint(GridButtons[i][j].Button,&BtnPaint);
				BitBlt(BtnHdc,0,0,TILESIZE,TILESIZE,GraphicSource,0,0,SRCAND);

				EndPaint(GridButtons[i][j].Button,&BtnPaint);
				return 0;
			}break;

		case WM_PAINT:
			{
				PAINTSTRUCT paint;
				HDC hdc;
				hdc = BeginPaint(hwnd,&paint);
				BitBlt(hdc,0,0,MAPWIDTH*TILESIZE,MAPHEIGHT*TILESIZE,GameWindow,0,0,SRCCOPY);

				EndPaint(hwnd,&paint);
				return 0;
			}break;

		default:
			{
			}break;
	}
	
	return(DefWindowProc(hwnd,uMsg,wParam,lParam));
}


//////////////The WinMain Entry Point///////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpArgs, int nCmdShow)
{
	MessageBox(NULL,"Welcome To Battle Ship!", "WELCOME!", MB_OK);
	hInstanceMain = hInstance;

	WNDCLASSEX clex;
	clex.cbSize = sizeof(WNDCLASSEX);
	clex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	clex.lpfnWndProc = WindowProcedure;
	clex.cbClsExtra = 0;
	clex.cbWndExtra = 0;
	clex.hInstance = hInstanceMain;
	clex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	clex.hCursor = LoadCursor(NULL, IDC_ARROW);
	clex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	clex.lpszMenuName = NULL;
	clex.lpszClassName = WINDOWCLASS;
	clex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	
	if(!RegisterClassEx(&clex)){
		MessageBox(NULL, "Window Registration Failed","ERROR!",MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}

	hWndMain = CreateWindowEx(
		0,
		WINDOWCLASS,
		WINDOWTITLE,
		WS_BORDER | WS_SYSMENU | 
		WS_CAPTION| WS_VISIBLE | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		932,550,
		NULL,NULL,
		hInstanceMain,NULL);
	
	if(!hWndMain) return 0;
	if(!GameInitialize()) return 0;
    
    GameStatus status = GameStatus::RUNNING;

	MSG MainMsg;
	
	for(;;)
	{
        if (!PLAYERTURN)
        {
            EnemyTurn();
            continue;
        }

		if(PeekMessage(&MainMsg,NULL,0,0,PM_REMOVE))
		{
			if(MainMsg.message == WM_QUIT)
				break;
			TranslateMessage(&MainMsg);
			DispatchMessage(&MainMsg);
		}
		if(GameStarted == false)
		{
            if ((GameStarted = Setup(ships)))
            {
                Cursor.x = 0;
                Cursor.y = 0;
            }

            continue;
		}
        else
        {
            status = CheckVictoryStatus(ships, Opponent->GetShips());
            if (status == GameStatus::AIWINS)
            {
                HideOpponent = false;
                MessageBox(NULL, "You Lose!", "GAME OVER!", MB_OK);
            }
            if (status == GameStatus::PLAYERWINS)
            {
                HideOpponent = false;
                MessageBox(NULL, "You Win!", "GAME OVER!", MB_OK);
            }
        }
	}
	return MainMsg.wParam;
}

bool GameInitialize()
{
	RECT tempRect;
	SetRect(&tempRect, 0, 0, MAPWIDTH * TILESIZE, MAPHEIGHT * TILESIZE);
	AdjustWindowRect(&tempRect, WS_BORDER | WS_SYSMENU | WS_CAPTION | WS_VISIBLE, FALSE);
	SetWindowPos(hWndMain,
		NULL, 0, 0,
		tempRect.right  - tempRect.left,
		tempRect.bottom - tempRect.top,
		SWP_NOMOVE);

	HDC hdc = GetDC(hWndMain);
	GameWindow.Create(hdc,MAPWIDTH * TILESIZE, MAPWIDTH * TILESIZE);
	FillRect(GameWindow,&tempRect,(HBRUSH)GetStockObject(NULL_BRUSH));
	ReleaseDC(hWndMain,hdc);

	GraphicSource.Load(NULL,(LPCTSTR)"tiles3.bmp");

	NewGame();

	return true;
}

void mCreateButton_xy(mButton &button, int x, int y)
{
	button.Button = CreateWindowEx(
		WS_EX_TRANSPARENT,
		"BUTTON",
		NULL,
		WS_CHILD|WS_VISIBLE|BS_FLAT|
		BS_NOTIFY|BS_BITMAP,
		x*TILESIZE+0,//x-coordinate of button
		y*TILESIZE+0,//y-coordinate of button
		TILESIZE-0,
		TILESIZE-0,
		hWndMain,
		(HMENU)button.ID,
		hInstanceMain,
		NULL);

	SendMessage(hWndMain,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)button.ID);
}

void NewGame()
{
	ShipId = INVALID;
	for(int i = 0; i < GRIDSIZE; i++)
	{
		for(int j = 0; j < GRIDSIZE; j++)
		{
			if(i==0&&j==0){
				OpponentGrid[i][j] = MISS;
				PlayerPosGrid[i][j] = MISS;
			}
			else if(i==0&&j>=1){
				OpponentGrid[i][j] = 19+j;
				PlayerPosGrid[i][j] = 19+j;
			}
			else if(j==0&&i>=1){
				OpponentGrid[i][j] = 9+i;
				PlayerPosGrid[i][j] = 9+i;
			}
			else{
				OpponentGrid[i][j] = WATER;
				PlayerPosGrid[i][j] = WATER;
			}
		}
	}

	RenderMap(HideOpponent);
}

bool Setup(std::map<int, std::pair<Ship*, bool>> &ships)
{
    if (ShipId == INVALID)
    {
        ShipId = 0;
        ships[ShipId].first->Initialize(PlayerPosGrid);
    }

    if (ships[ShipId].first->GetPositionedStatus())
    {
        ShipId++;
        if (ShipId >= SHIPCOUNT)
        {
            for (int bx = 0; bx < GRIDSIZE - 1; bx++)
            {
                for (int by = 0; by < GRIDSIZE - 1; by++) {
                    GridButtons[by][bx].ID = Id;
                    GridButtons[by][bx].xCoordinate = bx;
                    GridButtons[by][bx].yCoordinate = by;
                    mCreateButton_xy(GridButtons[by][bx], bx + 3, by + 4);
                    Id++;
                }
            }
            return true;
        }
        ships[ShipId].first->Initialize(PlayerPosGrid);
    }

    RenderMap(HideOpponent);

    return false;
}

void RenderMap(bool hide)
{
	for(int y = 0; y < MAPHEIGHT; y++)
	{
		for(int x = 0; x < MAPWIDTH; x++)
		{
            if ((y > 2 && y <= 13) && (x > 1 && x <= 12))
            {
                int value = OpponentGrid[y - 3][x - 2];
                if ((hide
                    &&  value != WATER)
                    && (value != HIT)
                    && (value != MISS)
                    && (value != ONE)
                    && (value != TWO)
                    && (value != THREE)
                    && (value != FOUR)
                    && (value != FIVE)
                    && (value != SIX)
                    && (value != SEVEN)
                    && (value != EIGHT)
                    && (value != NINE)
                    && (value != TEN)
                    && (value != A)
                    && (value != B)
                    && (value != C)
                    && (value != D)
                    && (value != E)
                    && (value != F)
                    && (value != G)
                    && (value != H)
                    && (value != I)
                    && (value != J))
                {
                    MapGrid[y][x] = INVISIBLE_SHIP;
                }
                else
                {
                    MapGrid[y][x] = OpponentGrid[y - 3][x - 2];
                }
            }
            else if ((y > 2 && y <= 13) && (x > 15 && x <= 26))
            {
                MapGrid[y][x] = PlayerPosGrid[y - 3][x - 16];
            }
			else
				MapGrid[y][x] = STEEL;
		}
	}

	for(int x = 0; x < MAPWIDTH; x++)
	{
		for(int y = 0; y < MAPHEIGHT; y++)
			DrawTile(GameWindow,GraphicSource,x,y,MapGrid[y][x]);
	}

	InvalidateRect(hWndMain,NULL,FALSE);
}

void DrawTile(BitMapObj &BmoDestination, BitMapObj &BmoSource, int x, int y, int TILE)
{
	POINT bitMapPos = FindBitMapPos(TILE);
	BitBlt(BmoDestination,x*TILESIZE,y*TILESIZE,TILESIZE,TILESIZE,BmoSource,WATER*TILESIZE,0,SRCAND);
	BitBlt(BmoDestination,x*TILESIZE,y*TILESIZE,TILESIZE,TILESIZE,BmoSource,bitMapPos.x,bitMapPos.y,SRCCOPY);
}

inline POINT FindBitMapPos(int TILE)
{
	POINT pos;
	pos.x = 0, pos.y = 0;
	pos.x = (TILE % BOARDSIZE) * TILESIZE;
	pos.y = (TILE / BOARDSIZE) * TILESIZE;
	return pos;
}

ActionResult ReadOpponentAction(int Map[][11], std::pair<OpponentAction, XY> action)
{
    if (action.first == OpponentAction::Fire)
    {
        Coordinates position = action.second;
        if (Map[position.y + 1][position.x + 1] != WATER)
        {
            PlayerPosGrid[position.y + 1][position.x + 1] += 80;

            for (std::map<int, std::pair<Ship*, bool>>::size_type i = 0; i < ships.size(); ++i)
            {
                if (ships[i].second)
                {
                    continue;
                }
                else
                {
                    bool sunk = ships[i].first->GetSunkStatus(PlayerPosGrid);

                    if (sunk)
                    {
                        ships[i].second = sunk;
                        return ActionResult::Sunk;
                    }
                }
            }

            return ActionResult::Hit;
        }
        else
        {
            PlayerPosGrid[position.y + 1][position.x + 1] = MISS;
            return ActionResult::Miss;
        }
    }
    else
    {
        OpponentAction action_type = action.first;

        if (action_type == OpponentAction::Ready)
        {
            return ActionResult::Begin;
        }
        else
        {
            int ship_id = Opponent->GetShipId();
            if (ship_id == -1)
            {
                return ActionResult::Begin;
            }
            else
            {
                Movement movement = (Movement)(action.first ^ OpponentAction::MoveFlag);
                Ship* ship = Opponent->GetShips().at(ship_id).first;
                ship->Initialize(OpponentGrid);
                if (MoveShip(ship, OpponentGrid, movement))
                {
                    return ActionResult::Accept;
                }
                else
                {
                    return ActionResult::Accept;
                }
            }
        }
    }
}

void EnemyTurn()
{
    std::pair<OpponentAction, Coordinates> action = Opponent->GetAction();
    ActionResult result = ReadOpponentAction(PlayerPosGrid, action);
    Opponent->ReadResult(result);

    if (result != ActionResult::Accept)
    {
        PLAYERTURN = true;
    }

    RenderMap(HideOpponent);
}

bool MoveShip(Ship * ship, int map[][11], Movement movement)
{
    if (movement == Movement::Rotate)
    {
        ship->Rotate(map);
    }
    else if (movement == Movement::Up)
    {
        ship->Move(-1, 0, map);
    }
    else if (movement == Movement::Down)
    {
        ship->Move(1, 0, map);
    }
    else if (movement == Movement::Left)
    {
        ship->Move(0, -1, map);
    }
    else if (movement == Movement::Right)
    {
        ship->Move(0, +1, map);
    }
    else if (movement == Movement::Set)
    {
        if (!ship->GetPositionedStatus())
        {
            ship->SetPositionedStatus();
            return true;
        }
    }

    return false;
}

void MoveCursor(Coordinates cursor, int map[][11], Movement movement)
{
    if (movement == Movement::Up)
    {
    }

    else if (movement == Movement::Down)
    {
    }

    else if (movement == Movement::Left)
    {
    }

    else if (movement == Movement::Right)
    {
    }
}

GameStatus CheckVictoryStatus(
    std::map<int, std::pair<Ship*, bool>> const &player_ships,
    std::map<int, std::pair<Ship*, bool>> const &opponent_ships)
{
    bool player_alive = false;
    bool opponent_alive = false;

    for (size_t i = (size_t)0; i < player_ships.size(); ++i)
    {
        if (!player_ships.at(i).second)
        {
            player_alive = true;
            break;
        }
    }

    for (size_t i = (size_t)0; i < opponent_ships.size(); ++i)
    {
        if (!opponent_ships.at(i).second)
        {
            opponent_alive = true;
            break;
        }
    }

    if (opponent_alive && player_alive)
        return GameStatus::RUNNING;

    if (opponent_alive)
        return GameStatus::AIWINS;

    if (player_alive)
        return GameStatus::PLAYERWINS;

    return GameStatus::RUNNING;
}