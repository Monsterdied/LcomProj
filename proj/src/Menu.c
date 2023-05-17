#include "Menu.h"
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
Mouse mouse;
struct MenuModel model;
message msg;
int ipc_status;
int r;
int timer_interrupts_per_frame;
int timer_interrupts_counter;
uint8_t irq_set_timer;
uint32_t irq_set_mouse;
uint32_t irq_set_kbc;
uint8_t bit_no_mouse;
uint8_t bit_no_kbc;
uint8_t bit_no_timer;
int fr_rate = 10;
extern int scan_code[2];
int i;
void (kbc_api_menu()){
    printf("api\n");
  if(scan_code[0] == KBC_MAKE_CODE_A){
    model.selectedOption --;
    if(model.selectedOption<0){
      model.selectedOption=model.noptions-1;

    }
    printf("A\n");
    printf(" sel %d\n",model.selectedOption);
  }else  if(scan_code[0] == KBC_MAKE_CODE_D){
    model.selectedOption ++;
    if(model.selectedOption>model.noptions-1){
      model.selectedOption=0;
    }
    printf("D\n");
    printf(" sel %d\n",model.selectedOption);
  }
}
struct MenuModel (get_default_Menu)(){
    printf("get default menu\n");
    model.selectedOption=0;
    model.nlevels=1;
    model.noptions=2;
    model.selectedLevel=0;
    return model;
}
int get_started_on_menu(){
    mouse.x = 600;
    mouse.y = 300;
    mouse.height = 44;
    mouse.width = 44;

    printf("get started\n");
    if(map_vram(0x14C)){
        return 1;
    }
    if(vg_init_new(0x14C)!=OK){
        return 1;
    }
    if(kbc_Subscribe(&bit_no_kbc) != OK)
        return 1;

    if(timer_subscribe_int(&bit_no_timer) != OK){
        return 1;
    }
    if(mouse_Subscribe(&bit_no_mouse) != OK){
        return 1;
    }
    i=0;
    irq_set_timer = BIT(bit_no_timer);
    irq_set_kbc = BIT(bit_no_kbc);
    irq_set_mouse = BIT(bit_no_mouse);
    timer_interrupts_per_frame = 60/fr_rate;
    timer_interrupts_counter = 0;
    return 0;
}


struct ArenaModel (Menu)(enum GameState* state){
    model=get_default_Menu();
    if(get_started_on_menu()){
        printf("error on menu\n");
        struct ArenaModel arenamodel=loadArena(arena);
        return arenamodel;
    }
    printf("started on menu\n");
    while(*state==MENU){
        if( timer_interrupts_counter % timer_interrupts_per_frame == 0 ){
            timer_interrupts_counter = 0;        
        draw_menu(model,mouse);
        if(vg_update()!= OK){
            printf("Screen dind't update");        
            }
        } 
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != OK ) {     
        printf("driver_receive failed with: %d", r);
        continue;
        }

        if (is_ipc_notify(ipc_status)) { /* received notification */
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: /* hardware interrupt notification */				
                    if (msg.m_notify.interrupts & irq_set_kbc) { /* subscribed interrupt */
                        kbc_ih(); //calls the kbc_ih() 
                        if(scan_code[i]==TWO_BYTES){   //se o scan code for de 2 bytes vai incrementar o i e fazer o continue para ler o proximo byte (o segundo neste caso)
                        i++; 
                        continue;
                        }//Prints the input scancode.
                        kbc_api_menu();
                        printf("real sel %d\n",model.selectedOption);
                        i=0;
                        if(scan_code[0]==BREAK_ESC || (model.selectedOption==1  && scan_code[0]==KBC_MAKE_CODE_ENTER)){
                            *state=EXIT;
                        }if((model.selectedOption==0  && scan_code[0]==KBC_MAKE_CODE_ENTER)){
                            *state=GAME;
                        }
                         //volta a ler o primeiro byte
                    }

                    if(msg.m_notify.interrupts & irq_set_timer){
                        timer_interrupts_counter++;

                    }

                    if (msg.m_notify.interrupts & irq_set_mouse) {
                    mouse_ih_new(&mouse);
                  }

                    break;
                default:
                    break; /* no other notifications expected: do nothing */	
            }
            
        } else { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }

        


    }  
    mouse_Unsubscribe();
    kbc_Unsubscribe();
    timer_unsubscribe_int();
    vg_exit();

    struct ArenaModel arenamodel=loadArena(arena);

    return arenamodel;
}
