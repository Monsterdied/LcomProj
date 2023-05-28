/**
 * @file
 * @brief Mouse functions
 *
 * This file contains functions related to the mouse.
 */

#include <lcom/lcf.h>
#pragma once
 
/**
 * @brief Mouse structure
 *
 * Structure that represents the mouse.
 */
typedef struct {
  bool left_click;
  int x,y;             /**< current sprite position */
  int width, height;   /**< sprite dimensions */
  int xspeed, yspeed;  /**< current speeds in the x and y direction */      
} Mouse;

/**
 * @brief Subscribe to mouse interrupts
 *
 * Subscribes to mouse interrupts using the specified bit number.
 *
 * @param bit_no Pointer to the memory location where the bit number will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (mouse_Subscribe)(uint8_t *bit_no);

/**
 * @brief Unsubscribe from mouse interrupts
 *
 * Unsubscribes from mouse interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int (mouse_Unsubscribe)();

/**
 * @brief Check for mouse errors
 *
 * Checks the status byte for errors occurred during communication with the mouse.
 *
 * @param status_mouse The status byte to be checked
 * @return Return 0 if no errors occurred, non-zero otherwise
 */
int (error_checking_mouse)(uint8_t status_mouse);

/**
 * @brief Mouse interrupt handler
 *
 * Interrupt handler for the mouse interrupts.
 */
void (mouse_ih)();

/**
 * @brief Disable mouse data reporting
 *
 * Disables the mouse data reporting.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int (mouse_disable_data_reporting)();

/**
 * @brief Get mouse status
 *
 * Reads the status byte from the mouse controller.
 *
 * @param st Pointer to the memory location where the read status byte will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (mouse_get_status)(uint8_t *st);

/**
 * @brief Read data from mouse buffer
 *
 * Reads data from the mouse's buffer using the specified port.
 *
 * @param port The port to read the data from
 * @param output Pointer to the memory location where the read data will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (mouse_read_buffer)(uint8_t port, uint8_t *output);

/**
 * @brief New mouse interrupt handler
 *
 * New interrupt handler for the mouse interrupts that updates the mouse structure.
 *
 * @param mouse Pointer to the mouse structure to be updated
 */
void (mouse_ih_new)(Mouse *mouse);
