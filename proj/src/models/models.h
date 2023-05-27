/**
 * @file models.h
 *
 * @brief Contains the data structures used in the Bomberman game.
 */

#ifndef BOMBERMAN_MODELS_H
#define BOMBERMAN_MODELS_H

#include "devices/video_gr.h"

/**
 * @brief Enumerates the possible game states.
 */
enum GameState{
    SELECTNAMES,    ///< State for selecting player names
    MENU,           ///< Main menu state
    GAME,           ///< Gameplay state
    GAMEOVER,       ///< Game over state
    EXIT,           ///< Exit state
    PLAYER1WON,     ///< State indicating player 1 has won
    PLAYER2WON      ///< State indicating player 2 has won
};

/**
 * @brief Enumerates the possible movement directions.
 */
enum Direction {
    UP,             ///< Up direction
    DOWN,           ///< Down direction
    LEFT,           ///< Left direction
    RIGHT,          ///< Right direction
    STAY            ///< No movement
};

/**
 * @brief Enumerates the possible flame directions for an explosion.
 */
enum FlameDirection{
    UPFLAME,        ///< Flame going up
    DOWNFLAME,      ///< Flame going down
    LEFTFLAME,      ///< Flame going left
    RIGHTFLAME,     ///< Flame going right
    CENTERFLAME     ///< Flame at the center
};

/**
 * @brief Enumerates the possible types of power-ups.
 */
enum PowerUpType {
    BOMB,           ///< Bomb power-up
    RANGE,          ///< Range power-up
    SPEED           ///< Speed power-up
};

/**
 * @brief Represents a position in the game arena.
 */
struct Position {
    int x;          ///< X-coordinate of the position
    int y;          ///< Y-coordinate of the position
};

/**
 * @brief Represents an explosion in the game.
 */
struct Explosion {
    struct Position position;       ///< Position of the explosion
    enum FlameDirection direction;  ///< Direction of the flame
    double timeUntilNextXpm;        ///< Time until the next explosion sprite
    double timeUntilFade;           ///< Time until the explosion fades
    int currentXpm;                 ///< Current explosion sprite index
};

/**
 * @brief Represents a bomb in the game.
 */
struct Bomb {
    struct Position position;       ///< Position of the bomb
    double timeUntilExplosion;      ///< Time until the bomb explodes
    double timeUntilNextXpm;        ///< Time until the next bomb sprite
    int currentXpm;                 ///< Current bomb sprite index
    int range;                      ///< Range of the bomb explosion
    int owner;                      ///< ID of the player who placed the bomb
};

/**
 * @brief Represents a button in the game's menu.
 */
struct Button{
    int x;                          ///< X-coordinate of the button
    int y;                          ///< Y-coordinate of the button
    int width;                      ///< Width of the button
    int height;                     ///< Height of the button
    bool selected;                  ///< Indicates if the button is selected
    xpm_image_t button_selected;    ///< Image for the selected button
    xpm_image_t button_unselected;  ///< Image for the unselected button
};

/**
 * @brief Represents a player in the game.
 */
struct Player {
    char name[10];                  ///< Player's name
    int nameSize;                   ///< Size of the player's name
    enum Direction direction;       ///< Current movement direction
    struct Position position;       ///< Current position
    xpm_image_t Left[3];            ///< Images for the left movement animation
    xpm_image_t Right[3];           ///< Images for the right movement animation
    xpm_image_t Up[3];              ///< Images for the up movement animation
    xpm_image_t Down[3];            ///< Images for the down movement animation
    int numberOfImages;             ///< Number of animation images
    int currentXpm;                 ///< Current animation image index
    double timeUntilNextXpm;        ///< Time until the next animation image
    double coldownBetweenXpms;      ///< Cooldown between animation images
    int lives;                      ///< Number of remaining lives
    int bombs;                      ///< Number of bombs the player has
    int bombcooldown;               ///< Cooldown between placing bombs
    int range;                      ///< Range of the player's bombs
    int speed;                      ///< Movement speed of the player
    double timeuntilnextmovement;   ///< Time until the next movement
    double movementcooldown;        ///< Cooldown between movements
    int score;                      ///< Player's score
    int id;                         ///< Player's ID
};

/**
 * @brief Represents a wall in the game arena.
 */
struct Wall {
    struct Position position;       ///< Position of the wall
};

/**
 * @brief Represents a brick in the game arena.
 */
struct Brick {
    struct Position position;       ///< Position of the brick
};

/**
 * @brief Represents a power-up in the game.
 */
struct PowerUp {
    struct Position position;       ///< Position of the power-up
    enum PowerUpType type;          ///< Type of the power-up
};

/**
 * @brief Represents the game arena model.
 */
struct ArenaModel {
    struct Player players[2];       ///< Array of players
    struct Bomb bombs[6];           ///< Array of bombs
    struct Wall walls[450];         ///< Array of walls
    struct Brick bricks[450];       ///< Array of bricks
    struct Explosion explosions[450];   ///< Array of explosions
    struct PowerUp powerUps[10];     ///< Array of power-ups
    struct Button returnButton;      ///< Return button in the game
    double elapsedTime;             ///< Elapsed time in the game
    int nWalls;                     ///< Number of walls in the arena
    int nBricks;                    ///< Number of bricks in the arena
    int nPowerUps;                  ///< Number of power-ups in the arena
    int nBombs;                     ///< Number of bombs in the arena
    int nExplosions;                ///< Number of explosions in the arena
};

/**
 * @brief Represents the menu model.
 */
struct MenuModel {
    int selectedOption;             ///< Index of the selected menu option
    int selectedLevel;              ///< Index of the selected game level
    int nlevels;                    ///< Number of available game levels
    int noptions;                   ///< Number of available menu options
};

#endif // BOMBERMAN_MODELS_H
