// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


  extern bool flag;
  extern struct packet mouse_packet;
int (mouse_test_packet)(uint32_t cnt) {
  uint8_t mouse_hook =0;

  mouse_enable_data_reporting(); 
  if(mouse_subscribe(&mouse_hook)!=0){
    printf("error subscribing");
    return 1;
  }
  uint32_t irq_set = BIT(mouse_hook);
  message msg;
  int pic_status;
 while (cnt != 0) {
        int r;
        
        if ((r = driver_receive(ANY, &msg, &pic_status)) != 0) {
        printf("driver_receive failed with: %d", r);
        }
        if (is_ipc_notify(pic_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {

            case HARDWARE: {

            if (msg.m_notify.interrupts & irq_set) {
                mouse_ih();
                if (flag) {
                  mouse_print_packet(&mouse_packet);
                  cnt--;
                }
                
            }

            break;
            }

            default: break;
        }
        }



  }
  mouse_unsubscribe();
  mouse_disable_data_reporting();


  return 0;
}
extern int timer_counter;
int (mouse_test_async)(uint8_t idle_time) {
    uint8_t bit_mouse=1;
  uint8_t bit_timer=2;


  mouse_enable_data_reporting(); 
  timer_subscribe_int(&bit_timer);
  if(mouse_subscribe(&bit_mouse)!=0){
    printf("error subscribing");
    return 1;
  }
  uint32_t irq_set_mouse = BIT(bit_mouse);
  uint32_t irq_set_timer = BIT(bit_timer);
  message msg;
  int pic_status;
 while (timer_counter <= idle_time*60) {
        int r;
        
        if ((r = driver_receive(ANY, &msg, &pic_status)) != 0) {
        printf("driver_receive failed with: %d", r);
        }
        if (is_ipc_notify(pic_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {

            case HARDWARE: {

            if (msg.m_notify.interrupts & irq_set_mouse) {
                mouse_ih();
                if (flag) {
                  mouse_print_packet(&mouse_packet);
                  
                }
                timer_counter=0;
                
              }
              if(msg.m_notify.interrupts & irq_set_timer){

                timer_int_handler();
          
              }

            break;
            }

            default: break;
        }
        }



  }
  mouse_unsubscribe();
  mouse_disable_data_reporting();
  return 0;





}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
