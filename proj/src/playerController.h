#ifndef UNTITLED10_DRAW_H
#define UNTITLED10_DRAW_H

void (PlayerController)(int PlayerNumber,struct ArenaModel* ArenaModel);
bool (PlayerCanWalkTo)(struct Position position,int PlayerNumber, struct ArenaModel* ArenaModel);
bool (PlayerCanWalkLeft)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkRight)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkTop)(int PlayerNumber , struct ArenaModel* ArenaModel);
bool (PlayerCanWalkDown)(int PlayerNumber , struct ArenaModel* ArenaModel); 
#endif //UNTITLED10_DRAW_H
