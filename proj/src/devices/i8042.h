/**
 * @file i8042.h
 *
 * @brief Constants and definitions for programming the i8042 keyboard controller and mouse.
 */

#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8254 Timer.
 */

#define IRQ_KEYBOARD    1        ///< Keyboard interrupt request line

#define BREAK_ESC       0x81     ///< Break code for the Esc key
#define MAKE_CODE       BIT(7)   ///< Make code flag
#define TWO_BYTES       0xE0     ///< Two-byte code prefix
#define ENABLE_INT      BIT(0)   ///< Enable interrupt flag
#define AUX             BIT(5)   ///< Auxiliary device flag

#define TIMEOUT_ERROR   BIT(6)   ///< Timeout error flag
#define PARITY_ERROR    BIT(7)   ///< Parity error flag
#define FULL_OUT_BUFFER BIT(0)   ///< Full output buffer flag
#define FULL_IN_BUFFER  BIT(1)   ///< Full input buffer flag

#define KBC_STATUS_REG  0x64     ///< Keyboard controller status register port
#define KBC_IN_CMD      0x64     ///< Keyboard controller input command port
#define KBC_OUT_CMD     0x60     ///< Keyboard controller output command port
#define KBC_OUT_BUFFER  0x60     ///< Keyboard controller output buffer port
#define KBC_READ_CMD    0x20     ///< Keyboard controller read command
#define KBC_WRITE_CMD   0x60     ///< Keyboard controller write command
#define KBC_INT         BIT(0)   ///< Keyboard controller interrupt enable flag

#define WAIT_KBC        20000    ///< Wait time for keyboard controller
#define MAX_ATTEMPS     10       ///< Maximum number of attempts for keyboard controller communication

// IO PORTS
#define OUT_BUF       0x60       ///< Output buffer port
#define STATUS_REG    0x64       ///< Status register port
#define MOUSE_ARGS    0x60       ///< Same as output buffer, but used for sending command arguments
#define MOUSE_CMD_REG 0x64       ///< Same as status register, but used for issuing commands

// MOUSE/KBC COMMANDS
#define KBC_READ_CMD 0x20        ///< Keyboard controller read command
#define KBC_WRITE_CMD 0x60       ///< Keyboard controller write command
#define WRITE_BYTE_TO_MOUSE 0xD4 ///< Command to write a byte to the mouse

// MOUSE COMMANDS
#define DISABLE_DATA_REPORTING_CMD 0xF5 ///< Command to disable data reporting from the mouse

// MOUSE COMMUNICATION BYTES
#define MOUSE_OK 0xFA                ///< Everything is OK
#define MOUSE_NOCK 0xFE              ///< Communication error
#define MOUSE_COMMUNICATION_ERR 0xFE ///< Second consecutive communication error

// MOUSE STUFF
#define FIRST_MOUSE_BIT BIT(3) ///< First bit of the mouse packet

// MOUSE ERROR CHECKING
#define X_OVERFLOW      BIT(6) ///< X coordinate overflow flag
#define Y_OVERFLOW      BIT(7) ///< Y coordinate overflow flag

// MOUSE BUTTONS
#define RMOUSE_BUTTON   BIT(1) ///< Right mouse button flag
#define LMOUSE_BUTTON   BIT(0) ///< Left mouse button flag
#define MMOUSE_BUTTON   BIT(2) ///< Middle mouse button flag

// MSB DELTAS (negative or not)
#define MOUSE_MSB_X BIT(4) ///< MSB bit of the X delta (indicates if the delta is negative or not)
#define MOUSE_MSB_Y BIT(5) ///< MSB bit of the Y delta (indicates if the delta is negative or not)

// DELTAS POSITIVE OR NEGATIVE
#define X_SIGNAL_OF_DELTA_MOUSE BIT(4) ///< Signal bit of the X delta (indicates if the delta is positive or negative)
#define Y_SIGNAL_OF_DELTA_MOUSE BIT(5) ///< Signal bit of the Y delta (indicates if the delta is positive or negative)

#endif /* _LCOM_I8042_H_ */
