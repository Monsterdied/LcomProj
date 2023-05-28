#include <stdio.h>
#include <unistd.h>
#include "Game/load.h"

#include "models/models.h"
#include "Game/Game.h"
#include "Game/Menu.h"
#include "Game/message.h"
#include "Game/SelectNames.h"
#include "devices/rtc.h"

#include <lcom/lcf.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "models/models.h"

extern time_display time_info; 

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
extern time_display time_info;

int (proj_main_loop)(){



    update_time_display(&time_info);  
    enum GameState state=MENU;

    // first argument is y and secon is x 
    char arena[15][30]={
                     "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
                     "H______h_hhhhhh____B_________H",
                     "H_____________h______________H",
                     "H_____________h______________H",
                     "H___HHHH______h______h_______H",
                     "H______h______h______________H",
                     "H____________________________H",
                     "H_____h_______HHHHH______h___H",
                     "H______________h_____________H",
                     "H______C________h____________H",
                     "H______O_________h___________H",
                     "H___HHHH__________h_b________H",
                     "H__________________h_________H",
                     "H___________________h________H",
                     "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
    };
    
    struct ArenaModel model=loadArena(arena);

    load_xpms(&model);
    state=MENU;

    while(state!=EXIT){
        switch (state){
            case MENU:       
                model=Menu(&state,model);
                break;
            case SELECTNAMES:
                printf("game\n");
                SelectNames(&state,&model);
                break;
            case GAME:

                time_info = Game( &model,&state);
                break;
            case GAMEOVER:
                state=EXIT;
                //state=gameOver(state);
                break;    
            case EXIT:
                break;
            case PLAYER1WON:
                addPlayerToLeaderbord(model.players[0],&model,time_info);
                Message(&state,model);
                state=MENU;
                break;
            case PLAYER2WON:
                addPlayerToLeaderbord(model.players[1],&model,time_info);
                Message(&state,model);
                state=MENU;
                break;
            case TIE:
                state=EXIT;
                break;
        }
    }
    



    return 0;
}
