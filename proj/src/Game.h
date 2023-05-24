#ifndef GAME_H
#define GAME_H
#include "models/models.h"
#include "draw.h"
#include "load.h"
#include "keyboard.h"
#include "mouse.h"
#include "playerController.h"

void Game(struct ArenaModel model, enum GameState* state);

#endif // !GAME_H
