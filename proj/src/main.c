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
extern int scan_code[2];
int i = 0;


int (proj_main_loop)() {
    enum GameState state=MENU;

    // first argument is y and secon is x 
    char arena[15][30]={
                     "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
                     "H__________________B_________H",
                     "H____________________________H",
                     "H____________________________H",
                     "H___HHHH_____________________H",
                     "H____________________________H",
                     "H____________________________H",
                     "H_____________HHHHH__________H",
                     "H____________________________H",
                     "H____________________________H",
                     "H____________________________H",
                     "H___HHHH____________b________H",
                     "H____________________________H",
                     "H____________________________H",
                     "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
    };
    struct ArenaModel model=loadArena(arena);




    while(state!=EXIT){
        switch (state){
            case MENU:
                    printf("menu\n");
                model=Menu(&state);
                break;
            case GAME:
                                printf("game\n");
                Game(model,&state);
                break;
         case GAMEOVER:
                state=EXIT;
                //state=gameOver(state);
                break;    
            case EXIT:
                break;
        }
    }



    return 0;
}
