#include "Food.h"
#include "Gamemechs.h"
#include "MacUILib.h"

Food::Food(){

}

Food::~Food(){

}
void Food::generateFood(objPos Blockoff){

    GameMechs *Gm = new GameMechs();
    srand(time(NULL));
    int count = 0;
    int randomX, randomY;
    char randSym;
    int xRange = (Gm->getBoardSizeX() -1);
    int yRange = (Gm->getBoardSizeY() -1);

    while(count < 1) //only doing 1 now
   {
        randomX = rand() % (xRange-1);
        if(randomX == 0) randomX++;
        randomY = rand() % (yRange-1);
        if(randomY == 0) randomY++;
        if(randomX == Blockoff.pos->x && randomY == Blockoff.pos->y) continue;
        // for(i=0; i<5; i++)
        // {
        //     if(food.pos->x == randomX && food.pos->y == randomY)
        //     {
        //         flag = 1;
        //     }
        // }
        // if(flag == 1) continue;
        food.pos->x = randomX;
        food.pos->y = randomY;
        count++;
    }
    count = 0;
    randSym = (rand() % 93) + 33;
    food.symbol = randSym;

    delete[] Gm;

}
objPos Food::getFoodPos() const
{
    return food;
}