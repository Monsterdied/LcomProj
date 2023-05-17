#include <lcom/lcf.h>

int (kbc_Subscribe)(uint8_t *bit_no);
int (kbc_Unsubscribe)();
int (kbc_error_checking)(uint8_t status);
int (writing_command_kbc)(int port ,uint8_t cmdb);
int (reading_from_kbc)(uint8_t *data);
int(kbd_reenable_ints)();
int(keyboard_read_out_buffer)(uint8_t *output);
int(keyboard_get_status)(uint8_t *st);
void (kbc_ih)();
