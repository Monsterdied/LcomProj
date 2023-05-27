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

                explosion_center_1,explosion_top_1,explosion_left_1,explosion_right_1,explosion1bot,
                explosion_center_2,explosion_top_2,explosion_left_2,explosion_right_2,explosion2bot,

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
                menu_continue_button_not_selected,
                number_0,number_1,number_2,number_3,number_4,number_5,number_6,number_7,number_8,number_9,double_point,
                font,
                coin1,coin2,coin3,coin4,coin5;
int multiplier = 22; 
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
    //player 2
    model->players[1].Left[0] = bomberman_idle_left_black;
    model->players[1].Left[1] = bomberman_left_wallking_1_black;
    model->players[1].Left[2] = bomberman_left_wallking_2_black;

    model->players[1].Right[0] = bomberman_idle_right_black;
    model->players[1].Right[1] = bomberman_right_wallking_1_black;
    model->players[1].Right[2] = bomberman_right_wallking_2_black;

    model->players[1].Up[0] = bomberman_idle_up_black;
    model->players[1].Up[1] = bomberman_up_wallking_1_black;
    model->players[1].Up[2] = bomberman_up_wallking_2_black;

    model->players[1].Down[0] = bomberman_idle_down_black;
    model->players[1].Down[1] = bomberman_down_wallking_1_black;
    model->players[1].Down[2] = bomberman_down_wallking_2_black;

    xpm_load(menuIcon_xpm,XPM_8_8_8,&menuIcon);
    xpm_load(selected_continue_xpm,XPM_8_8_8,&menu_continue_button_selected);
    xpm_load(not_selected_continue_xpm,XPM_8_8_8,&menu_continue_button_not_selected);
    xpm_load(selected_exit_xpm,XPM_8_8_8,&menu_exit_button_selected);
    xpm_load(not_selected_exit_xpm,XPM_8_8_8,&menu_exit_button_not_selected);
    xpm_load(selected_start_xpm,XPM_8_8_8,&menu_start_button_selected);
    xpm_load(not_selected_start_xpm,XPM_8_8_8,&menu_start_button_not_selected);

    //buttons
    model->returnButton.button_selected =menu_exit_button_selected;
    model->returnButton.button_unselected =menu_exit_button_not_selected;

    xpm_load(LOL_MOUSE_xpm,XPM_8_8_8,&mouse_icon);

    xpm_load(bomb1_xpm,XPM_8_8_8,&bomb1);
    xpm_load(bomb2_xpm,XPM_8_8_8,&bomb2);
    xpm_load(bomb3_xpm,XPM_8_8_8,&bomb3);

    xpm_load(brick_xpm,XPM_8_8_8,&brick);
    xpm_load(wall_xpm,XPM_8_8_8,&wall);
    
    xpm_load(explosion1_xpm,XPM_8_8_8,&explosion_center_1);
    xpm_load(explosion2_xpm,XPM_8_8_8,&explosion_center_2);

    xpm_load(explosion1top_xpm,XPM_8_8_8,&explosion_top_1);
    xpm_load(explosion2top_xpm,XPM_8_8_8,&explosion_top_2);

    xpm_load(explosion1left_xpm,XPM_8_8_8,&explosion_left_1);
    xpm_load(explosion2left_xpm,XPM_8_8_8,&explosion_left_2);

    xpm_load(explosion1right_xpm,XPM_8_8_8,&explosion_right_1);
    xpm_load(explosion2right_xpm,XPM_8_8_8,&explosion_right_2);

    xpm_load(explosion1bot_xpm,XPM_8_8_8,&explosion1bot);
    xpm_load(explosion2bot_xpm,XPM_8_8_8,&explosion2bot);

    xpm_load(number_0_xpm,XPM_8_8_8,&number_0);
    xpm_load(number_1_xpm,XPM_8_8_8,&number_1);
    xpm_load(number_2_xpm,XPM_8_8_8,&number_2);
    xpm_load(number_3_xpm,XPM_8_8_8,&number_3);
    xpm_load(number_4_xpm,XPM_8_8_8,&number_4);
    xpm_load(number_5_xpm,XPM_8_8_8,&number_5);
    xpm_load(number_6_xpm,XPM_8_8_8,&number_6);
    xpm_load(number_7_xpm,XPM_8_8_8,&number_7);
    xpm_load(number_8_xpm,XPM_8_8_8,&number_8);
    xpm_load(number_9_xpm,XPM_8_8_8,&number_9);
    xpm_load(double_points_xpm,XPM_8_8_8,&double_point);

    xpm_load(font_xmp,XPM_8_8_8,&font);


    xpm_load(coin1_xpm,XPM_8_8_8,&coin1);
    xpm_load(coin2_xpm,XPM_8_8_8,&coin2);
    xpm_load(coin3_xpm,XPM_8_8_8,&coin3);
    xpm_load(coin4_xpm,XPM_8_8_8,&coin4);
    xpm_load(coin5_xpm,XPM_8_8_8,&coin5);
    
    return 0;
}
                

