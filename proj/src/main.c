#include <stdio.h>
#include <unistd.h>
#include "load.h"
#include "draw.h"
#include "models/models.h"
#include "Game.h"
#include "Menu.h"

#include <lcom/lcf.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "load.h"
#include "draw.h"
#include "models/models.h"
#include "rtc.h"


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

int (proj_main_loop)() {
    // Initialize graphics mode (replace MODE_XXXX with the desired video mode)
    if (vg_init_new(0X14C) != 0) {
        printf("Failed to initialize graphics mode.\n");
        return 1;
    }

    // Map video RAM
    if (map_vram(0X14C) != 0) {
        printf("Failed to map video RAM.\n");
        return 1;
    }

    // Draw a rectangle
    uint16_t x = 0;     
    uint16_t y = 0;     
    uint16_t width = 1151; 
    uint16_t height = 863;
    uint32_t color = 0xFFFFFF; 

    if (vg_draw_rectangle(x, y, width, height, color) != 0) {
        printf("Failed to draw rectangle.\n");
        return 1;
    }

    // Update the screen to show the changes
    if (vg_update() != 0) {
        printf("Failed to update the screen.\n");
        return 1;
    }

    sleep(5);

    return 0;
}
