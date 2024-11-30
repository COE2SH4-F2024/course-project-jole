#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer;
GameMechs *myGM;



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

    objPosArrayList* Playerpos = myPlayer->getPlayerPos();
    int playerSize = Playerpos->getSize();

    //objPos foodPos = myGM->getFoodPos();

    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();

    for(int i=0;i< boardY;i++)
    {
        for(int j=0;j<boardX;j++)
        {
            int printed = 0;
            // iterate through the playerPosArrayList to print all the segments
            for(int k = 0; k < playerSize; k++){
                int printed = 0;
                objPos thisSeg = Playerpos->getElement(k);

                // check if the current segment x, y pos matches (j, i) coordinate
                //      if yes, print the symbol
                if(i == thisSeg.pos->y && j == thisSeg.pos->x){
                    MacUILib_printf("%c", thisSeg.symbol);
                    printed = 1;
                }
                // watch out: skip the if-else block if something is printed in here
            }

            if (printed == 0){ // skip printing if a player segment has been printed in this i, j
                if(i == 0 || j == 0 || i == boardY - 1 || j == boardX - 1)
                    MacUILib_printf("%c", '$');
                else
                    MacUILib_printf("%c", ' '); 
            }
            else continue;
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("Player[x,y]= [%d,%d] ,Symbol: %c, Score: %d\n", Playerpos->getHeadElement().pos->x,Playerpos->getHeadElement().pos->y,Playerpos->getHeadElement().symbol, myGM->getScore());
    
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

    MacUILib_uninit();
}