void (drawWalls)(struct ArenaModel model){
    for(int i=0;i<model.nWalls;i++){

        drawXpm8_8_8(wall,model.walls[i].position.x * multiplier,model.walls[i].position.y*multiplier);
    }
}
void (drawBricks)(struct ArenaModel model){
    for(int i=0;i<model.nBricks;i++){

        drawXpm8_8_8(brick,model.bricks[i].position.x * multiplier,model.bricks[i].position.y*multiplier);
    }
}
void (drawPowerUps)(char** arena, struct ArenaModel model){
    for(int i=0;i<model.nPowerUps;i++){
        arena[model.powerUps[i].position.y][model.powerUps[i].position.x]=  'P';
    }
}
void (drawBombs)(struct ArenaModel model){
    for(int i=0;i<model.nBombs;i++){
        if(model.bombs[i].currentXpm==0)
            drawXpm8_8_8(bomb1,model.bombs[i].position.x * multiplier,model.bombs[i].position.y*multiplier);
        else if (model.bombs[i].currentXpm==1)
            drawXpm8_8_8(bomb2,model.bombs[i].position.x * multiplier,model.bombs[i].position.y*multiplier);
        else{
            drawXpm8_8_8(bomb3,model.bombs[i].position.x * multiplier,model.bombs[i].position.y*multiplier);
        }    
    }
}
void (drawFlames)(struct ArenaModel model){
    for(int i =0 ;i<model.nExplosions;i++){
        if(model.explosions[i].direction==CENTERFLAME){
            if(model.explosions[i].currentXpm==0){
                drawXpm8_8_8(explosion_center_1,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }else{
                drawXpm8_8_8(explosion_center_2,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }
        }else if(model.explosions[i].direction==UPFLAME){
            if(model.explosions[i].currentXpm==0){
                drawXpm8_8_8(explosion_top_1,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }else{
                drawXpm8_8_8(explosion_top_2,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }
        }else if(model.explosions[i].direction==DOWNFLAME){
            if(model.explosions[i].currentXpm==0){
                drawXpm8_8_8(explosion1bot,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }else{
                drawXpm8_8_8(explosion2bot,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }
        }else if(model.explosions[i].direction==LEFTFLAME){
            if(model.explosions[i].currentXpm==0){
                drawXpm8_8_8(explosion_left_1,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }else{
                drawXpm8_8_8(explosion_left_2,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }
        }else{
            if(model.explosions[i].currentXpm==0){
                drawXpm8_8_8(explosion_right_1,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }else{
                drawXpm8_8_8(explosion_right_2,model.explosions[i].position.x * multiplier,model.explosions[i].position.y*multiplier);
            }
        }
        
    }
}
void (draw_string)(char* text, int x, int y,int size,uint32_t color){
    for(int i = 0 ; i < size;i++){
        x+=15;
        vg_draw_Character(text[i],font,x,y,color);
    }
}


void (drawPlayers)(struct ArenaModel model){
    int positionx_white =model.players[0].position.x * multiplier;
    int positiony_white =model.players[0].position.y*multiplier;
    int positionx_black =model.players[1].position.x * multiplier;
    int positiony_black =model.players[1].position.y*multiplier;
    if(model.players[0].direction==UP){
        drawXpm8_8_8(model.players[0].Up[model.players[0].currentXpm],positionx_white,positiony_white);
    }else if(model.players[0].direction==LEFT){
        drawXpm8_8_8(model.players[0].Left[model.players[0].currentXpm],positionx_white,positiony_white);
    }else if(model.players[0].direction==RIGHT){
        drawXpm8_8_8(model.players[0].Right[model.players[0].currentXpm],positionx_white,positiony_white);
    }else{
        drawXpm8_8_8(model.players[0].Down[model.players[0].currentXpm],positionx_white,positiony_white);
    }
    if(model.players[1].direction==UP){
        drawXpm8_8_8(model.players[1].Up[model.players[1].currentXpm],positionx_black,positiony_black);
    }else if (model.players[1].direction==LEFT){
        drawXpm8_8_8(model.players[1].Left[model.players[1].currentXpm],positionx_black,positiony_black);
    }else if(model.players[1].direction==RIGHT){
        drawXpm8_8_8(model.players[1].Right[model.players[1].currentXpm],positionx_black,positiony_black);
    }else{
        drawXpm8_8_8(model.players[1].Down[model.players[1].currentXpm],positionx_black,positiony_black);
    }            
}

void (draw_coins)(struct ArenaModel model){
    for(int i=0;i<model.nCoins;i++){
        if(model.coins[i].currentXpm==0)
        drawXpm8_8_8(coin1,model.coins[i].position.x * multiplier,model.coins[i].position.y*multiplier);
        else if(model.coins[i].currentXpm==1)
        drawXpm8_8_8(coin2,model.coins[i].position.x * multiplier,model.coins[i].position.y*multiplier);
        else if(model.coins[i].currentXpm==2)
        drawXpm8_8_8(coin3,model.coins[i].position.x * multiplier,model.coins[i].position.y*multiplier);
        else if(model.coins[i].currentXpm==3)
        drawXpm8_8_8(coin4,model.coins[i].position.x * multiplier,model.coins[i].position.y*multiplier);
        else if(model.coins[i].currentXpm==4)
        drawXpm8_8_8(coin5,model.coins[i].position.x * multiplier,model.coins[i].position.y*multiplier);
    }
}
void (draw_background)(struct ArenaModel model){
    vg_draw_rectangle(0,0,30*multiplier,15*multiplier,0x7CFC00);
}

void (numbersDisplay)(int number, int x, int y ){
    if(number==0){
        drawXpm8_8_8(number_0,x,y);
    }
    if(number==1){
        drawXpm8_8_8(number_1,x,y);
    }
    if(number==2){
        drawXpm8_8_8(number_2,x,y);
    }
    if(number==3){
        drawXpm8_8_8(number_3,x,y);
    }
    if(number==4){
        drawXpm8_8_8(number_4,x,y);
    }
    if(number==5){
        drawXpm8_8_8(number_5,x,y);
    }
    if(number==6){
        drawXpm8_8_8(number_6,x,y);
    }
    if(number==7){
        drawXpm8_8_8(number_7,x,y);
    }
    if(number==8){
        drawXpm8_8_8(number_8,x,y);
    }
    if(number==9){
        drawXpm8_8_8(number_9,x,y);
    }
}
void (draw_TimeNumbers)(time_display time_info){
    uint8_t hours = getHours(time_info);
    uint8_t minutes = getMinutes(time_info);
    uint8_t seconds = getSeconds(time_info);
    numbersDisplay(hours/10,10,10);
    numbersDisplay(hours%10,30,10);
    drawXpm8_8_8(double_point,50,10);
    numbersDisplay(minutes/10,70,10);
    numbersDisplay(minutes%10,90,10);
    drawXpm8_8_8(double_point,110,10);
    numbersDisplay(seconds/10,130,10);
    numbersDisplay(seconds%10,150,10);
}
void draw_select_names(int player_number,struct ArenaModel model,Mouse mouse){
    char string[] = "PLAYER NUMBER 0";
    char string_num = player_number + '1';
    string[14] = string_num;

    draw_string(string,30,30,15,0xFF0F00);
    draw_string(model.players[player_number].name,200,300 ,model.players[player_number].nameSize,0XFF0000);
    drawXpm8_8_8(mouse_icon,mouse.x,mouse.y);
    
}
void (draw_menu)(struct MenuModel model,Mouse mouse,time_display time_info){
    drawXpm8_8_8(menuIcon,150,50);
    
    if(model.selectedOption==0){
        drawXpm8_8_8(menu_start_button_selected,150,400);
        drawXpm8_8_8(menu_exit_button_not_selected,150,500);
    }else if(model.selectedOption==1){
        drawXpm8_8_8(menu_start_button_not_selected,150,400);
        drawXpm8_8_8(menu_exit_button_selected,150,500);

    }
    draw_TimeNumbers(time_info);
    drawXpm8_8_8(mouse_icon,mouse.x,mouse.y);

    
}
void draw_Button(struct Button button){
    if(button.selected)
        drawXpm8_8_8(button.button_selected,button.x,button.y);
    else
        drawXpm8_8_8(button.button_unselected,button.x,button.y);
}
void (draw_game)(struct ArenaModel model,Mouse mouse){
    draw_coins(model);
    draw_Button(model.returnButton);
    //draw_background(model);
    drawWalls(model);

    drawBricks(model);
    drawBombs(model);
    drawFlames(model);
    /*
    drawPowerUps(arena, model);
    */
    drawPlayers(model);
    drawXpm8_8_8(mouse_icon,mouse.x,mouse.y);
}

void (draw_players_info)(struct ArenaModel model){
    char Coins_player1[3];
    char Coins_player2[3];
    char output_play1[11]= "COINS: ";
    char output_play2[11]= "COINS: ";
    sprintf(Coins_player1,"%d",model.players[0].score);
    sprintf(Coins_player2,"%d",model.players[1].score);
    strcat(output_play1,Coins_player1);
    strcat(output_play2,Coins_player2);
    printf(" ok %s\n",Coins_player1);
    printf(" ok %s\n",output_play1);
    printf(" ok %s\n",output_play2);
    draw_string("PLAYER1:", 50,450,8,0xFF00FF);
    draw_string(model.players[0].name, 50,500,model.players[0].nameSize,0xFF00FF);
    draw_string(output_play1, 50,550,8,0xFF00FF);
    draw_string("PLAYER2:", 250,450,8,0xFF00FF);
    draw_string(model.players[1].name, 250, 500,model.players[1].nameSize,0xFF00FF); 
    draw_string(output_play2, 250,550,8,0xFF00FF);
}
