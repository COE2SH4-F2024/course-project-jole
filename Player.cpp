#include "Player.h"
#include "Food.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(mainGameMechsRef->getBoardSizeX()/2, // place the original player position at the middle of the board
                  mainGameMechsRef->getBoardSizeY()/2,
                  '0');

    playerPosList->insertHead(headPos); // initialize with 1 element which is the head

    mainFoodRef->generateFood(playerPosList); // Generate the first food with the starting head position as its blocked space
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic      
    char input = mainGameMechsRef->getInput();
    
    switch(input)
    {                      
        case 'w':
            if(myDir == STOP || myDir == LEFT || myDir == RIGHT){ // can only turn 90 degrees
                myDir = UP;
            }
            break;
        case 'a':
            if(myDir == STOP || myDir == UP || myDir == DOWN){
                myDir = LEFT;
            }
            break;
        case 's':
            if(myDir == STOP || myDir == LEFT || myDir == RIGHT){
                myDir = DOWN;
            }
            break;
        case 'd':
            if(myDir == STOP || myDir == UP || myDir == DOWN){
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    updatePlayerDir();

    
    objPosArrayList* foodBucket = mainFoodRef->getFoodPos(); 
    int foodSize = foodBucket->getSize();
    objPos temp = playerPosList->getHeadElement(); // create a temp objPos to calculate the new head pos 
    int flag = 0;
    char symbolAte = 0;

    switch(myDir)
    {
        // calculate the new position of the head using the temp objPos
        case DOWN:
            // playerPos.pos->y++;
            // if(playerPos.pos->y >= (mainGameMechsRef->getBoardSizeY() - 1)) playerPos.pos->y = 1;
            temp.pos->y++;
            if(temp.pos->y >= (mainGameMechsRef->getBoardSizeY() - 1)) temp.pos->y = 1;
            break;
        case UP:
            temp.pos->y--;
            if(temp.pos->y <= 0) temp.pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
            break;
        case LEFT:
            temp.pos->x--;
            if(temp.pos->x <= 0) temp.pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
            break;
        case RIGHT:
            temp.pos->x++;
            if(temp.pos->x >= (mainGameMechsRef->getBoardSizeX() - 1)) temp.pos->x= 1;
            break;
        default:
            break;
    }

    // insert temp objPos to the head of the list
        playerPosList->insertHead(temp);
    

    // check if the new temp objPos overlaps with the food position
    for(int i = 0; i< foodSize;i++){
        objPos oneFood = foodBucket->getElement(i);
        symbolAte = oneFood.getSymbolIfPosEqual(&temp);
        if(oneFood.isPosEqual(&temp)){
            // if overlapped, consume the food, and do not remove the snake tail
            if(symbolAte==107) // poisioned food condition
            {
                mainGameMechsRef->setPoisonFlag();
                playerPosList->removeHead();
                flag = 1;
                break;
            }
            else if(symbolAte==104) // regular food
            {
                for(int l = 0; l < 5; l++)
                {
                    mainGameMechsRef->incrementScore();
                    
                }
            }
            for(int k = 0; k< foodSize;k++)
            {
                foodBucket->removeHead();
            }
            mainFoodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore(); // increase the score
            
            flag = 1;
        }
    }
    if(flag==0){
        
        playerPosList->removeTail(); // if no overlap, remove tail
    }
    
    // game end check
    for(int i = 1; i < playerPosList->getSize(); i++){
        objPos thisSeg = playerPosList->getElement(i);

        if(temp.isPosEqual(&thisSeg)){
            playerPosList->removeHead();
            mainGameMechsRef->setLoseFlag();
        }
    }
    
}

// More methods to be added