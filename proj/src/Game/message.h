#pragma once
#include <stdlib.h>
#include "models/models.h"
#include "draw/draw.h"
#include "devices/keyboard.h"
#include "devices/mouse.h"

void (Message)(enum GameState* state,struct ArenaModel model);
