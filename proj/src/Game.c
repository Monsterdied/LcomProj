#include "Game.h"
#include "draw.h"

void Game(struct ArenaModel model, enum GameState* state){

    int timeteout=50;
    while(timeteout>0){
        draw( model);
        timeteout--;
    }
    *state=EXIT;

}
