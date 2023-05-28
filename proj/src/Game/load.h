/**
 * @file
 * @brief Load functions
 *
 * This file contains functions related to loading game data.
 */

#ifndef UNTITLED10_LOAD_H
#define UNTITLED10_LOAD_H

/**
 * @brief Load ArenaModel
 *
 * Loads the game arena model based on the provided string array.
 *
 * @param pString The string array representing the game arena
 * @return The loaded ArenaModel
 */
struct ArenaModel (loadArena)(char pString[15][30]);

#endif // UNTITLED10_LOAD_H
