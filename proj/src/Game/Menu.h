/**

@file
@brief Menu functions
This file contains functions related to the game menu.
*/
#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include "models/models.h"
#include "draw/draw.h"
#include "load.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "devices/rtc.h"

/**
* @brief Menu function
*
* Displays the game menu and handles user input to update the game state.
*
* @param state Pointer to the game state
* @return The updated ArenaModel after the menu selection
*/
struct ArenaModel (Menu)(enum GameState* state);
#endif // MENU_H
