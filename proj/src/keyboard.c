#include "keyboard.h"
#include <lcom/lcf.h>
#include <stdint.h>

int hook_id_kbc = 1;
uint8_t data[2];
int kbc_i=0;
bool flag = false;


int(keyboard_subscribe_interrupts)(uint8_t *bit_kbd){
    *bit_kbd = hook_id_kbc;
    return sys_irqsetpolicy(1,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id_kbc);
}

int(keyboard_unsubscribe_interrupts)(){
    return sys_irqrmpolicy(&hook_id_kbc);
}

int(check_status)(uint8_t status){
    if(status & PARITY_ERROR) return printf("PARITY ERROR");
    if(status & TIMEOUT_ERROR) return printf("TIMEOUT ERROR");
    if(status & OUTPUT_BUFFER_FULL) return printf("OUT_BUFFER FULL ERROR");
    if(status & INPUT_BUFFER_FULL) return printf("IN_BUFFER FULL ERROR");
    return 0;
}

int(keyboard_reenable_interrupts)(){
    uint8_t output;
    sys_outb(KBC_IN_CMD,READ_KBC_CMD);
    util_sys_inb(KBC_OUT_CMD,&output);
    output|=1;
    sys_outb(KBC_IN_CMD,WRITE_KBC_CMD);
    sys_outb(KBC_OUT_CMD,(uint32_t)output);
    return 0;
}


void (kbc_ih)(){
    uint8_t output;
    util_sys_inb(KBC_OUT_CMD,&output);

    uint8_t st;

    util_sys_inb(KBC_STATUS_REG,&st);
    if(check_status(st)==0){
        
      data[kbc_i]=output;

      if(output!=TWO_BYTES){
        if(output & MAKE_CODE){
          flag=false;
        }
        else{
          flag=true;
        }
      }  
    }
}
