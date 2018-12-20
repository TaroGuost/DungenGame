#include <sys/stat.h>

#include "map.h"
#include "RLfile.h"
#include "pQueue.h"
#include "monster.h"
#include "path.h"
#include "move.h"


using namespace std;

int main (int argc , char *argv[])
{
  int i,n;
  point Base[21][80];
  srand (time(NULL));
  int size = 0;
  int Msize;
  int MonsterCount = 10;
  room *rooms;
  int playlocation[2];
  bool issave = false;
  bool isload = false;
  Monster *Monsters;
  Monster *Cala = (Monster*)malloc(sizeof(Monster));
  vector<objects> ob;
  vector<objects> obj;
  Player *player = new Player();
  
  rooms = (room*)malloc(sizeof(room));

  char *home = getenv("HOME");
  char *dir = strcat(home , "/.rlg327");
  //dir = strcat(dir, "/dungeon");
  mkdir(dir,0777);  

  string s = dir;
  string filename = s + "/monster_desc.txt";
  string fname = s + "/object_desc.txt";
  
  n = argc;

  for( i = 0 ; i < n ; i++)
    {
      if(strcmp("--save" , argv[i])==0)
	{
	  issave =true;
	}
      else if(strcmp("--load" , argv[i])==0)
	{
	  isload = true;
	}
      if(strcmp("--n" , argv[i]) == 0)
	{
	  if(argv[i+1] != NULL)
	    {
	      MonsterCount = atoi(argv[i+1]);
	    }
	}
    }

  Monsters = ( Monster*)malloc((MonsterCount)*sizeof( Monster));
	
  if(isload)
    {
      loadFile(Base , rooms , &size , dir , playlocation );
    }
  else
    {
      generatemap(Base , &size , &rooms , playlocation);	  
    }
		
  if(issave)
    {
      WriteFile(size , playlocation , Base , rooms , dir);
    }

  printMap(Base);
  std:: cout << "size of rooms: " << size <<endl;

  printRoom(rooms , size);
  
  Msize = ImportMonster(&Cala,filename);
  tempc(Cala , Msize);
  GMonster(rooms , Monsters , size ,Base , MonsterCount , Cala , Msize);
  ImportObject(&ob,fname);
  Gobject(&obj,rooms,size,Base , ob);
  printobject(&ob);
  
  bool check = MonsterMove(Monsters , MonsterCount, Base , playlocation[0] , playlocation[1], &obj , player);

  while(check)
    {
      free(rooms);
      rooms = (room*)malloc(sizeof(room));
      cleanObject(Base , &obj);
      generatemap(Base , &size , &rooms , playlocation);
      GMonster(rooms , Monsters , size ,Base , MonsterCount , Cala , Msize);
      Gobject(&obj,rooms,size,Base , ob);
      check = MonsterMove(Monsters , MonsterCount, Base , playlocation[0] , playlocation[1],&obj,player);
    }
  free(rooms);
  free(Monsters);
  free(Cala);
  return 0;

}

