/**

@file
@brief Game functions
This file contains the main game function.
*/
#ifndef GAME_H
#define GAME_H

#include "models/models.h"
#include "draw/draw.h"
#include "load.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "gameControllers/Controller.h"
#include "devices/rtc.h"

/**
* @brief Game function
*
* The main game function that handles the game logic and updates the game state returns the time it ends.
*
* @param model The initial ArenaModel
* @param state Pointer to the game state
* @return The time the game ends
*/
time_display Game(struct ArenaModel* model, enum GameState* state);


#endif // GAME_H
