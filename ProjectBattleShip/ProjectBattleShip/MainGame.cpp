///==================================================================
/// Project Created By: Steven Shriver
/// Date March 2012
/// This probably wouldn't happen but if this program crashes your
/// computer... I will not be held liable
/// Enjoy and report all bugs/comments/ideas/fixes you come up with
///
///==================================================================

#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<stdlib.h>
#include<DShow.h>
#include"MapComponents.h"
#include"_BitMapObj.h"
#include"Ships.h"
#include"BattleshipOpponent.h"

#define WINDOWCLASS "Battling Ships"
#define WINDOWTITLE "BATTLEFIELD"

CHAR  WarningMessage[] = "You are about to exit the game!\nAre you sure this is what you want to do?";

//The Buttons----------------------------------------------------------------
//HWND GridButtons[GRIDSIZE-1][GRIDSIZE-1];
//int ButtonIds[GRIDSIZE-1][GRIDSIZE-1];
int Id = 100;//start id for the buttons
typedef struct ButtonSpecs
{
	HWND Button;
	//BitMapObj BitMap;
	int ID;
	int xCoordinate;
	int yCoordinate;
	//ButtonSpecs* _Me;
}mButton;

mButton GridButtons[GRIDSIZE-1][GRIDSIZE-1];

//Ship Declarations ------------------------------------------------------------------------------
Carrier    PlayerCarrier;
BattleShip PlayerBattleShip;
Destroyer  PlayerCruiser;
Submarine  PlayerSub;
Patroller  PlayerPatrol;

Ship * ships[5] = { &PlayerCarrier, &PlayerBattleShip, &PlayerCruiser, &PlayerSub, &PlayerPatrol };

BattleShipOpponent* BtlShpOp = new BattleShipOpponent(new Probability(), 1);

//End ships---------------------------------------------------------------------------------------
int ShipId;

enum Movement
{
      Set    = VK_RETURN
    , Rotate = VK_SPACE
    , Left   = VK_LEFT
    , Up     = VK_UP
    , Right  = VK_RIGHT
    , Down   = VK_DOWN
};

//Game Functions------------------------------------------------------------
void NewGame();
void EnemyTurn();
bool Setup(Ship * ships[]);
void MoveShip(Ship * ship, int map[][11], Movement movement);
void DrawTile(BitMapObj &BmoDestination, BitMapObj &BmoSource, int x, int y, int TILE);
void RenderMap();
void mCreateButton_xy(mButton &button, int x, int y);
POINT FindBitMapPos(int TILE);
bool GameInitialize();
//End Game Functions---

//Some Booleans For GamePlay
bool SUNK = false;
bool PLAYERTURN = true;
bool ENEMYTURN = false;
bool GameStarted = false;

int SHIPCOUNT = 5;
long MouseX;
long MouseY;
POINT cursorPos;

//The Main Window and Its Instance-------------------------------------------
HINSTANCE hInstanceMain = NULL;
HWND      hWndMain      = NULL;
HWND      hWndOptions   = NULL;
HWND      NewGameBtn    = NULL;
HWND      SurrenderBtn  = NULL;
HWND      ExitBtn       = NULL;


