#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"
#define READ_FOUR_LSB 0x0F
static int hook_id = 0;SPEAKER_CTR;
int counter = 0;


int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint32_t rb_comm = TIMER_RB_CMD | BIT(5) | BIT(timer + 1);
  sys_outb(TIMER_CTRL, rb_comm);

  uint8_t conf = 0;
  timer_get_conf(timer, &conf);
  conf &= READ_FOUR_LSB;
  conf |= TIMER_LSB_MSB;

  switch (timer) {
    case 0: conf |= TIMER_SEL0; break;
    case 1: conf |= TIMER_SEL1; break;
    case 2: conf |= TIMER_SEL2; break;
    default: return 1;
  }

  sys_outb(TIMER_CTRL, conf);

  uint16_t new_clk = TIMER_FREQ/freq;

  uint8_t lsb = 0, msb = 0;

  util_get_LSB(new_clk, &lsb);
  util_get_MSB(new_clk, &msb);

  sys_outb(TIMER_0 + timer, lsb); //LSB
  sys_outb(TIMER_0 + timer, msb); //MSB


  return 0;
}






int (timer_subscribe_int)(uint8_t *bit_no) {
  *bit_no = hook_id; //valor do bit_no passa a ser o valor do hook_id (default value for an interrupt request identifier) que é zero e o valor do hook passa a estar na memoria apontada pelo bit_no.
  return sys_irqsetpolicy(TIMER0_IRQ,IRQ_REENABLE,&hook_id); //function takes three arguments: the interrupt request number (TIMER0_IRQ), the interrupt policy (IRQ_REENABLE), and a pointer to the interrupt request identifier (&hook_id).
  //IRQ_REENABLE policy indicates that the interrupt should be automatically re-enabled after it has been handled.
  //TIMER0_IRQ é a linha que representa número de pedido de interrupção para o TIMER 0.
}


int (timer_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_id); //sys_irqrmpolicy() function is called to remove the interrupt policy that was previously set using sys_irqsetpolicy()
  /*&hook_id pointer is used to provide the identifier of the interrupt request that needs to be removed. 
  The sys_irqrmpolicy() function searches for the interrupt request that matches the provided identifier and 
  removes the corresponding interrupt policy.*/
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t Read_back_Command=TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if(sys_outb(TIMER_CTRL,Read_back_Command)!=OK){                       //sys_outb(...) serve para escrever o rb command no TIMER_CTRL
    printf("timer_get_conf FAILED TO WRITE READ BACK COMMAND");
    return 1;
  }
  if(util_sys_inb(TIMER_0+timer,st)!=0){                       //calls the util_sys_inb() para ler a configuração atual do timer e escrever no st
    return 1;
  } 
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  union timer_status_field_val result;
  switch (field) {
    case tsf_all:
      result.byte = st;
      break;
    case tsf_initial:
      result.in_mode = ((st & (BIT(5) | BIT(6))) >> 4);
      return timer_print_config(timer, field, result);
    case tsf_mode:
      result.count_mode = ((st & (BIT(1) | BIT(2) | BIT(3))) >> 1);
      break;
    case tsf_base:
      result.bcd = (st & BIT(0));
      break;
  }
  return timer_print_config(timer, field, result);
}


