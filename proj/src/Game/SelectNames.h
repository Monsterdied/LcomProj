/**

@file
@brief Select Names functions
This file contains functions related to selecting player names.
*/
#ifndef SELECTNAMES_H
#define SELECTNAMES_H

#include <stdlib.h>
#include "models/models.h"
#include "draw/draw.h"
#include "load.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "gameControllers/kbc_controller.h"

/**
* @brief Select Names function
*
* Allows players to select their names and updates the game state and model accordingly.
*
* @param state Pointer to the game state
* @param model Pointer to the ArenaModel containing the game information
*
* @return The updated ArenaModel after the name selection
*/
struct ArenaModel (SelectNames)(enum GameState* state, struct ArenaModel* model);
#endif // SELECTNAMES_H
