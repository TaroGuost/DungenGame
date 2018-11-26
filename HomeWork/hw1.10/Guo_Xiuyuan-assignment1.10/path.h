#ifndef PATH_H
#define PATH_H

#include "map.h"
#include "pQueue.h"
#include "monster.h"
#include "move.h"

void printPath(int dis[1680] , Node **head , point *source);
int calculateindex(int x , int y);
int getlength(int p);
void FindShortestPath(point base[21][80] , point *source , int dis[1680]);
void printWallPath(int dis[1680],point *source);
void FindShortestPathWithWall(point base[21][80] , point *source , int dis[1680]);
void spellList(WINDOW **game , Monster *Ori , point base[21][80] , Player *p , bool fog , int mc);
void activeSpell(WINDOW **game , Monster *Ori , point base[21][80] , bool fog , Player *p , Spell spell , int mc);
void PrintMonster(WINDOW **game , Monster *ms , int mc , point base[21][80] , int px ,int py , int stair , int Dstair , bool check , vector<objects> ob , Player *p);

#endif
