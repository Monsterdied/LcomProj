//
// Created by diogo on 22/04/2023.
//

#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H
void draw( struct Model model);
char (**getemptyArena());
void (drawPlayers)(char** arena, struct Model model);
void drawBombs(char** arena, struct Model model);
void drawPowerUps(char** arena, struct Model model);
void drawBricks(char** arena, struct Model model);
void (drawWalls)(char** arena, struct Model model);
#endif //UNTITLED10_DRAW_H
