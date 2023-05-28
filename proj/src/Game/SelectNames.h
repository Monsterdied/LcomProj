#ifndef SELECTNAMES_H
#define SELECTNAMES_H
#include <stdlib.h>
#include "models/models.h"
#include "draw/draw.h"
#include "load.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "gameControllers/kbc_controller.h"
struct ArenaModel (SelectNames)(enum GameState* state,struct ArenaModel* model);


#endif // !sELECTNAMES_H
