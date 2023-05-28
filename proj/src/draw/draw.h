/**
 * @file
 * @brief Drawing functions
 *
 * This file contains functions related to drawing various elements on the screen.
 */
#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H
#include <stdio.h>
#include <malloc.h>
#include "models/models.h"
#include "devices/video_gr.h"
#include "devices/mouse.h"
#include "devices/rtc.h"

//Bombs Bricks Walls MouseCursor Xpms
#include "models/bomb/bomb1.xpm"
#include "models/bomb/bomb2.xpm"
#include "models/bomb/bomb3.xpm"

#include "models/brick/brick.xpm"
#include "models/wall/wall.xpm"
#include "models/mouse/LOL_MOUSE.xpm"

//Black Bomberman xpm (with actions)

#include "models/bomberman/downview/black/downidleblack.xpm"
#include "models/bomberman/downview/black/downwalk1black.xpm"
#include "models/bomberman/downview/black/downwalk2black.xpm"

#include "models/bomberman/upview/black/upidleblack.xpm"
#include "models/bomberman/upview/black/upwalk1black.xpm"
#include "models/bomberman/upview/black/upwalk2black.xpm"

#include "models/bomberman/leftview/black/leftidleblack.xpm"
#include "models/bomberman/leftview/black/walkleft1black.xpm"
#include "models/bomberman/leftview/black//walkleft2black.xpm"

#include "models/bomberman/rightview/black/rightidleblack.xpm"
#include "models/bomberman/rightview/black/walkright1black.xpm"
#include "models/bomberman/rightview/black/walkright2black.xpm"


//White Bomberman xpm (with actions)

#include "models/bomberman/downview/white/downidlewhite.xpm"
#include "models/bomberman/downview/white/downwalk1white.xpm"
#include "models/bomberman/downview/white/downwalk2white.xpm"

#include "models/bomberman/upview/white/upidlewhite.xpm"
#include "models/bomberman/upview/white/upwalk1white.xpm"
#include "models/bomberman/upview/white/upwalk2white.xpm"

#include "models/bomberman/leftview/white/leftidlewhite.xpm"
#include "models/bomberman/leftview/white/walkleft1white.xpm"
#include "models/bomberman/leftview/white//walkleft2white.xpm"

#include "models/bomberman/rightview/white/rightidlewhite.xpm"
#include "models/bomberman/rightview/white/walkright1white.xpm"
#include "models/bomberman/rightview/white/walkright2white.xpm"

//Explosions xpm 
#include "models/explosions/explosion1.xpm"
#include "models/explosions/explosion2.xpm"

#include "models/explosions/explosion1bot.xpm"
#include "models/explosions/explosion2bot.xpm"

#include "models/explosions/explosion1left.xpm"
#include "models/explosions/explosion2left.xpm"

#include "models/explosions/explosion1right.xpm"
#include "models/explosions/explosion2right.xpm"

#include "models/explosions/explosion1top.xpm"
#include "models/explosions/explosion2top.xpm"

//Menu xpm
#include "models/menu/menuIcon.xpm"
#include "models/menu/not_selected_continue.xpm"
#include "models/menu/not_selected_exit.xpm"
#include "models/menu/not_selected_start.xpm"
#include "models/menu/selected_continue.xpm"
#include "models/menu/selected_exit.xpm"
#include "models/menu/selected_start.xpm"

//Numbers xpm
#include "models/numbers/0.xpm"
#include "models/numbers/1.xpm"
#include "models/numbers/2.xpm"
#include "models/numbers/3.xpm"
#include "models/numbers/4.xpm"
#include "models/numbers/5.xpm"
#include "models/numbers/6.xpm"
#include "models/numbers/7.xpm"
#include "models/numbers/8.xpm"
#include "models/numbers/9.xpm"
#include "models/numbers/double_points.xpm"

#include "models/font/font.xpm"

//coinss

#include "models/coin/coin1.xpm"
#include "models/coin/coin2.xpm"
#include "models/coin/coin3.xpm"
#include "models/coin/coin4.xpm"
#include "models/coin/coin5.xpm"
#include "models/weather/sun.xpm"
#include "models/weather/moon.xpm"

