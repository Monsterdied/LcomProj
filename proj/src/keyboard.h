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
int (kbc_Subscribe)(uint8_t *bit_no);
int (kbc_Unsubscribe)();
int (kbc_error_checking)(uint8_t status);
int (writing_command_kbc)(int port ,uint8_t cmdb);
int (reading_from_kbc)(uint8_t *data);
int(kbd_reenable_ints)();
int(keyboard_read_out_buffer)(uint8_t *output);
int(keyboard_get_status)(uint8_t *st);
void (kbc_ih)();
