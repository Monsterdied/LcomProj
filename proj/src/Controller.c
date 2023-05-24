#include "models/models.h"
#include "Controller.h"
extern int scan_code[2];

bool (PlayerCanWalkTo)(struct Position position,int PlayerNumber, struct ArenaModel* ArenaModel){
    for(int i = 0; i < ArenaModel->nBricks; i++){
        /*if(ArenaModel->bricks[i].position.x == -1 || ArenaModel->bricks[i].position.y == -1){
            continue;
        }*/
        if(position.x  == ArenaModel->bricks[i].position.x && position.y == ArenaModel->bricks[i].position.y){
            return false;
        }
    }
    for(int i = 0; i < ArenaModel->nWalls; i++){

        /*if(ArenaModel->walls[i].position.x == -1 || ArenaModel->walls[i].position.y == -1){
            continue;
        }*/
        if(position.x  == ArenaModel->walls[i].position.x && position.y == ArenaModel->walls[i].position.y){
            return false;
        }
    }
    for(int i = 0; i < ArenaModel->nBombs; i++){
        /*if(ArenaModel->bombs[i].position.x == -1 || ArenaModel->bombs[i].position.y == -1){
            continue;
        }*/
        if(position.x == ArenaModel->bombs[i].position.x && position.y == ArenaModel->bombs[i].position.y){
            return false;
        }
    }
    if(PlayerNumber == 0){
        if(position.x  == ArenaModel->players[1].position.x && position.y == ArenaModel->players[1].position.y){
            return false;
        }
    }
    if(PlayerNumber == 1){
        if(position.x  == ArenaModel->players[0].position.x && position.y == ArenaModel->players[0].position.y){
            return false;
        }
    }
    return true;

}


bool (PlayerCanWalkLeft)(int PlayerNumber , struct ArenaModel* ArenaModel){
    struct Position position ;
    position.x = ArenaModel->players[PlayerNumber].position.x - 1;
    position.y = ArenaModel->players[PlayerNumber].position.y;
    return PlayerCanWalkTo(position,PlayerNumber ,ArenaModel);
}

bool (PlayerCanWalkRight)(int PlayerNumber, struct ArenaModel* ArenaModel){
    struct Position position ;
    position.x = ArenaModel->players[PlayerNumber].position.x + 1;
    position.y = ArenaModel->players[PlayerNumber].position.y;
    return PlayerCanWalkTo(position,PlayerNumber ,ArenaModel);
}
bool (PlayerCanWalkDown)(int PlayerNumber, struct ArenaModel* ArenaModel){
    struct Position position ;
    position.x = ArenaModel->players[PlayerNumber].position.x ;
    position.y = ArenaModel->players[PlayerNumber].position.y + 1;
    return PlayerCanWalkTo(position,PlayerNumber ,ArenaModel);
}
bool (PlayerCanWalkUp)(int PlayerNumber, struct ArenaModel* ArenaModel){
    struct Position position ;
    position.x = ArenaModel->players[PlayerNumber].position.x ;
    position.y = ArenaModel->players[PlayerNumber].position.y - 1;
    return PlayerCanWalkTo(position,PlayerNumber ,ArenaModel);
}

void (kbc_Player1)(enum Direction *action){
    if(scan_code[0] == 0x1e){
        *action = LEFT;
    }else if(scan_code[0] == 0x9e && *action == LEFT){
        *action = STAY;
    }else  if(scan_code[0] == 0x1f){
        *action = DOWN;
    }else if(scan_code[0] == 0x9f && *action == DOWN){
        *action = STAY;
    }else  if(scan_code[0] == 0x11){
        *action = UP;
    }else if(scan_code[0] == 0x91 && *action == UP){
        *action = STAY;
    }else  if(scan_code[0] == 0x20){
        *action = RIGHT;
    }else if(scan_code[0] == 0xa0 && *action == RIGHT){
        *action = STAY;
    }
}
void (kbc_Player2)(enum Direction *action){
    if(scan_code[0] == 0x4B){
        *action = LEFT;
    }else if(scan_code[0] == 0xCB && *action == LEFT){
        *action = STAY;
    }else  if(scan_code[0] == 0x50){
        *action = DOWN;
    }else if(scan_code[0] == 0xD0 && *action == DOWN){
        *action = STAY;
    }else  if(scan_code[0] == 0x48){
        *action = UP;
    }else if(scan_code[0] == 0xC8 && *action == UP){
        *action = STAY;
    }else  if(scan_code[0] == 0x4D){
        *action = RIGHT;
    }else if(scan_code[0] == 0xCD && *action == RIGHT){
        *action = STAY;
    }
}

void (updateXmp)(int PlayerNumber,struct ArenaModel* ArenaModel){
    ArenaModel->players[PlayerNumber].timeUntilNextXpm -= ArenaModel->elapsedTime;
    if(ArenaModel->players[PlayerNumber].timeUntilNextXpm <= 0){
        ArenaModel->players[PlayerNumber].timeUntilNextXpm = ArenaModel->players[PlayerNumber].coldownBetweenXpms;
        if(ArenaModel->players[PlayerNumber].currentXpm + 1 >= ArenaModel->players[PlayerNumber].numberOfImages){
            ArenaModel->players[PlayerNumber].currentXpm = -1;
        }
        ArenaModel->players[PlayerNumber].currentXpm++;
    }
}

