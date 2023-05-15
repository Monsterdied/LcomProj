#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include <stdint.h>

int (keyboard_subscribe_interrupts)(uint8_t *bit_no);

int (keyboard_unsubscribe_interrupts)();

int(check_status)(uint8_t st);

int(keyboard_get_status)(uint8_t *st);

int(keyboard_read_out_buffer)(uint8_t *output);

int(keyboard_renable_interrupts)();

int(keyboard_write_cmdb)(int port, uint8_t cmdb);

int(keyboard_read_ret_cmdb)(uint8_t *data);

#endif
