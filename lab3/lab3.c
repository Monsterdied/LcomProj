#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "keyboard.h"
#include <stdbool.h>
#include <stdint.h>
extern uint32_t counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

uint8_t data[2]; //para guardar os os 2 bytes de scan code

int i =0;  //selecionar o byte a ler

bool flag =false; //indica se é make or break code (pressed or release event)


void (kbc_ih)(){
  uint8_t st;
  keyboard_get_status(&st);
  uint8_t ouput;
  util_sys_inb(KBC_OUT_BUF,&ouput);
  data[i]=ouput;
  if(check_status(st)==0){
    if(ouput!=TWO_BYTES){
      
      if(ouput & MAKE_CODE){
        flag=false;
      }else{
        flag=true;
      }
    }

  }

}


int(kbd_test_scan)() {

  uint8_t bit;
 
  keyboard_subscribe_interrupts(&bit);

  uint32_t irq_set = BIT(bit);

  int pic_status;
  
  message msg;

  while(data[i]!=BREAK_ESC){  //sai do ciclo qnd carregar na tecla ESC
    int r;
    if ( (r = driver_receive(ANY, &msg, &pic_status)) != OK ) {  //to receive a message from any device driver
        
    //ANY (source):the function can receive a message from any driver (cuz ANY)
    //&mensg(message): pointer to a message struct, which is used to store the message that is received.
    //&pic_status(status):a pointer to an integer that is used to store the status of the message that is received.
        
      printf("driver_receive failed with: %d", r);
      continue;
    }

      if (is_ipc_notify(pic_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                    kbc_ih(); //calls the kbc_ih() 
                    if(data[i]==TWO_BYTES){   //se o scan code for de 2 bytes vai incrementar o i e fazer o continue para ler o proximo byte (o segundo neste caso)
                      i++; 
                      continue;
                    }
                    kbd_print_scancode(flag,i+1,data); //Prints the input scancode.
                    i=0; //volta a ler o primeiro byte
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */	
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
     counter++;
  }

  keyboard_unsubscribe_interrupts();
  kbd_print_no_sysinb(counter);  //contar o nº de sysinb calls

  return 0;



}

int(kbd_test_poll)() {
  

  while(data[i]!=BREAK_ESC){
    uint8_t st;
    keyboard_get_status(&st);
    if(st & FULL_OUT_BUFFER && !(st & (PARITY_ERROR | TIMEOUT_ERROR | AUX))){
      uint8_t ouput;
      if(keyboard_read_out_buffer(&ouput)){
        fprintf(stderr, "Error reading KBC ouput buffer!\n");
      return -1;
      }
      data[i]=ouput;
      if(ouput==TWO_BYTES){
        i++;
        continue;
      }
      if(ouput & MAKE_CODE){
        flag=false;
      }else{
        flag=true;
      }
      kbd_print_scancode(flag,i+1,data);
      i=0;
      counter++;
    }
  }
   kbd_reenable_ints();
  kbd_print_no_sysinb(counter);
  return 0;


  
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
