#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>
#define READ_FOUR_LSB 0x0F
int counter;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
uint8_t timer_config;  //para guardar a configuraçao do timer
  if (timer_get_conf(timer, &timer_config) != 0) {  //o if é para dar a mensagem de erro
    printf("timer_get_conf FAILED\n");
    return 1;
  }
  if (timer_display_conf(timer, timer_config, field) != 0) {  //mesmo que o if anterior
    printf("timer_display_conf FAILED\n");
    return 1;
  }
  return 0;

}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  if(freq<19) return 1;
  return timer_set_frequency(timer, freq);
}

int(timer_test_int)(uint8_t time) {
  uint8_t bit;
  timer_subscribe_int(&bit); //This function calls the timer_subscribe_int(&bit)

  uint32_t irq_set = BIT(bit); //This sets irq_set to a bit mask that represents the timer interrupt, using the bit position that was set in timer_subscribe

  int pic_status;
  message mensg;

  while( time ) { /* You may want to use a different condition */
     /* Get a request message. */
      int r;

      if ( (r = driver_receive(ANY, &mensg, &pic_status)) != 0 ) {  //to receive a message from any device driver
        
        //ANY (source):the function can receive a message from any driver (cuz ANY)
        //&mensg(message): pointer to a message struct, which is used to store the message that is received.
        //&pic_status(status):a pointer to an integer that is used to store the status of the message that is received.
        
        printf("driver_receive failed with: %d", r);
        continue;
      }

      if (is_ipc_notify(pic_status)) { /* received notification */
         switch (_ENDPOINT_P(mensg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (mensg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    timer_int_handler();

                    if (counter % 60 == 0) { //a cada 60 ciclos de relogio decrementar um
                        timer_print_elapsed_time();
                        time--;
                    } 
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */	
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  timer_unsubscribe_int();
  return 0;
}

