#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define IRQ_KEYBOARD    1

#define BREAK_ESC       0x81
#define MAKE_CODE       BIT(7)
#define TWO_BYTES       0xE0
#define ENABLE_INT      BIT(0)
#define AUX             BIT(5)

#define TIMEOUT_ERROR   BIT(6)
#define PARITY_ERROR    BIT(7)
#define FULL_OUT_BUFFER BIT(0)
#define FULL_IN_BUFFER  BIT(1)

#define KBC_STATUS_REG  0x64
#define KBC_IN_CMD      0x64
#define KBC_OUT_CMD     0x60
#define KBC_OUT_BUFFER  0x60
#define KBC_READ_CMD    0x20
#define KBC_WRITE_CMD   0x60
#define KBC_INT         BIT(0)

#define WAIT_KBC        20000
#define MAX_ATTEMPS     10

//IO PORTS
#define OUT_BUF       0x60          // output buffer port
#define STATUS_REG    0x64          // status register port
#define MOUSE_ARGS    0x60          // same as output buffer, but used for sending command arguments
#define MOUSE_CMD_REG 0x64          // same as status register, but used for issuing commands
//mouse /kbc commands
#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60
#define WRITE_BYTE_TO_MOUSE 0xD4
//MOUSE COMANDS
#define DISABLE_DATA_REPORTING_CMD 0XF5
//MOUSE COMUNICATION BYTES
#define MOUSE_OK 0XFA //EVERYTHING IS OK !!
#define MOUSE_NOCK 0XFE //COMUNICATION ERROR OR SOMETHING !!!
#define MOUSE_COMUNICATION_ERR 0XFE //SECONDE CONCECUTIVE ERR COMUNICATION ERROR OR SOMETHING !!!
//MOUSE STUFF
#define FIRST_MOUSE_BIT BIT(3)
//mouse error checking
#define X_OVERFLOW      BIT(6)
#define Y_OVERFLOW      BIT(7)
//MOUSE BUTTONS
#define RMOUSE_BUTTON   BIT(1)
#define LMOUSE_BUTTON   BIT(0)
#define MMOUSE_BUTTON   BIT(2)
//msb deltas negativos ou não
#define MOUSE_MSB_X BIT(4)
#define MOUSE_MSB_Y BIT(5)
//DELTAS POSITIVOS OU N
#define X_SIGNAL_OF_DELTA_MOUSE BIT(4) //SE ESTA BIT FOR 1 O DELTA É NEGATIVO OU AO CONTRARIO
#define Y_SIGNAL_OF_DELTA_MOUSE BIT(5)
#endif /* _LCOM_I8042_H_ */ 
