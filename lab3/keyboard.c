
#include "keyboard.h"
#include <lcom/lcf.h>
#include <stdint.h>
int static hook_id = 1;
int counter=0;
extern uint8_t data;

int(keyboard_get_status)(uint8_t *st){
    return util_sys_inb(KBC_STATUS_REG ,st);
}

int(keyboard_read_out_buffer)(uint8_t *output){
    return util_sys_inb(KBC_OUT_CMD,output);
}



int (read_keyboard_status)(uint8_t *st){
    return util_sys_inb(KBC_STATUS_REG,st);
}


int(check_status)(uint8_t st){
    if(st & PARITY_ERROR){
        return printf("Parity Error");
    }
    if(st & TIMEOUT_ERROR){
        return printf("Timeout Error");
    }
    if(st & FULL_OUT_BUFFER){
        return printf("Full out buffer");
    }
    if(st & FULL_IN_BUFFER){
        return printf("Full in buffer");
    }
    return 0;
}

int (keyboard_subscribe_interrupts)(uint8_t *bit_no){
    *bit_no=hook_id;
    return sys_irqsetpolicy(IRQ_KEYBOARD,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id);
}
int (keyboard_unsubscribe_interrupts)(){
    return sys_irqrmpolicy(&hook_id);
}

int (kbd_read_ret_cmdb)(uint8_t *data){

    int timeout=0;
    while(timeout<3){
        uint8_t st;
        if(keyboard_get_status(&st)){
            fprintf(stderr, "Error getting status when reading command byte return value!\n");
        return -1;

        }
        if (st & FULL_OUT_BUFFER && !(st & (PARITY_ERROR | TIMEOUT_ERROR | AUX))) {
            if(keyboard_read_out_buffer(data)!=0){
                fprintf(stderr, "Error reading KBC command byte return value from output buffer!\n");
                return -1;
            }
            return 0;

        }else return -1;

        tickdelay(micros_to_ticks(WAIT_KBC));
        timeout++;

    }
    return 0;

}

int(kbd_write_cmdb)(int port ,uint8_t cmdb) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 2) {  // used to retry writing a command byte to the keyboard controller if the input buffer is full.
                        /*When the input buffer is full, any further write attempts will be blocked until the buffer is emptied by reading the data byte. 
                        This can cause a delay in executing the desired operation and potentially lead to data loss if the command byte is not written properly.*/
    
    keyboard_get_status(&st); //guarda o status

    if((st & FULL_IN_BUFFER)==0){  //Check if the input buffer is empty by checking if the FULL_IN_BUFFER bit is not set in the st variable. If the input buffer is empty, continue to the next line.
        sys_outb(port,cmdb);        //escrever o cmdb no port
        return 0;
    }

    tickdelay(micros_to_ticks(10000)); //delays for 10000 ms
    timeout++;
  }

  return 1;
}

int(kbd_reenable_ints)() {

  uint8_t output;

  if (kbd_write_cmdb(KBC_CMD_REG,KBC_READ_CMD) != 0) {
    fprintf(stderr, "Error writing command byte while reenabling interrupts!\n");
    return -1;
  }

  if (kbd_read_ret_cmdb(&output) != 0) {
    fprintf(stderr, "Error reading return command byte!\n");
    return -1;
  }

  output |= KBC_INT;

  if (kbd_write_cmdb(KBC_CMD_REG,KBC_WRITE_CMD) != 0) {
    fprintf(stderr, "Error writing command byte while reenabling interrupts!\n");
    return -1;
  }

  if (kbd_write_cmdb(KBC_ARGS, output) != 0) {
    fprintf(stderr, "Error writing command byte arguments to input buffer!\n");
    return -1;
  }

  return 0;
}
