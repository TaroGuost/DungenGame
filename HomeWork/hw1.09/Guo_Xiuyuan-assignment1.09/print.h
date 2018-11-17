#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <string>
#include <ncurses.h>
#include "map.h"
#include "monster.h"
#include "move.h"

using namespace std;

void PrintMonster(WINDOW **game , Monster *ms , int mc , point base[21][80] , int px , int py , int stair , int Dstair , bool check , vector<objects> ob ,Player *p);
void PrintLose(Charactor *Monsters);
void PrintList(WINDOW **list , int mc , int px , int py , Monster *M , int n);
void MonsterList(Monster *M , int mc , int px , int py);
void PCteleport(WINDOW **game , point base[21][80] , Player *M , bool fog);
void printslot(WINDOW **list , Player *p , int highlight , vector<objects> *ob);
void printDesc(WINDOW **list , string temp);
void slotList(Player *p , point base[21][80] , vector<objects> *obj);
void equiList(Player *p);
void CheckMonster(WINDOW **game , Monster *Ori , point base[21][80] , int mc , bool fog);




#endif
