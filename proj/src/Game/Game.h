#ifndef GAME_H
#define GAME_H
#include "models/models.h"
#include "draw/draw.h"
#include "load.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "gameControllers/Controller.h"
#include "devices/rtc.h"

time_display Game(struct ArenaModel model, enum GameState* state);

#endif // !GAME_H
