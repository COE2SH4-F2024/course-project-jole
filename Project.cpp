#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "GameMechs.h"
#include "Food.h"
#include "Player.h"
#include "Food.h"

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
    myFood = new Food();
    myPlayer = new Player(myGM, myFood);
    
}

void GetInput(void)
{
    myGM->collectAsyncInput();
}


void RunLogic(void)
{
    // if(myGM->getInput() == '=') 
    // {
    //     myGM->incrementScore();
    //     myGM->clearInput();
    // }                                     //this was for testing purposes and debugging
    // if(myGM->getInput() == '-') {
    //     myGM->setLoseFlag();
    //     myGM->clearInput();
    // }

    myPlayer->movePlayer(); 
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

    // get the position of the player and food
    objPosArrayList* Playerpos = myPlayer->getPlayerPos();
    int playerSize = Playerpos->getSize();
    objPosArrayList* foodPos = myFood->getFoodPos();
    int foodSize = foodPos->getSize();

    int boardX = myGM->getBoardSizeX();
    int boardY = myGM->getBoardSizeY();
    

    int printed;

    for(int i=0;i< boardY;i++)
    {
        for(int j=0;j<boardX;j++)
        {
            printed = 0;
            for(int k = 0; k < playerSize; k++){ // print each element of the snake
                
                objPos thisSeg = Playerpos->getElement(k);

                if(i == thisSeg.pos->y && j == thisSeg.pos->x){
                    MacUILib_printf("%c", thisSeg.symbol);
                    printed = 1;
                }
            }

            for(int l= 0; l < foodSize; l++){ // print each food
                
                objPos onefood = foodPos->getElement(l);

                if(i == onefood.pos->y && j == onefood.pos->x){
                    MacUILib_printf("%c", onefood.symbol);
                    printed = 1;
                }
            }
            if(printed == 0){
                if(i == 0 || j == 0 || i == boardY - 1 || j == boardX - 1)  
                    MacUILib_printf("%c", '$');
                else
                    MacUILib_printf("%c", ' '); // print the empty space other than the player on the board
            } 
        }
        MacUILib_printf("\n"); 
    }
    MacUILib_printf("Player[x,y]= [%d,%d] ,Symbol: %c, Score: %d\n", Playerpos->getHeadElement().pos->x,Playerpos->getHeadElement().pos->y,Playerpos->getHeadElement().symbol, myGM->getScore());
    MacUILib_printf("K character is poison BE CAREFUL \nH character is Bonus Points");
    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();
    
    // get lose conditions and print different end screens depending on the lose condition
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == true) MacUILib_printf("You Lose. Better luck next time! Score:%d", myGM->getScore());
    else if(myGM->getExitFlagStatus() == true && myGM->getPoisonFlagStatus() == true) MacUILib_printf("You were poisoned, OH NO! Score:%d", myGM->getScore());
    else MacUILib_printf("Exit Game");

    // plug leaks
    delete myPlayer;
    delete myGM;   
    delete myFood;

    MacUILib_uninit();
}
