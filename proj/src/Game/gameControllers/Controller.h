/**
 * @file
 * @brief Controller functions
 *
 * This file contains functions related to controlling player actions and game elements.
 */

#ifndef UNTITLED10_CONTROLLER_H
#define UNTITLED10_CONTROLLER_H

#pragma once

#include "devices/keyboard.h"


/**
 * @brief Player controller
 *
 * Controls the actions of the player with the specified player number in the ArenaModel.
 *
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 */
void (PlayerController)(int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Check if player can walk to a position
 *
 * Checks if the player with the specified player number can walk to the given position in the ArenaModel.
 *
 * @param position The position to check
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 * @return True if the player can walk to the position, false otherwise
 */
bool (PlayerCanWalkTo)(struct Position position, int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Check if player can walk left
 *
 * Checks if the player with the specified player number can walk to the left in the ArenaModel.
 *
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 * @return True if the player can walk left, false otherwise
 */
bool (PlayerCanWalkLeft)(int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Check if player can walk right
 *
 * Checks if the player with the specified player number can walk to the right in the ArenaModel.
 *
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 * @return True if the player can walk right, false otherwise
 */
bool (PlayerCanWalkRight)(int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Check if player can walk to the top
 *
 * Checks if the player with the specified player number can walk to the top in the ArenaModel.
 *
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 * @return True if the player can walk to the top, false otherwise
 */
bool (PlayerCanWalkTop)(int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Check if player can walk down
 *
 * Checks if the player with the specified player number can walk down in the ArenaModel.
 *
 * @param PlayerNumber The player number
 * @param ArenaModel The ArenaModel containing the game information
 * @return True if the player can walk down, false otherwise
 */
bool (PlayerCanWalkDown)(int PlayerNumber, struct ArenaModel* ArenaModel);

/**
 * @brief Player controllers
 *
 * Controls the actions of all players in the ArenaModel.
 *
 * @param ArenaModel The ArenaModel containing the game information
 */
void (PlayerControllers)(struct ArenaModel* ArenaModel);

/**
 * @brief Players sprite controllers
 *
 * Controls the actions of the players' sprites in the ArenaModel.
 *
 * @param model The ArenaModel containing the game information
 */
void (PlayersSpriteControllers)(struct ArenaModel* model);

/**
 * @brief Bombs sprite controllers
 *
 * Controls the actions of the bombs' sprites in the ArenaModel.
 *
 * @param ArenaModel The ArenaModel containing the game information
 */
void (BombsSpriteControllers)(struct ArenaModel* ArenaModel);

/**
 * @brief Explosions controller
 *
 * Controls the actions of the explosions in the ArenaModel.
 *
 * @param arenaModel The ArenaModel containing the game information
 */
void (ExplosionsController)(struct ArenaModel* arenaModel);

/**
 * @brief Check if players are alive
 *
 * Checks if any players are alive in the ArenaModel and updates the game state accordingly.
 *
 * @param arenaModel The ArenaModel containing the game information
 * @param state Pointer to the game state
 * @return The number of players alive
 */
int (PlayersAreAlive)(struct ArenaModel* arenaModel, enum GameState* state);

#endif //UNTITLED10_CONTROLLER_H
