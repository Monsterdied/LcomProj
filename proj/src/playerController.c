#include "models/models.h"
#include "playerController.h"
#include "keyboard.h"
extern int scan_code[2];

bool (PlayerCanWalkTo)(struct Position position,int PlayerNumber, struct ArenaModel* ArenaModel){
    for(int i = 0; i < ArenaModel->nBricks; i++){
        if(ArenaModel->bricks[i].position.x == -1 || ArenaModel->bricks[i].position.y == -1){
            continue;
        }
        if(position.x - 1 == ArenaModel->bricks[i].position.x && position.y == ArenaModel->bricks[i].position.y){
            return false;
        }
    }
    for(int i = 0; i < ArenaModel->nWalls; i++){
        if(ArenaModel->walls[i].position.x == -1 || ArenaModel->walls[i].position.y == -1){
            continue;
        }
        if(position.x - 1 == ArenaModel->walls[i].position.x && position.y == ArenaModel->walls[i].position.y){
            return false;
        }
    }
    for(int i = 0; i < ArenaModel->nBombs; i++){
        if(ArenaModel->bombs[i].position.x == -1 || ArenaModel->bombs[i].position.y == -1){
            continue;
        }
        if(position.x - 1 == ArenaModel->bombs[i].position.x && position.y == ArenaModel->bombs[i].position.y){
            return false;
        }
    }
    if(PlayerNumber == 0){
        if(position.x - 1 == ArenaModel->players[1].position.x && position.y == ArenaModel->players[1].position.y){
            return false;
        }
    }
    if(PlayerNumber == 1){
        if(position.x - 1 == ArenaModel->players[0].position.x && position.y == ArenaModel->players[0].position.y){
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
void updateXmp(int PlayerNumber,struct ArenaModel* ArenaModel){
    if(ArenaModel->players[PlayerNumber].timeUntilNextXpm == 0){
        ArenaModel->players[PlayerNumber].timeUntilNextXpm = ArenaModel->players[PlayerNumber].coldownBetweenXpms;
        if(ArenaModel->players[PlayerNumber].currentXpm + 1 >= ArenaModel->players[PlayerNumber].numberOfImages){
            ArenaModel->players[PlayerNumber].currentXpm = -1;
        }
        ArenaModel->players[PlayerNumber].currentXpm++;
    }
}


void (PlayerController)(int PlayerNumber,struct ArenaModel* ArenaModel){
    kbc_Player1(&ArenaModel->players[PlayerNumber].direction);
    if(ArenaModel->players[PlayerNumber].timeUntilNextXpm - ArenaModel->elapsedTime < 0){
        ArenaModel->players[PlayerNumber].timeUntilNextXpm = 0;
        updateXmp(PlayerNumber,ArenaModel);
    }else{
        ArenaModel->players[PlayerNumber].timeUntilNextXpm -= ArenaModel->elapsedTime;
    }

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
