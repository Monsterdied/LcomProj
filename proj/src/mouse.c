#include "mouse.h"

int hook_id_mouse=12;

struct packet data;  
int mouse_i;
int mouse_flag = false;
int(mouse_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id_mouse;
  return sys_irqsetpolicy(12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}
int(mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id_mouse);
}
int(mouse_disable_data_reporting)() {
  return mouse_write_cmd(DIS_DATA_REP);
}
int(mouse_get_status)(uint8_t *st){
  return util_sys_inb(STATUS_REG, st);
}
int(mouse_read_buffer)(uint8_t port, uint8_t *output) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    mouse_get_status(&st);

    if ((st & (OBF | AUX)) && !((st & (PARITY | TIME_OUT)))) {
      util_sys_inb(port, output);
      return 0;
    }
    else return -1;

    tickdelay(micros_to_ticks(DELAY_US2));
    timeout++;
  }

  return -1;
}
int(mouse_write_cmd)(uint8_t cmdb) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    if (mouse_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if (!(st & IBF)) {
      sys_outb(MOUSE_CMD_REG, WRITE_AUX);
    }


    if (mouse_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if (!(st & IBF)) {
      sys_outb(MOUSE_ARGS, cmdb);
    }

    tickdelay(micros_to_ticks(DELAY_US2));

    uint8_t ack_byte;
    util_sys_inb(OUT_BUF, &ack_byte);

    if (ack_byte == MOUSE_OK) return 0;

    timeout++;
  }

  return -1;
}
void(mouse_ih)() {

  uint8_t output, st;
  mouse_get_status(&st);

  if (st & OBF && !(st & (PARITY | TIME_OUT))) {

    if (mouse_read_buffer(OUT_BUF, &output) != 0) {
      fprintf(stderr, "Error reading from buffer in mouse!\n");
      return;
    }

    data.bytes[mouse_i] = output;
    
    if (mouse_i == 0 && !(output & FIRST_BYTE)) {
      while (mouse_read_buffer(OUT_BUF, &output) == 0) {
        continue;
      }
      return;
    }

    switch (mouse_i) {
      case 0:
        data.lb = output & BIT(0);
        data.rb = output & BIT(1);
        data.mb = output & BIT(2);

        data.x_ov = output & BIT(6);
        data.y_ov = output & BIT(7);
        break;

      case 1:
        data.delta_x = output;
        if (data.bytes[0] & BIT(4)) data.delta_x |= 0xFF00;
        break;
        
      case 2:
        data.delta_y = output;
        if (data.bytes[0] & BIT(5)) data.delta_y |= 0xFF00;
        break;
    }

    mouse_i++;

    if (mouse_i == 3) {
      mouse_flag = true;
      mouse_i = 0;
    }

  }
}
