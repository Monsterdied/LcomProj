#ifndef _KBD_H_
#define _KBD_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <minix/sysutil.h>
#include "i8042.h"

int (keyboard_subscribe_interrupts)(uint8_t *bit_kbd);

int (keyboard_unsubscribe_interrupts)();

int (check_status)(uint8_t status);

int (keyboard_reenable_interrupts)();

void (kbc_ih)();

extern int hook_id_kbc;
extern uint8_t data[2];
extern int kbc_i;
extern bool flag;

#endif /*_KBD_H_*/
