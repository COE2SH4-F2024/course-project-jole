#include "Food.h"
#include "Gamemechs.h"
#include "MacUILib.h"

Food::Food(){
    foodBucket = new objPosArrayList();
}

Food::~Food(){
    delete foodBucket;
}
void Food::generateFood(objPosArrayList *Blockoff){

    GameMechs *Gm = new GameMechs();
    srand(time(NULL));
    int count = 0, flag = 0;
    objPos random;
    objPos randomUp;
    objPos randomDown;
    char randSym;
    int xRange = (Gm->getBoardSizeX() -1);
    int yRange = (Gm->getBoardSizeY() -1);

    while(count < 3) //doing 3 normal characters
   {
        flag = 0;
        random.pos->x = rand() % (xRange-1);
        if(random.pos->x == 0) random.pos->x++;
        random.pos->y = rand() % (yRange-1); //get the positions within bounds
        if(random.pos->y == 0) random.pos->y++;
        for(int i = 0; i<Blockoff->getSize(); i++)
            if(random.pos->y == Blockoff->getElement(i).pos->x && random.pos->y == Blockoff->getElement(i).pos->y) flag = 1; //retry if on playerelements
        if(count>0){
            for(int i = 0; i<foodBucket->getSize(); i++){
                if(foodBucket->getElement(i).isPosEqual(&random) || foodBucket->getElement(i).pos->x == (random.pos->x+1) || foodBucket->getElement(i).pos->x == (random.pos->x-1)){
                    flag = 1; 
                }
            }
        }
            //retry if on other food and beside other food on x domain to not cause printing errors
        if(flag == 1) continue;
        
        random.symbol = 'a';
        foodBucket->insertHead(random);
        count++;
    }
      while(count < 5) //doing the special chars that change after 3 normal
   {
        flag = 0;
        random.pos->x = rand() % (xRange-1);
        if(random.pos->x == 0) random.pos->x++;
        random.pos->y = rand() % (yRange-1); //get the positions within bounds
        if(random.pos->y == 0) random.pos->y++;
        for(int i = 0; i<Blockoff->getSize(); i++)
            if(random.pos->x == Blockoff->getElement(i).pos->x && random.pos->y == Blockoff->getElement(i).pos->y) flag = 1; //retry if on playerelements
        if(count>0){
            for(int i = 0; i<foodBucket->getSize(); i++){
                if(foodBucket->getElement(i).isPosEqual(&random) || foodBucket->getElement(i).pos->x == (random.pos->x+1) || foodBucket->getElement(i).pos->x == (random.pos->x-1)){
                    flag = 1; 
                }
            }
        }
            //retry if on other food
        if(flag == 1) continue;
        
        if(count==3)random.symbol = 104; //put the special char are a symbol depending on count
        else random.symbol = 107;
        foodBucket->insertHead(random);
        count++;
    }
    count = 0;

    delete Gm;

}
objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}