#ifndef _LCOM_I8254_H_
#define _LCOM_I8254_H_

#define IRQ_MOUSE 12 //irq mouse



//---------------------
//Mouse-Related KBC Commands These commands are for the KBC and must be written to port 0x64
//Arguments and return values are passed via port 0x60
//---------------------
#define KBC_stat_reg 0x64
#define KBC_write_port 0x64
#define KBC_args 0x60
#define OUT_BUF 0x60
//---------------------
//Mouse-Related KBC Commands
//---------------------
#define READ_COMMAND_BYTE 0x20
#define WRITE_COMMAND_BYTE 0x60
#define DISABLE_MOUSE 0xA7 
#define ENABLE_MOUSE 0xA8
#define WRITE_BYTE_TO_MOUSE 0xD4
#define CHECK_MOUSE_INTERFACE 0xA9 
//---------------------
//status reg
//---------------------
#define STATUS_PARITY BIT(7)
#define STATUS_TIMEOUT BIT(6)
#define STATUS_AUX BIT(5)
#define IBF BIT(1)
#define OBF BIT(0)


//---------------------
#define FIRST_BYTE    BIT(3)        // bit mask to check if we are receiving a packet's first byte
//---------------------
//Command Byte
//---------------------
#define DISABLE__MOUSE BIT(5)
#define ENABLE_INTERUPT_MOUSE BIT(1)


//-------------------
//Commands passed as arguments of command 0xD4
//-------------------
#define RESET_ARG 0xFF 
#define RESEND_ARG 0xFE
#define SET_DEFAULT_ARG 0xF6 
#define DISABLE_DATA_REPORTING  0xF5          // disables mouse data reporting
#define ENABLE_DATA_REPORTING 0xF4 

#define SET_SAMPLE    0xF3          // set sample rate
#define SET_REMOTE    0xF0          // set mouse to remote mode
#define READ_DATA     0xEB          // request a packet from the mouse (remote mode only)
#define SET_STREAM    0xEA          // set mouse to stream mode
#define MOUSE_CONFIG   0xE9 
//-------------------
//acknowledgment byte
//-------------------
#define ACK   0xFA  //everything ok
#define NACK  0xFE  // not OK
#define ERROR 0xFC  // errorssss

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






#endif
