#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>
#include "i8254.h"
#define READ_FOUR_LSB 0x0F
int hook_id = 0;
int counter = 0;

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t rbcommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL,rbcommand);
  util_sys_inb(TIMER_0+timer,st);
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field){
    union timer_status_field_val val;
    switch(field){
        case tsf_all: 
            val.byte = st; break;
        case tsf_initial : 
            if(st & TIMER_LSB && st & TIMER_MSB) val.in_mode=MSB_after_LSB;
            else if(st & TIMER_LSB) val.in_mode = LSB_only;
            else if(st & TIMER_MSB) val.in_mode = MSB_only;
            else val.in_mode= INVAL_val;
            break;
        case tsf_mode : 
            val.count_mode = ((st & (BIT(1)|BIT(2)|BIT(3)))>>1);
            if(val.count_mode==7)val.count_mode=3;
            if(val.count_mode==6)val.count_mode=2;
            break;
        case tsf_base:
            val.bcd=(st & BIT(0));
            break;
    }    
    return timer_print_config(timer,field,val);
}

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint32_t rbcommand = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(TIMER_CTRL,rbcommand);

  uint8_t config;
  timer_get_conf(timer,&config);
  config = config & READ_FOUR_LSB;
  config = config | TIMER_LSB_MSB;

  switch (timer){
    case 0: config |= TIMER_SEL0; break;
    case 1: config|= TIMER_SEL1; break;
    case 2: config |= TIMER_SEL2; break;
    default: return 1;
  }

  sys_outb(TIMER_CTRL,config);

  uint16_t FREQ = TIMER_FREQ / freq;
  uint8_t lsb =0, msb =0;

  util_get_LSB(FREQ,&lsb);
  util_get_MSB(FREQ,&msb);


  sys_outb(TIMER_0+timer,lsb); 
  sys_outb(TIMER_0+timer, msb); 

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id;
  return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id); 
}

int (timer_unsubscribe_int)(){
    return sys_irqrmpolicy(&hook_id);
}

void (timer_int_handler)() {  
  counter++;
}
