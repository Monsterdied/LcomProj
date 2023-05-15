//
// Created by diogo on 22/04/2023.
//

#include <stdio.h>
#include <malloc.h>
#include "models/models.h"
#include "draw.h"

void (drawWalls)(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nWalls;i++){
        arena[model.walls[i].position.x][model.walls[i].position.y]=  'H';
    }
}
void drawBricks(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nBricks;i++){
        arena[model.bricks[i].position.x][model.bricks[i].position.y]=  'h';
    }
}
void drawPowerUps(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nPowerUps;i++){
        arena[model.powerUps[i].position.x][model.powerUps[i].position.y]=  'P';
    }
}
void drawBombs(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nBombs;i++){
        arena[model.bombs[i].position.x][model.bombs[i].position.y]=  'B';
    }
}
void (drawPlayers)(char** arena, struct ArenaModel model){
    for(int i=0;i<2;i++){
//        printf("\n%d\n",model.players[i].id);
        if(model.players[i].id==0)
            arena[model.players[i].position.x][model.players[i].position.y]='P';
        else arena[model.players[i].position.x][model.players[i].position.y]='p';
    }
}
char (**getemptyArena()) {
    char** arena = (char**) malloc(15 * sizeof(char*));
    for (int i = 0; i < 15; i++) {
        arena[i] = (char*) malloc(30 * sizeof(char));
        for (int j = 0; j < 30; j++) {
            arena[i][j] = '_';
        }
    }
    return arena;
}
void draw( struct ArenaModel model){
    char** arena=getemptyArena();
    drawWalls(arena, model);
    drawBricks(arena, model);
    drawPowerUps(arena, model);
    drawBombs(arena, model);
    drawPlayers(arena, model);

    for (int i=0;i<30;i++) {
        printf("\n");
        for(int j=0;j<15;j++)
            printf("%c",arena[j][i]);

    }
}
