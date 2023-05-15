#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "videocard.h"
#include "keyboard.h"
#include "i8042.h"

///

// Any header files included below this line should have been created by you
extern vbe_mode_info_t info;
int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
    videographics_init(mode);

    sleep(delay);
    vg_exit();
  return 0;
}

extern int scan_code[2];
int i = 0;

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,uint16_t width, uint16_t height, uint32_t color) {
    if(mappVm(mode)){
    printf("mapping error\n");
    return 1;
  }
  videographics_init(mode);    
      

    
    

    vg_draw_rectangle(x,y,width,height,color);
    uint8_t bit_no;
  if(kbc_Subscribe(&bit_no)!= OK)
    return 1;

  uint32_t irq_set = BIT(bit_no);

  message msg;
  
  int ipc_status;
  int r;
  while( scan_code[0]!=0x81) { /* You may want to use a different condition */
    /* Get a request message. */
    
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != OK ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  kbc_ih();
                if(scan_code[i] == TWO_BYTES){
                  i++;
                  continue;
                }
                i=0;

                 }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
       /* no standard messages expected: do nothing */
    }

 }
  if(kbc_Unsubscribe() != 0)
    return 1;
    vg_exit();
  return 0;
}


int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  #define MACRO_DIRECT_COLOR_MODE 0x06
    if(mappVm(mode)){
      return 1;
    }
    videographics_init(mode);
    int divx = info.XResolution/no_rectangles;
    int divy = info.YResolution/no_rectangles;
      for(int row = 0 ; row<no_rectangles;row++){
      for(int col = 0 ; col <no_rectangles ; col++){
        if (info.MemoryModel != MACRO_DIRECT_COLOR_MODE) {
          //indexed
          uint32_t color = (first + (row * no_rectangles + col) * step) % (1 << info.BitsPerPixel) ;
          vg_draw_rectangle(col*divx,row*divy,divx,divy,color);
        }
        else{
          // direct
          uint32_t red = (R(first) + col * step) % (1 << info.RedMaskSize) ;
          uint32_t green = (G(first) + row * step) % (1 << info.GreenMaskSize) ;
          uint32_t blue = (B(first) + (col + row) * step) % (1 << info.BlueMaskSize) ;
          uint32_t color = (red <<info.RedFieldPosition)| (green << info.GreenFieldPosition)| (blue <<info.BlueFieldPosition);
          vg_draw_rectangle(col*divx,row*divy,divx,divy,color);
        }
      }
    }





  uint8_t bit_no;
  if(kbc_Subscribe(&bit_no)!= OK)
    return 1;

  uint32_t irq_set = BIT(bit_no);

  message msg;
  
  int ipc_status;
  int r;
  while( scan_code[0]!=0x81) { /* You may want to use a different condition */
    /* Get a request message. */
    
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != OK ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */				
                if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                  kbc_ih();
                if(scan_code[i] == TWO_BYTES){
                  i++;
                  continue;
                }
                i=0;

                 }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
       /* no standard messages expected: do nothing */
    }

 }
  if(kbc_Unsubscribe() != 0)
    return 1;
    vg_exit();
  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

