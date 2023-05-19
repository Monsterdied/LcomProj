//
// Created by diogo on 22/04/2023.
//
#include "draw.h"

xpm_image_t     bomberman_idle_down_white,bomberman_down_wallking_1_white ,bomberman_down_wallking_2_white,
                bomberman_idle_up_white,bomberman_up_wallking_1_white ,bomberman_up_wallking_2_white,
                bomberman_idle_right_white,bomberman_right_wallking_1_white,bomberman_right_wallking_2_white ,
                bomberman_idle_left_white,bomberman_left_wallking_1_white,bomberman_left_wallking_2_white ,


                bomberman_idle_down_black,bomberman_down_wallking_1_black ,bomberman_down_wallking_2_black,
                bomberman_idle_up_black,bomberman_up_wallking_1_black ,bomberman_up_wallking_2_black,
                bomberman_idle_right_black,bomberman_right_wallking_1_black,bomberman_right_wallking_2_black ,
                bomberman_idle_left_black,bomberman_left_wallking_1_black,bomberman_left_wallking_2_black ,

                explosion_center_1,explosion_top_1,explosion_left_1,explosion_right_1,
                explosion_center_2,explosion_top_2,explosion_left_2,explosion_right_2,

                bomb1,bomb2,bomb3,
                brick,
                wall,
                mouse_icon,
                menuIcon,
                menu_start_button_selected,
                menu_start_button_not_selected,
                menu_exit_button_selected,
                menu_exit_button_not_selected,
                menu_continue_button_selected,
                menu_continue_button_not_selected;

int (load_xpms)(struct ArenaModel* model){
    //white Bomberman
    xpm_load(downidlewhite_xpm, XPM_8_8_8, &bomberman_idle_down_white);
    xpm_load(downwalk1white_xpm, XPM_8_8_8, &bomberman_down_wallking_1_white);
    xpm_load(downwalk2white_xpm, XPM_8_8_8, &bomberman_down_wallking_2_white);

    xpm_load(upidlewhite_xpm, XPM_8_8_8, &bomberman_idle_up_white);
    xpm_load(upwalk1white_xpm, XPM_8_8_8, &bomberman_up_wallking_1_white);
    xpm_load(upwalk2white_xpm, XPM_8_8_8, &bomberman_up_wallking_2_white);

    xpm_load(leftidlewhite_xpm, XPM_8_8_8, &bomberman_idle_left_white);
    xpm_load(walkleft1white_xpm, XPM_8_8_8, &bomberman_left_wallking_1_white);
    xpm_load(walkleft2white_xpm, XPM_8_8_8, &bomberman_left_wallking_2_white);

    xpm_load(rightidlewhite_xpm, XPM_8_8_8, &bomberman_idle_right_white);
    xpm_load(walkright1white_xpm, XPM_8_8_8, &bomberman_right_wallking_1_white);
    xpm_load(walkright2white_xpm, XPM_8_8_8, &bomberman_right_wallking_2_white);

    xpm_load(downidleblack_xpm, XPM_8_8_8, &bomberman_idle_down_black);
    xpm_load(downwalk1black_xpm, XPM_8_8_8, &bomberman_down_wallking_1_black);
    xpm_load(downwalk2black_xpm, XPM_8_8_8, &bomberman_down_wallking_2_black);

    xpm_load(upidleblack_xpm, XPM_8_8_8, &bomberman_idle_up_black);
    xpm_load(upwalk1black_xpm, XPM_8_8_8, &bomberman_up_wallking_1_black);
    xpm_load(upwalk2black_xpm, XPM_8_8_8, &bomberman_up_wallking_2_black);

    xpm_load(leftidleblack_xpm, XPM_8_8_8, &bomberman_idle_left_black);
    xpm_load(walkleft1black_xpm, XPM_8_8_8, &bomberman_left_wallking_1_black);
    xpm_load(walkleft2black_xpm, XPM_8_8_8, &bomberman_left_wallking_2_black);

    xpm_load(rightidleblack_xpm, XPM_8_8_8, &bomberman_idle_right_black);
    xpm_load(walkright1black_xpm, XPM_8_8_8, &bomberman_right_wallking_1_black);
    xpm_load(walkright2black_xpm, XPM_8_8_8, &bomberman_right_wallking_2_black);

                //xpm
                model->players[0].Left[0] = bomberman_idle_left_white;
                model->players[0].Left[1] = bomberman_left_wallking_1_white;
                model->players[0].Left[2] = bomberman_left_wallking_2_white;

                model->players[0].Right[0] = bomberman_idle_right_white;
                model->players[0].Right[1] = bomberman_right_wallking_1_white;
                model->players[0].Right[2] = bomberman_right_wallking_2_white;

                model->players[0].Up[0] = bomberman_idle_up_white;
                model->players[0].Up[1] = bomberman_up_wallking_1_white;
                model->players[0].Up[2] = bomberman_up_wallking_2_white;

                model->players[0].Down[0] = bomberman_idle_down_white;
                model->players[0].Down[1] = bomberman_down_wallking_1_white;
                model->players[0].Down[2] = bomberman_down_wallking_2_white;
    xpm_load(menuIcon_xpm,XPM_8_8_8,&menuIcon);
    xpm_load(selected_continue_xpm,XPM_8_8_8,&menu_continue_button_selected);
    xpm_load(not_selected_continue_xpm,XPM_8_8_8,&menu_continue_button_not_selected);
    xpm_load(selected_exit_xpm,XPM_8_8_8,&menu_exit_button_selected);
    xpm_load(not_selected_exit_xpm,XPM_8_8_8,&menu_exit_button_not_selected);
    xpm_load(selected_start_xpm,XPM_8_8_8,&menu_start_button_selected);
    xpm_load(not_selected_start_xpm,XPM_8_8_8,&menu_start_button_not_selected);


    xpm_load(LOL_MOUSE_xpm,XPM_8_8_8,&mouse_icon);


    
    return 0;
}
                

