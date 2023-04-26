//
// Created by diogo on 22/04/2023.
#ifndef BOMBERMAN_MODELS_H
#define BOMBERMAN_MODELS_H
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
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
    int lives;
    int bombs;
    int range;
    int speed;
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
struct Model {
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
#endif //BOMBERMAN_MODELS_H
