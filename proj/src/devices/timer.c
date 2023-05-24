#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
int time_global = 0;
int hook_id = 0 ;
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  // check if frequency is within spec
  if(freq >TIMER_FREQ || freq <=0){
    return 1;
  }
  uint32_t rb_comm = TIMER_RB_CMD | BIT(5) | BIT(timer + 1);
  sys_outb(TIMER_CTRL, rb_comm);
  uint8_t conf = 0;

  timer_get_conf(timer, &conf);
  conf  = conf & ( BIT(3) | BIT(2) | BIT(1) |BIT(0)); //select only the 4 bits  Mode (3) BCD/Binary counting
  conf  = conf | TIMER_LSB_MSB;
  switch (timer) {
    case 0: conf |= TIMER_SEL0; break;
    case 1: conf |= TIMER_SEL1; break;
    case 2: conf |= TIMER_SEL2; break;
    default: return 1;
  }// conf |= TIMER_SEL0  ===       conf = conf | TIMER_SEL0

  sys_outb(TIMER_CTRL , conf);
  // TIMER_FREQ = 1193182
  uint16_t new_clk = TIMER_FREQ/freq;
  uint8_t msb = 0,lsb = 0;
  util_get_MSB(new_clk, &msb);
  util_get_LSB(new_clk , &lsb );

  sys_outb(TIMER_0 +timer,lsb); sys_outb(TIMER_0 + timer,msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = 0;
  *bit_no = hook_id;

  bool tmp = sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id);
  return tmp;
}

int (timer_unsubscribe_int)() {
  bool tmp = sys_irqrmpolicy(&hook_id);
  return tmp ;
}

void (timer_int_handler)() {
  time_global++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  switch(timer) {

    case 0: return util_sys_inb(TIMER_0, st);

    case 1: return util_sys_inb(TIMER_1, st);

    case 2: return util_sys_inb(TIMER_2, st);
  };
  return 1;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  union timer_status_field_val result;
  switch (field) {
    case tsf_all:
      result.byte = st;
      break;
    case tsf_initial:
      if ( st & TIMER_LSB_MSB) result.in_mode = MSB_after_LSB;
      else if ( st & TIMER_LSB) result.in_mode = LSB_only;
      else if ( st & TIMER_MSB) result.in_mode = MSB_only;
      else result.in_mode = INVAL_val;
      break;
    case tsf_mode:
      result.count_mode = ((st & (BIT(1) | BIT(2) | BIT(3))) >> 1);
      break;
    case tsf_base:
      result.bcd = (st & BIT(0));
      break;
  }
  return timer_print_config(timer, field, result);
}
