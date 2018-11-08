# ifndef MONSTER_H
# define MONSTER_H

#include<iostream>
#include<string>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdio.h>
#include<climits>
#include<fstream>
#include<iomanip>
#include<vector>
#include<iterator>
#include"map.h"

using namespace std;

enum Ability{SMART = 1, TELE =10 ,TUNNEL=100, ERRATIC = 1000 , NONE =0 ,PASS = -1 ,PICKUP =-2, DESTORY = -3 , UNIQ = -4 , BOSS = -5 };
enum Color{BLACK = 0 , RED = 1 , GREEN = 2 , YELLOW = 3 , BLUE =4 , MAGENTA = 5 , CYAN = 6 , WHITE = 7};

class dices
{
public:
  int side=0;
  int Amount=0;
  int base=0;
public:
  void setup(vector<string> s);
  int Roll();
  string toString();
};

class objects
{
public:
  objects()
  {
   x = 0;
   y = 0;
   Desc = "";
   type = "";
   name = "";
   val = 0;
   hit = 0;
   dodge = 0;
   def = 0;
   speed = 0;
   art = false;
   RRTY = 0;
   weight = 0;
   attr = 0;
   HP = 0;
   Sybol = '*';
  }
  
public:
  int x;
  int y;
  string Desc;
  string type;
  string name;
  Color c[8] = {BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};
  int val;
  dices damage;
  int hit;
  int dodge;
  int def;
  int speed;
  bool art;
  int RRTY;
  int weight;
  int attr;
  int HP;
  char Sybol;
  void setSybol();
  void assignBase(point base[21][80] , int n);
  int SelectColor();
  
};


class Charactor
{
public:
  int x;
  int y;
  int speed;
  int s = 0;
  char type;
  bool Dead = false;
};

class Monster: public Charactor
{
public:
  Ability a[9] = {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}; 
  string name;
  int HP;
  dices Damage;
  int RRTY = 12;
  Color c[8] = {BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};
  char Sybol;
  string Desc;

  void setType();
  string displayAbil();
  int usefulColor();
};

class Player : public Charactor
{
  
};

void addPlayer(Player *p , int px , int py);
void GMonster( room *rooms ,  Monster *Monsters , int size ,  point base[21][80] , int mc, Monster *Cala , int Msize);
char Mtype(int a, int b , int c, int d);
bool IfPC( room *r ,  point base[21][80]);
void setCount(string s ,int *count);
int ImportMonster(Monster **M , string Filename);
void tempc(Monster *M , int size);
vector<string> Split(string s , char c);
bool checkCala(Monster *M);
void ImportObject(vector<objects> *O , string name);
void printobject(vector<objects> O);
void Gobject(vector<objects> *ob, room *rooms , int size  , point base[21][80] , vector<objects> O);

#endif
