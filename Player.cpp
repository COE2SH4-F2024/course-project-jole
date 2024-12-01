#include "Player.h"
#include "Food.h"

Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    playerPosList = new objPosArrayList();
    myDir = STOP;

    objPos headPos(mainGameMechsRef->getBoardSizeX()/2,
                  mainGameMechsRef->getBoardSizeY()/2,
                  '0');

    playerPosList->insertHead(headPos); // initialize with 1 element which is the head

    mainFoodRef->generateFood(playerPosList);
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
        // case ' ':  // exit
        //     exitFlag = 1;
        //     break;
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

    // create a temp objPos to calculate the new head pos - probably should get the head element of the playerPosList as a good starting point
    objPos temp = playerPosList->getHeadElement();

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
    if(temp.pos->x == mainFoodRef->getFoodPos().pos->x && temp.pos->y == mainFoodRef->getFoodPos().pos->y){
        // if overlapped, consume the food, and do not remove the snake tail
        mainFoodRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore(); // increase the score
    }
    else{
        playerPosList->removeTail(); // if no overlap, remove tail
    }
    
    // game end check
    for(int i = 1; i < playerPosList->getSize(); i++){
        objPos thisSeg = playerPosList->getElement(i);

        if(temp.pos->x == thisSeg.pos->x && temp.pos->y == thisSeg.pos->y){
            mainGameMechsRef->setLoseFlag();
        }
    }
    
}

// More methods to be added