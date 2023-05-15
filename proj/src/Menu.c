#include "Menu.h"
#include "models/models.h"
#include "load.h"


struct ArenaModel Menu(enum GameState* state){
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
    *state=GAME;
    return model;
}
