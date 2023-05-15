// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/pp.h>

#include <stdint.h>

//----------------------------------------------------------------
#define Control_Reg 0x23;
#define Status_Reg 0x23;
#define IRQ 10;


#define Timer0_REG 0x20;
#define Timer1_REG 0x21;
#define Timer2_REG 0x22;

//controll word
#define Timer0 0x00;
#define Timer1 BIT(6);
#define Timer2 BIT(7);


#define alarm_mode BIT(4);
#define periodic_mode 0x00;



#define micro 0x00;
#define mili BIT(1);
#define second BIT(2);

#define ReadTimer0 BIT(0);
#define ReadTimer1 BIT(6);
#define ReadTimer2 BIT(7);



//----------------------------------------------------------------

static int __hook_id = 0;
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/pp/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/pp/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

intpp_test_alarm(int timer, int interval, enum l3223_time_units unit); {


  int ipc_status, r, irq_set = 0;
  message msg;

  bool done = false;
  uint8_t cmd =

  // XXX : you may need to add some code here

  // interrupt loop
  while (!done) {
    // Get a request message.
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { // received notification
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:                             // hardware interrupt notification
          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt
                                                   // handle interrupt
          }
          break;
        default:
          break;
      }
    }
  }

  return r;
}

int(pp_test_optimized)(uint32_t cnt) {
  /* To be completed */
  printf("%s(%u): under construction\n", __func__, cnt);

  return 1;
}