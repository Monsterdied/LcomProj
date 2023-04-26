#include <stdio.h>
#include <unistd.h>
#include "load.h"
#include "draw.h"
#include "models/models.h"


int main() {
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

    struct Model model=loadArena(arena);
    int timteout=5;
    while(timteout>0){
        draw( model);
        timteout--;
        sleep(1);
    }


    return 0;
}







