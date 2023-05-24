//
// Created by diogo on 22/04/2023.
#ifndef BOMBERMAN_MODELS_H
#define BOMBERMAN_MODELS_H

#include "devices/video_gr.h"

enum GameState{
    MENU,
    GAME,
    GAMEOVER,
    EXIT,
    PLAYER1WON,
    PLAYER2WON,
};
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY
};

enum PowerUpType {
    BOMB,
    RANGE,
    SPEED
};
struct Position {
    int x;
    int y;
};
struct Explosion {
    struct Position position;
    enum Direction direction;
    double timeUntilNextXpm;
    double timeUntilFade;
    int currentXpm;
};
struct Bomb {
    struct Position position;
    double timeUntilExplosion;
    double timeUntilNextXpm;
    int currentXpm;
    int range;
    int owner;
};
struct Player {
    enum Direction direction;
    struct Position position;
    xpm_image_t Left[3] ;
    xpm_image_t Right[3] ;
    xpm_image_t Up[3] ;
    xpm_image_t Down[3];
    int numberOfImages;
    int currentXpm;
    double timeUntilNextXpm;
    double coldownBetweenXpms;
    int lives;
    int bombs;
    int bombcooldown;
    int range;
    int speed;
    double timeuntilnextmovement;
    double movementcooldown;
    int score;
    int id;
};
struct Wall {
    struct Position position;
};
struct Brick {
    struct Position position;
};
struct PowerUp {
    struct Position position;
    enum PowerUpType type;
};
struct ArenaModel {
    struct Player players[2];
    struct Bomb bombs[6];
    struct Wall walls[450];
    struct Brick bricks[450];
    struct Explosion explosions[450];
    struct PowerUp powerUps[10];
    double elapsedTime;
    int nWalls;
    int nBricks;
    int nPowerUps;
    int nBombs;
    int nExplosions;

};

struct MenuModel {
    int selectedOption;
    int selectedLevel;
    int nlevels;
    int noptions;
};
#endif //BOMBERMAN_MODELS_H
