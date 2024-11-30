#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Food.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;
Food *myFood;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    myFood = new Food();
    myFood->generateFood(myPlayer->getPlayerPos());
    
}

void GetInput(void)
{
    myGM->collectAsyncInput();
}

void RunLogic(void)
{
    if(myGM->getInput() == '=') 
    {
        myGM->incrementScore();
        myGM->clearInput();
    }
    if(myGM->getInput() == '-') {
        myGM->setLoseFlag();
        myGM->clearInput();
    }
    myPlayer->movePlayer(); 
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    objPos Playerpos = myPlayer->getPlayerPos();
    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    objPos foodPos = myFood->getFoodPos();

    for(int i=0;i< boardY;i++)
    {
        for(int j=0;j<boardX;j++)
        {
            if(i == 0 || j == 0 || i == boardY - 1 || j == boardX - 1)
                MacUILib_printf("%c", '$');
            else if(i == Playerpos.pos->y && j == Playerpos.pos->x)
                MacUILib_printf("%c", Playerpos.symbol);
            else if(i == foodPos.pos->y && j == foodPos.pos->x)
                MacUILib_printf("%c", foodPos.symbol);
            else
                 MacUILib_printf("%c", ' '); 
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("Player[x,y]= [%d,%d] ,Symbol: %c, Score: %d\n", Playerpos.pos->x,Playerpos.pos->y,Playerpos.symbol, myGM->getScore());
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == true) MacUILib_printf("You LOSE :(");
    else if(myGM->getExitFlagStatus() == true) MacUILib_printf("Exit Game");

    delete myPlayer;
    delete myGM;   
    delete myFood;

    MacUILib_uninit();
}
