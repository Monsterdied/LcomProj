//
// Created by diogo on 22/04/2023.
//
#include "models/models.h"
struct ArenaModel  loadArena(char pString[15][30]){
    struct ArenaModel model;
    model.nWalls=0;
    model.nBombs=0;
    model.nBricks=0;
    model.nPowerUps=0;
    for (int i=0;i<30;i++) {
        for (int j=0;j<15;j++) {
            if(pString[j][i]=='H'){
                model.walls[model.nWalls].position.x=i;
                model.walls[model.nWalls].position.y=j;

                model.nWalls++;
            }
            if(pString[j][i]=='h'){
                model.bricks[model.nBricks].position.x=i;
                model.bricks[model.nBricks].position.y=j;
                model.nBricks++;
            }
            if(pString[j][i]=='P'){
                model.powerUps[model.nPowerUps].position.x=i;
                model.powerUps[model.nPowerUps].position.y=j;
                model.powerUps[model.nPowerUps].type=BOMB;
                model.nPowerUps++;
            }
            if(pString[j][i]=='O'){
                model.bombs[model.nBombs].position.x=i;
                model.bombs[model.nBombs].position.y=j;
                model.nBombs++;
            }
            if(pString[j][i]=='B'){
                model.players[0].position.x=i;
                model.players[0].position.y=j;
                model.players[0].range=1;
                model.players[0].bombs=1;
                model.players[0].speed=1;
                model.players[0].score=0;
                model.players[0].lives=1;
                model.players[0].id=0;
                model.players[0].movementcooldown=0;
                model.players[0].bombcooldown=0;
            }
            if(pString[j][i]=='b'){
                model.players[1].position.x=i;
                model.players[1].position.y=j;
                model.players[1].range=1;
                model.players[1].bombs=1;
                model.players[1].speed=1;
                model.players[1].score=0;
                model.players[1].lives=1;
                model.players[1].id=1;
                model.players[1].movementcooldown=0;
                model.players[1].bombcooldown=0;
            }
        }
    }

    return model;
}
