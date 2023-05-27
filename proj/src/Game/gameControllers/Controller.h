#ifndef UNTITLED10_CONTROLLER_H
#define UNTITLED10_CONTROLLER_H
#pragma once
#include "devices/keyboard.h"
void (PlayerController)(int PlayerNumber,struct ArenaModel* ArenaModel);
bool (PlayerCanWalkTo)(struct Position position,int PlayerNumber, struct ArenaModel* ArenaModel);
bool (PlayerCanWalkLeft)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkRight)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkTop)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkDown)(int PlayerNumber , struct ArenaModel* ArenaModel); 
void (PlayerControllers)(struct ArenaModel* ArenaModel);
void (PlayersSpriteControllers)(struct ArenaModel* model);
void (BombsSpriteControllers)(struct ArenaModel* ArenaModel);
void (ExplosionsController)(struct ArenaModel* arenaModel);
int (PlayersAreAlive)(struct ArenaModel* arenaModel,enum GameState* state);
void (CoinController)(struct ArenaModel* ArenaModel);

#endif //UNTITLED10_CONTROLLER_H
