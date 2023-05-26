//
// Created by diogo on 22/04/2023.
//
#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H
#include <stdio.h>
#include <malloc.h>
#include "models/models.h"
#include "devices/video_gr.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
//bombs and bricks etc
#include "models/bomb/bomb1.xpm"
#include "models/bomb/bomb2.xpm"
#include "models/bomb/bomb3.xpm"

#include "models/brick/brick.xpm"
#include "models/wall/wall.xpm"
#include "models/mouse/LOL_MOUSE.xpm"

//black Bomberman

#include "models/bomberman/downview/black/downidleblack.xpm"
#include "models/bomberman/downview/black/downwalk1black.xpm"
#include "models/bomberman/downview/black/downwalk2black.xpm"

#include "models/bomberman/upview/black/upidleblack.xpm"
#include "models/bomberman/upview/black/upwalk1black.xpm"
#include "models/bomberman/upview/black/upwalk2black.xpm"

#include "models/bomberman/leftview/black/leftidleblack.xpm"
#include "models/bomberman/leftview/black/walkleft1black.xpm"
#include "models/bomberman/leftview/black//walkleft2black.xpm"

#include "models/bomberman/rightview/black/rightidleblack.xpm"
#include "models/bomberman/rightview/black/walkright1black.xpm"
#include "models/bomberman/rightview/black/walkright2black.xpm"


//white Bomberman

#include "models/bomberman/downview/white/downidlewhite.xpm"
#include "models/bomberman/downview/white/downwalk1white.xpm"
#include "models/bomberman/downview/white/downwalk2white.xpm"

#include "models/bomberman/upview/white/upidlewhite.xpm"
#include "models/bomberman/upview/white/upwalk1white.xpm"
#include "models/bomberman/upview/white/upwalk2white.xpm"

#include "models/bomberman/leftview/white/leftidlewhite.xpm"
#include "models/bomberman/leftview/white/walkleft1white.xpm"
#include "models/bomberman/leftview/white//walkleft2white.xpm"

#include "models/bomberman/rightview/white/rightidlewhite.xpm"
#include "models/bomberman/rightview/white/walkright1white.xpm"
#include "models/bomberman/rightview/white/walkright2white.xpm"

//explosion
#include "models/explosions/explosion1.xpm"
#include "models/explosions/explosion2.xpm"

#include "models/explosions/explosion1bot.xpm"
#include "models/explosions/explosion2bot.xpm"

#include "models/explosions/explosion1left.xpm"
#include "models/explosions/explosion2left.xpm"

#include "models/explosions/explosion1right.xpm"
#include "models/explosions/explosion2right.xpm"

#include "models/explosions/explosion1top.xpm"
#include "models/explosions/explosion2top.xpm"
//menu
#include "models/menu/menuIcon.xpm"
#include "models/menu/not_selected_continue.xpm"
#include "models/menu/not_selected_exit.xpm"
#include "models/menu/not_selected_start.xpm"
#include "models/menu/selected_continue.xpm"
#include "models/menu/selected_exit.xpm"
#include "models/menu/selected_start.xpm"

//numbers
#include "models/numbers/0.xpm"
#include "models/numbers/1.xpm"
#include "models/numbers/2.xpm"
#include "models/numbers/3.xpm"
#include "models/numbers/4.xpm"
#include "models/numbers/5.xpm"
#include "models/numbers/6.xpm"
#include "models/numbers/7.xpm"
#include "models/numbers/8.xpm"
#include "models/numbers/9.xpm"
#include "models/numbers/double_points.xpm"

#include "models/font/font.xpm"















int (load_xpms)(struct ArenaModel* model);
void (draw_game)(struct ArenaModel model,Mouse mouse);
char** (getemptyArena());
void (drawPlayers)(struct ArenaModel model);
void (drawBombs)( struct ArenaModel model);
void (drawPowerUps)(char** arena, struct ArenaModel model);
void (drawBricks)(struct ArenaModel model);
void (drawWalls)(struct ArenaModel model);
void (draw_menu)(struct MenuModel model, Mouse mouse, time_display time_info);
void (draw_TimeNumbers)(time_display time_info);
void (draw_string)(char* text, int x, int y,int size,uint32_t color);
void (draw_select_names)(int player_number,struct ArenaModel model,Mouse mouse);
#endif //UNTITLED10_DRAW_H
