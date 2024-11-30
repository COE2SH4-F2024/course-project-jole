#include "Food.h"
#include "MacUILib.h"

void Food::generateFood(objPos Blockoff){


    srand(time(NULL));
    int count = 0;
    int randomX, randomY,rIndex, i, flag = 0, realCount = 0;
    char randSym;
/*
    while(count < listSize)
    {
        flag = 0;
        randomX = rand() % (xRange-1);
        if(randomX == 0) randomX++;
        randomY = rand() % (yRange-1);
        if(randomY == 0) randomY++;
        if(randomX == playerPos->x && randomY == playerPos->y) continue;
        for(i=0; i<5; i++)
        {
            if(list[i].x == randomX && list[i].y == randomY)
            {
                flag = 1;
            }
        }
        if(flag == 1) continue;
        list[count].x = randomX;
        list[count].y = randomY;
        count++;
    }
    count = 0;
*/
}
  