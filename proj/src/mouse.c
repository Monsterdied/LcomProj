#include "mouse.h"
#include "i8042.h"
#include <lcom/lcf.h>

int mouse_id = 3;
struct packet mouse_packet;
int mouse_byte_number = 0;
bool flag_mouse = true;
bool can_read_mouse = true;
int (mouse_Subscribe)(uint8_t *bit_no){
    *bit_no = mouse_id;
    return sys_irqsetpolicy(12,IRQ_REENABLE | IRQ_EXCLUSIVE ,&mouse_id);//12
}
int (mouse_Unsubscribe)(){
    return sys_irqrmpolicy(&mouse_id);
}

int (util_sys_inb_copy)(int port, uint8_t *value) {
  uint32_t tmp_value = 0x00;
  int ret = sys_inb(port , &tmp_value);
  *value = tmp_value;
  return ret;
}
void update_mouse(Mouse *mouse ,vbe_mode_info_t vmi){
  if(!mouse_packet.y_ov){
                        //printf("y:%d,",mouse_packet.delta_y);
    mouse->y = mouse->y - mouse_packet.delta_y;
    if(mouse->y + mouse->height >= vmi.YResolution){
      mouse->y = vmi.YResolution - mouse->height;
    }

    if(mouse->y < 0){
      mouse->y = 0;
    }
  }

  if(!mouse_packet.x_ov){
    //printf("x:%d\n",mouse_packet.delta_x);
    mouse->x = mouse->x + mouse_packet.delta_x;
    if(mouse->x + mouse->width >= vmi.XResolution){
      mouse->x = vmi.XResolution - mouse->width; 
    }
    if(mouse->x < 0){
      mouse->x = 0;
    }
  }
}

void (mouse_ih_new)( Mouse *mouse , const vbe_mode_info_t vmi) {
    uint8_t st;
    if(mouse_get_status(&st)!= OK){
        return;
    }
    if (!(st & FULL_OUT_BUFFER) || (st & (PARITY_ERROR | TIMEOUT_ERROR))) { 
      printf("not good interrupt");
        return ;
    }
    uint8_t output = 0;
    mouse_read_buffer(KBC_OUT_CMD,&output );
        mouse_packet.bytes[mouse_byte_number] = output;
        //printf("%d      %d         %d\n",mouse_byte_number,mouse_packet.bytes[mouse_byte_number] ,output);

    if (flag_mouse &&(output & FIRST_MOUSE_BIT)) {
        flag_mouse = false;
        mouse_packet.lb = output & LMOUSE_BUTTON;
        mouse_packet.rb = output & RMOUSE_BUTTON;
        mouse_packet.mb = output & MMOUSE_BUTTON;
        mouse_packet.x_ov = output & X_OVERFLOW;
        mouse_packet.y_ov = output & Y_OVERFLOW;
    }
    if(mouse_byte_number == 1){
        mouse_packet.delta_x = output;
        if (mouse_packet.bytes[0] & MOUSE_MSB_X){
          mouse_packet.delta_x |= 0xFF00;//to be negative
        } 
        
    }
    if(mouse_byte_number == 2){
        mouse_packet.delta_y = output;
        if (mouse_packet.bytes[0] & MOUSE_MSB_Y){
          mouse_packet.delta_y |= 0xFF00;
        }
        mouse_byte_number = -1;
        flag_mouse = true;
        update_mouse(mouse,vmi);
    }
    mouse_byte_number++;
}

int mouse_get_status(uint8_t *st){
    return util_sys_inb_copy(KBC_STATUS_REG,st);
}

int(mouse_read_buffer)(uint8_t port, uint8_t *output) {

  int out = 0;
  uint8_t status;

  while (out < 3) {

    mouse_get_status(&status);
  
    if (((status & FULL_OUT_BUFFER) && ( status & AUX  )) && !((status & (PARITY_ERROR | TIMEOUT_ERROR)))) {
      util_sys_inb_copy(port, output);
      return 0;
    }
    printf("ticking to check\n");
    tickdelay(micros_to_ticks(10000));
    out++;
  }

  return -1;
}


int(mouse_write_cmd)(uint8_t cmdb) {

  int out = 0;
  uint8_t status;

  while (out < 3) {

    if (mouse_get_status(&status) != 0) {
      printf("error geting status");
      return 1;
    }

    if (!(status & FULL_IN_BUFFER)) {
      sys_outb(MOUSE_CMD_REG, WRITE_BYTE_TO_MOUSE);
    }


    if (mouse_get_status(&status) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if (!(status & FULL_IN_BUFFER)) {
      sys_outb(MOUSE_ARGS, cmdb);
    }

    tickdelay(micros_to_ticks(25000));

    uint8_t ack_byte;
    util_sys_inb_copy(OUT_BUF, &ack_byte);

    if (ack_byte == MOUSE_OK){
      return 0;
    } 

    out++;
  }
  return -1;
}
int (mouse_disable_data_reporting)(){
    if(mouse_write_cmd(DISABLE_DATA_REPORTING_CMD)!= OK)
        return 1;
    return 0;

}