//background

#include "models/background/grass.xpm"
#include "models/background/grassnight.xpm"
#include "models/background/message_background.xpm"












/**
 * @brief Load XPM images
 *
 * Loads the XPM images required for the game from the specified model.
 *
 * @param model The ArenaModel containing the XPM images
 * @return Return 0 upon success, non-zero otherwise
 */
int (load_xpms)(struct ArenaModel* model);

/**
 * @brief Draw the game
 *
 * Draws the game elements on the screen based on the provided ArenaModel and mouse information.
 *
 * @param model The ArenaModel containing the game information
 * @param mouse The Mouse information
 * @param time_info The Time Information
 */
void (draw_game)(struct ArenaModel model,Mouse mouse,time_display time_info);

/**
 * @brief Get an empty arena
 *
 * Creates and returns an empty arena as a 2D character array.
 *
 * @return The empty arena as a 2D character array
 */
char** (getemptyArena)();

/**
 * @brief Draw the players on the screen
 *
 * Draws the player characters on the screen based on the provided ArenaModel.
 *
 * @param model The ArenaModel containing the player information
 */
void (drawPlayers)(struct ArenaModel model);

/**
 * @brief Draw the bombs on the screen
 *
 * Draws the bombs on the screen based on the provided ArenaModel.
 *
 * @param model The ArenaModel containing the bomb information
 */
void (drawBombs)(struct ArenaModel model);

/**
 * @brief Draw the bricks on the screen
 *
 * Draws the bricks on the screen based on the provided ArenaModel.
 *
 * @param model The ArenaModel containing the brick information
 */
void (drawBricks)(struct ArenaModel model);

/**
 * @brief Draw the walls on the screen
 *
 * Draws the walls on the screen based on the provided ArenaModel.
 *
 * @param model The ArenaModel containing the wall information
 */
void (drawWalls)(struct ArenaModel model);

/**
 * @brief Draw the menu
 *
 * Draws the menu elements on the screen based on the provided MenuModel, mouse information, and time display.
 *
 * @param model The MenuModel containing the menu information
 * @param mouse The Mouse information
 * @param time_info The time display information
 */
void (draw_menu)(struct MenuModel model, Mouse mouse, time_display time_info);

/**
 * @brief Draw the time numbers
 *
 * Draws the time numbers on the screen based on the provided time display information.
 *
 * @param time_info The time display information
 */
void (draw_TimeNumbers)(time_display time_info);
/**
 * @brief Draws the players' information on the screen.
 *
 * This function is responsible for drawing the players' information in the game, like coins and name.
 *
 * @param model The arena model containing the information about the players.
 */
void (draw_players_info)(struct ArenaModel model);
/**
 * @brief Draws the game over report on the screen.
 *
 * This function is responsible for drawing the game over report based on the winner and loser.
 *
 * @param model The arena model containing the game information.
 * @param state The current game state.
 */
void (draw_Game_over_report)(struct ArenaModel model, enum GameState state);
/**
 * @brief Draws the game over display.
 *
 * This function is responsible for drawing the game over display on the screen based based on the winner and loser.
 *
 * @param model The arena model containing the game information.
 * @param state The current game state.
 * @param mouse The mouse object containing the mouse information.
 * @param is_selected Indicates whether the message is selected or not.
 */
void (draw_message)(struct ArenaModel model, enum GameState state,Mouse mouse,bool is_selected);



/**
 * @brief Draw a string
 *
 * Draws a string on the screen at the specified coordinates with the specified size and color.
 *
 * @param text The string to be drawn
 * @param x The x-coordinate of the string's top-left corner
 * @param y The y-coordinate of the string's top-left corner
 * @param size The size of the string
 * @param color The color of the string
 */
void (draw_string)(char* text, int x, int y, int size, uint32_t color);

/**
 * @brief Draw the select names
 *
 * Draws the select names on the screen based on the player number, ArenaModel, and mouse information.
 *
 * @param player_number The player number
 * @param model The ArenaModel containing the select names information
 * @param mouse The Mouse information
 */
void (draw_select_names)(int player_number, struct ArenaModel model, Mouse mouse);

#endif //UNTITLED10_DRAW_H