void(movePlayer)(int PlayerNumber,struct ArenaModel* ArenaModel){
    
    switch (ArenaModel->players[PlayerNumber].direction){
        case UP:
            if(PlayerCanWalkUp(PlayerNumber,ArenaModel)){
                ArenaModel->players[PlayerNumber].position.y--;
            }
            break;
        case DOWN:
            if(PlayerCanWalkDown(PlayerNumber,ArenaModel)){
                ArenaModel->players[PlayerNumber].position.y++;
            }
            break;
        case LEFT:
            if(PlayerCanWalkLeft(PlayerNumber,ArenaModel)){
                ArenaModel->players[PlayerNumber].position.x--;
            }
            break;
        case RIGHT:
            if(PlayerCanWalkRight(PlayerNumber,ArenaModel)){
                ArenaModel->players[PlayerNumber].position.x++;
            }
            break;
        default:
            break;
    }
}
void (kbc_Bomb)(struct ArenaModel* ArenaModel){
    if(scan_code[0] == 0x39){
        if(ArenaModel->players[0].bombs > 0){
            ArenaModel->players[0].bombs--;
            ArenaModel->bombs[ArenaModel->nBombs].position.x = ArenaModel->players[0].position.x;
            ArenaModel->bombs[ArenaModel->nBombs].position.y = ArenaModel->players[0].position.y;
            ArenaModel->bombs[ArenaModel->nBombs].timeUntilExplosion = 1;
            ArenaModel->bombs[ArenaModel->nBombs].timeUntilNextXpm = 0.3;
            ArenaModel->bombs[ArenaModel->nBombs].range = 3+ ArenaModel->players[0].range;
            ArenaModel->bombs[ArenaModel->nBombs].owner = 0;
            ArenaModel->nBombs++;
            ArenaModel->players[0].bombcooldown = 3;
        }
    }else if(scan_code[0] == 0x52){
        if(ArenaModel->players[1].bombs > 0){
            ArenaModel->players[1].bombs--;
            ArenaModel->bombs[ArenaModel->nBombs].position.x = ArenaModel->players[1].position.x;
            ArenaModel->bombs[ArenaModel->nBombs].position.y = ArenaModel->players[1].position.y;
            ArenaModel->bombs[ArenaModel->nBombs].timeUntilExplosion = 1;
            ArenaModel->bombs[ArenaModel->nBombs].timeUntilNextXpm = 0.3;
            ArenaModel->bombs[ArenaModel->nBombs].range = 3+ ArenaModel->players[1].range;
            ArenaModel->bombs[ArenaModel->nBombs].owner = 1;
            ArenaModel->nBombs++;
            ArenaModel->players[1].bombcooldown = 3;
        }

    }
}

void (PlayerControllers)(struct ArenaModel* arenaModel){
    kbc_Player1(&arenaModel->players[0].direction);
    kbc_Player2(&arenaModel->players[1].direction);
    kbc_Bomb(arenaModel);
}
void (PlayerSpriteController)(int PlayerNumber, struct ArenaModel* ArenaModel){
    if(ArenaModel->players[PlayerNumber].direction!= STAY){
            updateXmp(PlayerNumber,ArenaModel);
    }else{
        ArenaModel->players[PlayerNumber].currentXpm = 0;
    }
    if(ArenaModel->players[PlayerNumber].timeuntilnextmovement>0){
        ArenaModel->players[PlayerNumber].timeuntilnextmovement -= ArenaModel->elapsedTime;
    }
    if(ArenaModel->players[PlayerNumber].timeuntilnextmovement <= 0 && ArenaModel->players[PlayerNumber].direction != STAY){
        ArenaModel->players[PlayerNumber].timeuntilnextmovement = ArenaModel->players[PlayerNumber].movementcooldown;
        movePlayer(PlayerNumber,ArenaModel);
    }
}

