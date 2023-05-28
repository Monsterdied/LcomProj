/**
 * @file
 * @brief Video Graphics functions
 *
 * This file contains functions related to video graphics.
 */

#pragma once
#include <machine/int86.h>
#include <stdint.h>
#include <lcom/lcf.h>

#define CHROMA_KEY_GREEN_888 0x00b140 /**< Chroma key green color in 888 format */

/**
 * @brief Map video RAM
 *
 * Maps the video RAM to the specified mode.
 *
 * @param mode The mode to set for the video RAM
 * @return Return 0 upon success, non-zero otherwise
 */
int map_vram(uint16_t mode);

/**
 * @brief Draw XPM image
 *
 * Draws an XPM image on the screen at the specified coordinates.
 *
 * @param xpm The XPM image to be drawn
 * @param x The x-coordinate of the image's top-left corner
 * @param y The y-coordinate of the image's top-left corner
 * @return Return 0 upon success, non-zero otherwise
 */
int drawXpm(xpm_map_t xpm, int x, int y);

/**
 * @brief Draw 8-bit 8-8-8 XPM image
 *
 * Draws an 8-bit 8-8-8 XPM image on the screen at the specified coordinates.
 *
 * @param img The XPM image to be drawn
 * @param x The x-coordinate of the image's top-left corner
 * @param y The y-coordinate of the image's top-left corner
 * @return Return 0 upon success, non-zero otherwise
 */
int drawXpm8_8_8(xpm_image_t img, int x, int y);

/**
 * @brief Initialize video graphics
 *
 * Initializes video graphics with the specified mode.
 *
 * @param mode The mode to set for video graphics
 * @return Return 0 upon success, non-zero otherwise
 */
int vg_init_new(uint16_t mode);

/**
 * @brief Get red component from color
 *
 * Retrieves the red component from the given color value.
 *
 * @param color The color value
 * @return The red component value
 */
int R(uint32_t color);

/**
 * @brief Get green component from color
 *
 * Retrieves the green component from the given color value.
 *
 * @param color The color value
 * @return The green component value
 */
int G(uint32_t color);

/**
 * @brief Get blue component from color
 *
 * Retrieves the blue component from the given color value.
 *
 * @param color The color value
 * @return The blue component value
 */
int B(uint32_t color);

/**
 * @brief Update video graphics
 *
 * Updates the video graphics buffer to display the changes made.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int vg_update();

/**
 * @brief Draw pixel
 *
 * Draws a pixel of the specified color at the given coordinates.
 *
 * @param x The x-coordinate of the pixel
 * @param y The y-coordinate of the pixel
 * @param color The color of the pixel
 * @return Return 0 upon success, non-zero otherwise
 */
int draw_pixel(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draw character using XPM image
 *
 * Draws a character using the specified XPM image at the given coordinates with the chosen color.
 *
 * @param c The character to be drawn
 * @param img The XPM image to be used for the character
 * @param x The x-coordinate of the character's top-left corner
 * @param y The y-coordinate of the character's top-left corner
 * @param colorChosen The color to be used for the character
 * @return Return 0 upon success, non-zero otherwise
 */
int vg_draw_Character(char c, xpm_image_t img, int x, int y, uint32_t colorChosen);
