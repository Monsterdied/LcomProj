#include <lcom/lcf.h>

int (mouse_subscribe)(uint8_t *bit_no);
int (mouse_unsubscribe)();
int (error_checking_mouse)(uint8_t status_mouse);
void (mouse_ih)();
int (mouse_disable_data_reporting)();
int (get_stat_mouse)(uint8_t  *st);
int(mouse_read_buffer)(uint8_t port, uint8_t *output);
