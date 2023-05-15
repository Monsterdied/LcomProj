
#ifndef __MOUSE_H
#define __MOUSE_H
#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <stdint.h>

#include "i8042-mouse.h"

#define DELAY_US2 25000

extern struct packet data;
extern int mouse_i;
extern bool mouse_ready;

int (mouse_subscribe_int)(uint8_t* bit_no);
int (mouse_unsubscribe_int)();
int (mouse_disable_data_reporting)();
int (mouse_get_status)(uint8_t *st);
int (mouse_read_buffer) (uint8_t port, uint8_t* output);
int(mouse_write_cmd)(uint8_t cmdb);
void(mouse_ih)();

#endif