//BitMapObjects for holding the Graphics-------------------------------------
BitMapObj Map;
BitMapObj AttackGridMap;
BitMapObj PlayerPosGridMap;
BitMapObj Source;

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
				RenderMap();
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
				AttackGrid[GridButtons[i][j].yCoordinate+1][GridButtons[i][j].xCoordinate+1] = HIT;
				SendMessage(GridButtons[i][j].Button,BM_SETIMAGE,(WPARAM)IMAGE_BITMAP,TRANSPARENT);
				EnableWindow(GridButtons[i][j].Button,FALSE);
				ShowWindow(GridButtons[i][j].Button,SW_HIDE);

                PLAYERTURN = false;

				RenderMap();
				return 0;
			}break;

		case WM_KEYDOWN://-------------------------------First Case
			{
				if(wParam == VK_ESCAPE){
					if(MessageBox(NULL,WarningMessage,"Leave Game?",MB_ICONEXCLAMATION|MB_YESNOCANCEL)==IDYES)
						DestroyWindow(hWndMain);
					return 0;
				}
                else
                {
                    MoveShip(ships[ShipId], PlayerPosGrid, (Movement)wParam);
					RenderMap();
					return 0;
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
				BitBlt(BtnHdc,0,0,TILESIZE,TILESIZE,Source,0,0,SRCAND);

				EndPaint(GridButtons[i][j].Button,&BtnPaint);
				return 0;
			}break;

		case WM_PAINT:
			{
				PAINTSTRUCT paint;
				HDC hdc;
				hdc = BeginPaint(hwnd,&paint);
				BitBlt(hdc,0,0,MAPWIDTH*TILESIZE,MAPHEIGHT*TILESIZE,Map,0,0,SRCCOPY);

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

	MSG MainMsg;
	
	for(;;)
	{
		if(PeekMessage(&MainMsg,NULL,0,0,PM_REMOVE))
		{
			if(MainMsg.message == WM_QUIT)
				break;
			TranslateMessage(&MainMsg);
			DispatchMessage(&MainMsg);
		}
		if(GameStarted == false)
		{
            GameStarted = Setup(ships);
            continue;
		}
		if(!PLAYERTURN)
		    EnemyTurn();
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
		tempRect.right - tempRect.left,
		tempRect.bottom -tempRect.top,
		SWP_NOMOVE);

	HDC hdc = GetDC(hWndMain);
	Map.Create(hdc,MAPWIDTH * TILESIZE, MAPWIDTH * TILESIZE);
	FillRect(Map,&tempRect,(HBRUSH)GetStockObject(NULL_BRUSH));
	ReleaseDC(hWndMain,hdc);

	Source.Load(NULL,(LPCTSTR)"tiles3.bmp");

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
	ShipId = -1;
	for(int i = 0; i < GRIDSIZE; i++)
	{
		for(int j = 0; j < GRIDSIZE; j++)
		{
			if(i==0&&j==0){
				AttackGrid[i][j] = MISS;
				PlayerPosGrid[i][j] = MISS;
			}
			else if(i==0&&j>=1){
				AttackGrid[i][j] = 19+j;
				PlayerPosGrid[i][j] = 19+j;
			}
			else if(j==0&&i>=1){
				AttackGrid[i][j] = 9+i;
				PlayerPosGrid[i][j] = 9+i;
			}
			else{
				AttackGrid[i][j] = WATER;
				PlayerPosGrid[i][j] = WATER;
			}
		}
	}

	RenderMap();
}

bool Setup(Ship * ships[])
{
    if (ShipId == -1)
    {
        ShipId = 0;
        ships[ShipId]->Initialize(PlayerPosGrid);
    }

    if (ships[ShipId]->GetPositionedStatus())
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
        ships[ShipId]->Initialize(PlayerPosGrid); 
    }

    RenderMap();

    return false;
}

void RenderMap()
{
	for(int y = 0; y < MAPHEIGHT; y++)
	{
		for(int x = 0; x < MAPWIDTH; x++)
		{
			if((y>2 && y<=13)&&(x>1&&x<=12))
				MapGrid[y][x] = AttackGrid[y-3][x-2];
			else if((y>2 && y<=13)&&(x>15&&x<=26))
				MapGrid[y][x] = PlayerPosGrid[y-3][x-16];
			else
				MapGrid[y][x] = STEEL;
		}
	}

	for(int x = 0; x < MAPWIDTH; x++)
	{
		for(int y = 0; y < MAPHEIGHT; y++)
			DrawTile(Map,Source,x,y,MapGrid[y][x]);
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

AttackResult LaunchMissile(int Map[][11], XY position)
{
    if (Map[position.y+1][position.x+1] != WATER)
    {
        PlayerPosGrid[position.y+1][position.x+1] += 80;
        return AttackResult::Hit;
    }
    else
    {
        PlayerPosGrid[position.y+1][position.x+1] = MISS;
        return AttackResult::Miss;
    }
}

void EnemyTurn()
{
	BtlShpOp->Update();
    XY choice = BtlShpOp->GetChoice();
    LaunchMissile(PlayerPosGrid, choice);
    //BtlShipOp->ReadResult(LaunchMissile(PlayerPosGrid, choice));

	RenderMap();

    PLAYERTURN = true;
}

void MoveShip(Ship * ship, int map[][11], Movement movement)
{
    if (movement == Movement::Rotate)
        ship->Rotate(PlayerPosGrid);

    else if (movement == Movement::Up)
    {
        ship->Move(-1, 0, PlayerPosGrid);
    }

    else if (movement == Movement::Down)
    {
        ship->Move(1, 0, PlayerPosGrid);
    }

    else if (movement == Movement::Left)
    {
        ship->Move(0, -1, PlayerPosGrid);
    }

    else if (movement == Movement::Right)
    {
        ship->Move(0, +1, PlayerPosGrid);
    }

    else if (movement == Movement::Set)
    {
        if (!ship->GetPositionedStatus())
            ship->SetPositionedStatus();
    }
}