void (PlayersSpriteControllers)(struct ArenaModel* arenaModel){
    PlayerSpriteController(0,arenaModel);
    PlayerSpriteController(1,arenaModel);
    
}
int (burn)(int x,int y,struct ArenaModel* arenaModel,enum Direction direction){
    for(int i = 0; i < arenaModel->nBricks; i++){
        if(arenaModel->bricks[i].position.x == x && arenaModel->bricks[i].position.y == y){
            arenaModel->bricks[i] = arenaModel->bricks[arenaModel->nBricks-1];
            arenaModel->nBricks--;
            arenaModel->explosions[arenaModel->nExplosions].position.x = x;
            arenaModel->explosions[arenaModel->nExplosions].position.y = y;
            arenaModel->explosions[arenaModel->nExplosions].direction = direction;
            arenaModel->explosions[arenaModel->nExplosions].timeUntilNextXpm = 0.3;
            arenaModel->explosions[arenaModel->nExplosions].currentXpm = 0;
            arenaModel->explosions[arenaModel->nExplosions].timeUntilFade = 1;
            arenaModel->nExplosions++;
            return 0;
        }
    }
    for(int i = 0; i < arenaModel->nWalls; i++){
        if(arenaModel->walls[i].position.x == x && arenaModel->walls[i].position.y == y){
            return 1;
        }
    }
    for(int i = 0; i < arenaModel->nBombs; i++){
        if(arenaModel->bombs[i].position.x == x && arenaModel->bombs[i].position.y == y){
            arenaModel->bombs[i].timeUntilExplosion = 0;
            arenaModel->explosions[arenaModel->nExplosions].position.x = x;
            arenaModel->explosions[arenaModel->nExplosions].position.y = y;
            arenaModel->explosions[arenaModel->nExplosions].direction = direction;
            arenaModel->explosions[arenaModel->nExplosions].timeUntilNextXpm = 0.3;
            arenaModel->explosions[arenaModel->nExplosions].currentXpm = 0;
            arenaModel->explosions[arenaModel->nExplosions].timeUntilFade = 1;
            arenaModel->nExplosions++;

            return 0;
        }
    }
    for(int i = 0; i < 2; i++){
        if(arenaModel->players[i].position.x == x && arenaModel->players[i].position.y == y){
            arenaModel->players[i].lives--;
            return 0;
        }
    }
    arenaModel->explosions[arenaModel->nExplosions].position.x = x;
    arenaModel->explosions[arenaModel->nExplosions].position.y = y;
    arenaModel->explosions[arenaModel->nExplosions].direction = direction;
    arenaModel->explosions[arenaModel->nExplosions].timeUntilNextXpm = 0.3;
    arenaModel->explosions[arenaModel->nExplosions].currentXpm = 0;
    arenaModel->explosions[arenaModel->nExplosions].timeUntilFade = 1;
    arenaModel->nExplosions++;
    return 0;

}
void (BombExplosion)(int i,struct ArenaModel* arenaModel){
    int x = arenaModel->bombs[i].position.x;
    int y = arenaModel->bombs[i].position.y;
    burn(x,y,arenaModel,STAY);
    for(int i=1;i>=arenaModel->bombs[i].range;i++)
        if(x+i<30 && burn(x+i,y,arenaModel,RIGHT)) break;
            
    for(int i=1;i>=arenaModel->bombs[i].range;i++)
        if(x-i>=0 && burn(x-i,y,arenaModel,LEFT)) break;

    for(int i=1;i>=arenaModel->bombs[i].range;i++)     
        if(y+i<15 && burn(x,y+i,arenaModel,DOWN)) break;
        
    for(int i=1;i>=arenaModel->bombs[i].range;i++)        
        if(y-i>=0 && burn(x,y-i,arenaModel,UP)) break;   
            
    



}
void (BombsSpriteControllers)(struct ArenaModel* arenaModel){
    for(int i = 0; i < arenaModel->nBombs; i++){
        arenaModel->bombs[i].timeUntilExplosion -= arenaModel->elapsedTime;
        if(arenaModel->bombs[i].timeUntilExplosion <= 0){
            BombExplosion(i,arenaModel);
            arenaModel->bombs[i] = arenaModel->bombs[arenaModel->nBombs-1];
            arenaModel->nBombs--;
        }else{
            arenaModel->bombs[i].timeUntilNextXpm -= arenaModel->elapsedTime;
            if(arenaModel->bombs[i].timeUntilNextXpm <= 0){
                arenaModel->bombs[i].timeUntilNextXpm = 0.3;
                if(arenaModel->bombs[i].currentXpm + 1 >= 3){
                    arenaModel->bombs[i].currentXpm = -1;
                }
                arenaModel->bombs[i].currentXpm++;
            }
        }
    }
}
void (ExplosionsController)(struct ArenaModel* arenaModel){
    for(int i = 0; i < arenaModel->nExplosions; i++){
        arenaModel->explosions[i].timeUntilNextXpm -= arenaModel->elapsedTime;
        if(arenaModel->explosions[i].timeUntilNextXpm <= 0){
            arenaModel->explosions[i].timeUntilNextXpm = 0.3;
            if(arenaModel->explosions[i].currentXpm + 1 >= 2){
                arenaModel->explosions[i].currentXpm = -1;
            }
            arenaModel->explosions[i].currentXpm++;
        }
        arenaModel->explosions[i].timeUntilFade -= arenaModel->elapsedTime;
        if(arenaModel->explosions[i].timeUntilFade <= 0){
            arenaModel->explosions[i] = arenaModel->explosions[arenaModel->nExplosions-1];
            arenaModel->nExplosions--;
            i--;
        }
    }

}
void (PlayersAreAlive)(struct ArenaModel* arenaModel,enum GameState* state){
    if(arenaModel->players[0].lives <= 0){
        *state = PLAYER2WON;
    }
    if(arenaModel->players[1].lives <= 0){
        *state = PLAYER1WON;
    }
}

