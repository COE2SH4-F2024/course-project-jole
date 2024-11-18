#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.pos->y = mainGameMechsRef->getBoardSizeY()/2;
    playerPos.symbol = '0';
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic      
    char input = mainGameMechsRef->getInput();
    
    if(input != 0)  // if not null character
    {
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
        input = 0;
    }
    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    if(myDir == UP){ // movement and wraparound for the player
        if(playerPos.pos->y == 1){
            playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;
        }
        else{
            playerPos.pos->y--;
        }
    }
    else if(myDir == DOWN){
        if(playerPos.pos->y == mainGameMechsRef->getBoardSizeY() - 2){
            playerPos.pos->y = 1;
        }
        else{
            playerPos.pos->y++;
        }
    }
    else if(myDir == LEFT){
        if(playerPos.pos->x == 1){
            playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;
        }
        else{
            playerPos.pos->x--;
        }
    }
    else if(myDir == RIGHT){
        if(playerPos.pos->x == mainGameMechsRef->getBoardSizeX() - 2){
            playerPos.pos->x = 1;
        }
        else{
            playerPos.pos->x++;
        }
    }
}

// More methods to be added