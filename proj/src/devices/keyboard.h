
/**
 * @file
 * @brief Keyboard Controller (KBC) functions
 *
 * This file contains functions related to the Keyboard Controller (KBC).
 */

#include <lcom/lcf.h>
#include "i8042.h"

#define KBC_MAKE_CODE_A 0x1e
#define KBC_BREAK_CODE_A 0x9e
#define KBC_MAKE_CODE_S 0x1f
#define KBC_BREAK_CODE_S 0x9f
#define KBC_MAKE_CODE_W 0x11
#define KBC_BREAK_CODE_W 0x91
#define KBC_MAKE_CODE_D 0x20
#define KBC_BREAK_CODE_D 0xa0
#define KBC_MAKE_CODE_SPACE 0x39
#define KBC_BREAK_CODE_SPACE 0xb9
#define KBC_MAKE_CODE_ENTER 0x1c
#define KBC_BREAK_CODE_ENTER 0x9c
#define KBC_MAKE_CODE_ESC 0x01

/**
 * @brief Subscribe to KBC interrupts
 *
 * Subscribes to KBC interrupts using the specified bit number.
 *
 * @param bit_no Pointer to the memory location where the bit number will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (kbc_Subscribe)(uint8_t *bit_no);

/**
 * @brief Unsubscribe from KBC interrupts
 *
 * Unsubscribes from KBC interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int (kbc_Unsubscribe)();

/**
 * @brief Check for KBC errors
 *
 * Checks the status byte for errors occurred during communication with the KBC.
 *
 * @param status The status byte to be checked
 * @return Return 0 if no errors occurred, non-zero otherwise
 */
int (kbc_error_checking)(uint8_t status);

/**
 * @brief Write command to KBC
 *
 * Writes a command to the specified port of the KBC.
 *
 * @param port The port to write the command to
 * @param cmdb The command byte to be written
 * @return Return 0 upon success, non-zero otherwise
 */
int (writing_command_kbc)(int port, uint8_t cmdb);

/**
 * @brief Read data from KBC
 *
 * Reads data from the KBC's output buffer.
 *
 * @param data Pointer to the memory location where the read data will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (reading_from_kbc)(uint8_t *data);

/**
 * @brief Re-enable keyboard interrupts
 *
 * Re-enables the keyboard interrupts.
 *
 * @return Return 0 upon success, non-zero otherwise
 */
int (kbd_reenable_ints)();

/**
 * @brief Read from keyboard output buffer
 *
 * Reads the contents of the keyboard output buffer.
 *
 * @param output Pointer to the memory location where the read data will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (keyboard_read_out_buffer)(uint8_t *output);

/**
 * @brief Get keyboard status
 *
 * Reads the status byte from the keyboard controller.
 *
 * @param st Pointer to the memory location where the read status byte will be stored
 * @return Return 0 upon success, non-zero otherwise
 */
int (keyboard_get_status)(uint8_t *st);

/**
 * @brief Keyboard interrupt handler
 *
 * Interrupt handler for the keyboard interrupts.
 */
void (kbc_ih)();
