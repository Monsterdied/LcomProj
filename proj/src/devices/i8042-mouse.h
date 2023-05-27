#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042mouse i8042mouse
 * @{
 *
 * Constants for programming the i8042 mouse.
 */

/* I/O Ports */
#define OUT_BUF       0x60     ///< Output buffer port
#define STATUS_REG    0x64     ///< Status register port
#define MOUSE_ARGS    0x60     ///< Same as output buffer, but used for sending command arguments
#define MOUSE_CMD_REG 0x64     ///< Same as status register, but used for issuing commands

/* Bit masks */
#define PARITY        BIT(7)   ///< Bit mask to check for parity error
#define TIME_OUT      BIT(6)   ///< Bit mask to check for timeout error
#define AUX           BIT(5)   ///< Bit mask, 1 if mouse data, 0 if keyboard data
#define IBF           BIT(1)   ///< Bit mask to check if input buffer is full
#define OBF           BIT(0)   ///< Bit mask to check if output buffer is full

#define DIS2          BIT(5)   ///< Bit set to 1 for disabling mouse in command byte
#define DIS1          BIT(4)   ///< Bit set to 1 for disabling keyboard in command byte
#define INT2          BIT(1)   ///< Bit set to 1 to enable OBF interrupts from mouse
#define INT1          BIT(0)   ///< Bit set to 1 to enable OBF interrupts from keyboard

#define FIRST_BYTE    BIT(3)   ///< Bit mask to check if receiving a packet's first byte

/* Constants */
#define MOUSE_OK      0xFA     ///< Signal that a mouse command had no issues
#define MOUSE_NACK    0xFE     ///< Signal an invalid byte
#define MOUSE_ERR     0xFC     ///< Signal a second consecutive invalid byte

/* KBC Commands */
#define READ_CMDB     0x20     ///< Read command byte
#define WRITE_CMDB    0x60     ///< Write command byte
#define MOUSE_DIS     0xA7     ///< Disable mouse
#define MOUSE_ENBL    0xA8     ///< Enable mouse
#define CHK_MOUSE     0xA9     ///< Check mouse interface
#define WRITE_AUX     0xD4     ///< Write byte to mouse

/* Mouse Commands */
#define MOUSE_RESET   0xFF     ///< Reset the mouse
#define MOUSE_RESEND  0xFE     ///< Resend byte (used for communication errors)
#define MOUSE_DEFAULT 0xF6     ///< Set default mouse settings
#define DIS_DATA_REP  0xF5     ///< Disable mouse data reporting
#define ENBL_DATA_REP 0xF4     ///< Enable mouse data reporting
#define SET_SAMPLE    0xF3     ///< Set sample rate
#define SET_REMOTE    0xF0     ///< Set mouse to remote mode
#define READ_DATA     0xEB     ///< Request a packet from the mouse (remote mode only)
#define SET_STREAM    0xEA     ///< Set mouse to stream mode
#define MOUSE_CFG     0xE9     ///< Get mouse configuration

#endif /* _LCOM_I8042_H_ */
