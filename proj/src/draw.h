//
// Created by diogo on 22/04/2023.
//
#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H

#include <stdio.h>
#include <malloc.h>
#include "models/models.h"

//bombs and bricks etc
/* to be added 
#include "models/bomb/bomb1.xpm"
#include "models/bomb/bomb2.xpm"
#include "models/bomb/bomb3.xpm"
*/
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
/* to be added
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
*/












void draw( struct ArenaModel model);
char (**getemptyArena());
void (drawPlayers)(char** arena, struct ArenaModel model);
void drawBombs(char** arena, struct ArenaModel model);
void drawPowerUps(char** arena, struct ArenaModel model);
void drawBricks(char** arena, struct ArenaModel model);
void (drawWalls)(char** arena, struct ArenaModel model);
#endif //UNTITLED10_DRAW_H
