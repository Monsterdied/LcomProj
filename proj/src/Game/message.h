#pragma once

#include <stdlib.h>
#include "models/models.h"
#include "draw/draw.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"

/**
 * @brief Display End Game
 *
 * Show the winner of the game
 *
 * @param state Pointer to the game state
 * @param model Pointer to the ArenaModel containing the game information
 *
 * @return The updated ArenaModel after the name selection
 */
void (Message)(enum GameState* state, struct ArenaModel model);
