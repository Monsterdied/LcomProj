//
// Created by diogo on 22/04/2023.
//

#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H
void draw( struct ArenaModel model);
char (**getemptyArena());
void (drawPlayers)(char** arena, struct ArenaModel model);
void drawBombs(char** arena, struct ArenaModel model);
void drawPowerUps(char** arena, struct ArenaModel model);
void drawBricks(char** arena, struct ArenaModel model);
void (drawWalls)(char** arena, struct ArenaModel model);
#endif //UNTITLED10_DRAW_H