void (drawWalls)(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nWalls;i++){
        printf("model x %d walls y%d \n",model.walls[i].position.x,model.walls[i].position.y );
        arena[model.walls[i].position.y][model.walls[i].position.x]=  'H';
    }
}
void drawBricks(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nBricks;i++){
        arena[model.bricks[i].position.y][model.bricks[i].position.x]=  'h';
    }
}
void drawPowerUps(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nPowerUps;i++){
        arena[model.powerUps[i].position.y][model.powerUps[i].position.x]=  'P';
    }
}
void drawBombs(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nBombs;i++){
        arena[ model.bombs[i].position.y][model.bombs[i].position.x]=  'B';
    }
}
void (drawPlayers)(struct ArenaModel model){
    int positionx =model.players[0].position.x * 20;
    int positiony =model.players[0].position.y*20;
    if(model.players[0].direction==UP){
        drawXpm8_8_8(model.players[0].Up[model.players[0].currentXpm],positionx,positiony);
    }else if(model.players[0].direction==LEFT){
        drawXpm8_8_8(model.players[0].Left[model.players[0].currentXpm],positionx,positiony);
    }else if(model.players[0].direction==RIGHT){
        drawXpm8_8_8(model.players[0].Right[model.players[0].currentXpm],positionx,positiony);
    }else{
        drawXpm8_8_8(model.players[0].Right[model.players[0].currentXpm],positionx,positiony);
    }
}
char (**getemptyArena()) {
    char** arena = (char**) malloc(15 * sizeof(char*));
    for (int i = 0; i < 15; i++) {
        arena[i] = (char*) malloc(30 * sizeof(char));
        for (int j = 0; j < 30; j++) {
            arena[i][j] = '_';
        }
    }
    return arena;
}


void (draw_menu)(struct MenuModel model,Mouse mouse){
    drawXpm8_8_8(menuIcon,150,50);
    
    if(model.selectedOption==0){
        drawXpm8_8_8(menu_start_button_selected,150,400);
        drawXpm8_8_8(menu_exit_button_not_selected,150,500);
    }else if(model.selectedOption==1){
        drawXpm8_8_8(menu_start_button_not_selected,150,400);
        drawXpm8_8_8(menu_exit_button_selected,150,500);

    }
    drawXpm8_8_8(mouse_icon,mouse.x,mouse.y);
}
void (draw_game)(struct ArenaModel model,Mouse mouse){

    /*drawWalls(arena, model);

    drawBricks(arena, model);
    drawPowerUps(arena, model);
    drawBombs(arena, model);*/
    drawPlayers(model);
}
