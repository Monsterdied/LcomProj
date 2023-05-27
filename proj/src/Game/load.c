//
// Created by diogo on 22/04/2023.
//
#include "models/models.h"
extern int fr_rate;
struct ArenaModel  loadArena(char pString[15][30]){
    struct ArenaModel model;
    
    model.nCoins=0;

    model.returnButton.x = 450;
    model.returnButton.y = 450;
    model.returnButton.width = 150;
    model.returnButton.height = 150;
    model.nWalls=0;
    model.nBombs=0;
    model.nBricks=0;
    model.nPowerUps=0;
    model.nExplosions=0;
    model.elapsedTime = 1/(double)fr_rate;
    model.nScores=0;
    //char buffer[50];  // Adjust the buffer size as per your requirements
    //sprintf(buffer, "%.6f", model.elapsedTime);
    //printf("Double: %s\n", buffer);

    for (int i=0;i<30;i++) {
        for (int j=0;j<15;j++) {
            if(pString[j][i]=='C'){
                model.coins[model.nCoins].position.x=i;
                model.coins[model.nCoins].position.y=j;
                model.coins[model.nCoins].currentXpm=0;
                model.coins[model.nCoins].timeUntilNextXpm=0.3;
                model.nCoins++;
            }
            if(pString[j][i]=='H'){
                model.walls[model.nWalls].position.x=i;
                model.walls[model.nWalls].position.y=j;
                model.nWalls++;
            }
            if(pString[j][i]=='h' || pString[j][i]=='C'){
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
                model.bombs[model.nBombs].timeUntilExplosion=2;
                model.bombs[model.nBombs].timeUntilNextXpm=0.3;
                model.bombs[model.nBombs].range=3;
                model.bombs[model.nBombs].owner=0;
                model.nBombs++;
            }
            if(pString[j][i]=='B'){

                model.players[0].nameSize = 0;
                model.players[0].direction = STAY;
                model.players[0].coldownBetweenXpms=0.3;
                model.players[0].timeUntilNextXpm=0.3;
                model.players[0].currentXpm=0;
                model.players[0].numberOfImages=3;
                model.players[0].position.x=i;
                model.players[0].position.y=j;
                model.players[0].range=1;
                model.players[0].bombs=1;
                model.players[0].speed=1;
                model.players[0].score=0;
                model.players[0].lives=1;
                model.players[0].id=0;
                model.players[0].timeuntilnextmovement=0.3;
                model.players[0].movementcooldown=0.3;
                model.players[0].bombcooldown=0;
            }
            if(pString[j][i]=='b'){
                model.players[1].nameSize = 0;
                model.players[1].direction = STAY;
                model.players[1].coldownBetweenXpms=0.2;
                model.players[1].timeUntilNextXpm=0.2;
                model.players[1].currentXpm=0;
                model.players[1].numberOfImages=3;
                model.players[1].position.x=i;
                model.players[1].position.y=j;
                model.players[1].range=1;
                model.players[1].bombs=1;
                model.players[1].speed=1;
                model.players[1].score=0;
                model.players[1].lives=1;
                model.players[1].id=1;
                model.players[1].timeuntilnextmovement=0.3;
                model.players[1].movementcooldown=0.3;
                model.players[1].bombcooldown=0;
            }
        }
    }
    printf("nCoins: %d\n",model.nCoins);
    printf("nWalls: %d\n",model.nWalls);
    printf("nBombs: %d\n",model.nBombs);
    printf("nBricks: %d\n",model.nBricks);
    printf("nPowerUps: %d\n",model.nPowerUps);
    printf("nExplosions: %d\n",model.nExplosions);
    printf("nlives: %d\n",model.players[1].lives);
    return model;
}

