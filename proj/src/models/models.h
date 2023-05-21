//
// Created by diogo on 22/04/2023.
#ifndef BOMBERMAN_MODELS_H
#define BOMBERMAN_MODELS_H
enum GameState{
    MENU,
    GAME,
    GAMEOVER,
    EXIT
};
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
enum Motion{
    STAY,
    MOVE
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
struct Bomb {
    struct Position position;
    int time;
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
    enum Motion State;
    int currentXpm;
    int lives;
    int bombs;
    int bombcooldown;
    int range;
    int speed;
    int movementcooldown;
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
    struct Wall walls[100];
    struct Brick bricks[100];
    struct PowerUp powerUps[10];
    int nWalls;
    int nBricks;
    int nPowerUps;
    int nBombs;

};

struct MenuModel {
    int selectedOption;
    int selectedLevel;
    int nlevels;
    int noptions;
};
#endif //BOMBERMAN_MODELS_H
