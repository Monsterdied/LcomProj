/**
 * @file models.h
 *
 * @brief Contains the data structures used in the Bomberman game.
 */

#ifndef BOMBERMAN_MODELS_H
#define BOMBERMAN_MODELS_H

#include "devices/rtc.h"
#include "devices/video_gr.h"

/**
 * @brief Enumerates the possible game states.
 */
enum GameState {
    TIE,            ///< State indicating a tie
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
enum FlameDirection {
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
 * @brief Represents a coin in the game.
 */
struct Coin {
    struct Position position;       /**< The position of the coin. */
    int currentXpm;                 /**< The current value of the coin in points. */
    double timeUntilNextXpm;        /**< The time remaining until the coin's value increases. */
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
struct Button {
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
 * @brief Represents a score in the leaderboard.
 */
struct LeaderBoardScore {
    char name[10];                  /**< The name of the player */
    int score;                      /**< The score */
};

/**
 * @brief Represents the model of an arena in a game.
 */
struct ArenaModel {
    struct Coin coins[450];              /**< Array of coins in the arena. */
    struct Player players[2];            /**< Array of players in the arena. */
    struct Bomb bombs[6];                /**< Array of bombs in the arena. */
    struct Wall walls[450];              /**< Array of walls in the arena. */
    struct Brick bricks[450];            /**< Array of bricks in the arena. */
    struct Explosion explosions[450];    /**< Array of explosions in the arena. */
    struct PowerUp powerUps[10];         /**< Array of power-ups in the arena. */
    struct Button returnButton;          /**< Button used to return to the main menu. */
    struct LeaderBoardScore scores[3];    /**< Array of leaderboard scores. */
    double elapsedTime;                  /**< Elapsed time in the arena. */
    int nScores;                         /**< Number of leaderboard scores. */
    int nWalls;                          /**< Number of walls in the arena. */
    int nBricks;                         /**< Number of bricks in the arena. */
    int nPowerUps;                       /**< Number of power-ups in the arena. */
    int nBombs;                          /**< Number of bombs in the arena. */
    int nExplosions;                     /**< Number of explosions in the arena. */
    int nCoins;                          /**< Number of coins in the arena. */
};

/**
 * @brief Represents the menu model.
 */
struct MenuModel {
    int selectedOption;     ///< Index of the selected menu option
    int selectedLevel;      ///< Index of the selected game level
    int nlevels;            ///< Number of available game levels
    int noptions;           ///< Number of available menu options
};

#endif // BOMBERMAN_MODELS_H
