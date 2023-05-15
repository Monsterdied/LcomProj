#include <lcom/lcf.h>

#define IRQ_KEYBOARD 1  /*interrupt line*/


//Status Register
#define OUTPUT_BUFFER_FULL BIT(0)   
#define INPUT_BUFFER_FULL BIT(1)
#define FLAG BIT(2)
#define COMMAND_DATA BIT(3)
#define INB_SWITCH BIT(4)
#define AUX BIT(5)
#define TIMEOUT_ERROR BIT(6)
#define PARITY_ERROR BIT(7)

//PORTS
#define READ_KBC_CMD 0x20
#define WRITE_KBC_CMD 0x60
#define KBC_STATUS_REG 0x64
#define KBC_IN_CMD 0x64
#define KBC_OUT_CMD 0x60

//OTHER STUFF
#define BREAK_ESC       0x81
#define MAKE_CODE       BIT(7)
#define TWO_BYTES       0xE0
#define ENABLE_INT      BIT(0)
