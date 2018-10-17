#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <endian.h>
#include <limits.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <ncurses.h>

struct point
{
  int x;
  int y;
  bool check;
  char value;
  int hardness;
};

void printhardness(struct point base[21][80]);


struct Monster
{
  int x;
  int y;
  int speed;
  int s;
  char type;
};

bool Move(struct Monster *M , int mc , struct Monster *Ori , struct point base[21][80], int px , int py, bool check);
bool MoveSix(struct Monster *M, int px , int py , struct point base[21][80] , int mc , bool check , struct Monster *Ori);
bool Moverand(struct Monster *M ,struct point base[21][80] , int mc , bool check , int px ,int py ,struct Monster *Ori);

struct room
{
  int x;
  int y;
  int rw;
  int rl;


};

typedef struct node
{
  int index;

  struct node* next;
}Node;

Node* newNode(int index)
{
  Node *temp = malloc(sizeof(Node));

  temp->index = index;
  temp->next = NULL;

  return temp;

}

void insert(Node** head , int index , int dis[1680] )
{
  Node* temp = (*head);

  Node* New = newNode(index);

  if(dis[(*head)->index]>=dis[New->index])
    {
      New->next = *head;
      (*head) = New;	
    }
  else
    {
      while(temp->next !=NULL && dis[temp->next->index]<dis[New->index])
	{
	  temp = temp->next;
	}

      New->next = temp->next;
      temp->next = New;

    }
}

void Minsert(Node** head , int index , struct Monster *Monsters)
{
  Node* temp = (*head);

  Node* New = newNode(index);

  if(((Monsters+((*head)->index))->speed) > (Monsters+index)->speed)
    {
      New->next = *head;
      (*head) = New;	
    }
  else
    {
      while(temp->next !=NULL && (Monsters+(temp->next->index))->speed <
	    (Monsters+New->index)->speed)
	{
	  temp = temp->next;
	}

      New->next = temp->next;
      temp->next = New;
    }
}

int pop(Node **head )
{
  int n = (*head)->index;
  Node* temp = (*head);
  (*head) = (*head)->next;
  free(temp);
	
  return n;
}

bool isEmpty(Node ** head)
{
  return (*head) == NULL;
}

int build (struct point p[21][80], int x, int y, int width, int length,
	   struct room* r)
{

  int i, j;

  for (i = 0; i < length; i++)
    {
      for (j = 0; j < width; j++)
	{
	  if (i == 0 && p[x - 1][y + j].check && x != 1)
	    {
	      return 0;
	    }
	  else if (j == 0 && p[x + i][y - 1].check && y != 1)
	    {
	      return 0;
	    }
	  else if (x + i >= 20 || y + j >= 79 || p[x + i + 1][y + j + 1].check
		   || p[x + i][y + j + 1].check || p[x + i + 1][y + j].check)
	    {
	      return 0;

	    }

	}
    }



  for(i = 0 ; i < length ; i ++)
    {
      for(j = 0 ; j < width ; j ++)
	{
	  p[x + i][y + j].value = '.';
	  p[x + i][y + j].check = true; 
	  p[x+i][y+j].hardness = 0;
	}
    }


  r->x = x;
  r->y = y;
  r->rl = length;
  r->rw = width;

  return 1;
}

int CreatRoom (struct point p[21][80], struct room *r)
{

  int i, j;
  int width = 3;
  int length = 2;
  int check = 0;
  int temp = 0;

  for (i = 1; i < 20; i++)
    {
      for (j = 1; j < 79; j++)
	{
	  if ((p[i][j].check == false) && ((rand () % 500) % 499 == 0))
	    {
	      width =  rand()% 8 + 3;
	      length = rand()% 8 + 2;

	      temp = check;
	      check += build (p, i, j, width, length, r+temp);
	      //if(check!=temp)
	      //	{
	      //	  r =(struct room*)realloc(r,check*sizeof(struct room)); 
	      //	}
	      printf("x: %d ", (r+temp)->x);
	      printf("y: %d ", (r+temp)->y);
	      printf("#: %d ", temp);
	      printf("address: %p",(r+temp));
	      printf("\n");
	        
	    }
	}
    }


  return check;
}


void initialBase (struct point b[21][80])
{
  int i, j;
  for (i = 0; i < 21; i++)
    {
      for (j = 0; j < 80; j++)
	{

	  if (i == 0 || i == 20)
	    {
	      b[i][j].value = '-';
	      b[i][j].x = i;
	      b[i][j].y = j;
	      b[i][j].check = false;
	      b[i][j].hardness = 255;
	    }
	  else if (j == 0 || j == 79)
	    {
	      b[i][j].value = '|';
	      b[i][j].x = i;
	      b[i][j].y = j;
	      b[i][j].check = false;
	      b[i][j].hardness = 255;
	    }
	  else
	    {
	      b[i][j].value = ' ';
	      b[i][j].x = i;
	      b[i][j].y = j;
	      b[i][j].check = false;
	      b[i][j].hardness = 1+ (rand()%254);

	    }
	}
    }

}

void makeCodder(struct point p[21][80] , int FromX, int FromY, int ToX, int ToY)
{
  int referx = FromX;
  int refery = FromY;
  int tempX , tempY;
  tempX = ToX - FromX;

  while(referx != ToX )
    {
      int temp = rand()%100;

      if(p[referx][refery].value != '.' && p[referx][refery].value != '|')
	{
	  p[referx][refery].value = '#';
	  p[referx][refery].hardness = 0;

	  if(temp%88 == 0 && refery > 1 )
	    {
	      refery--;
	      continue;
	    }
	  else if(temp%77 == 0 && refery <78)
	    {
	      refery++;
	      continue;
	    }
	  else
	    {
	      if(tempX<0)
		referx--;
	      else
		referx++;
	    }
	}
      else
	{
	  if(tempX<0)
	    referx--;
	  else
	    referx++;
	}
    }

  tempY = ToY - refery;

  while(refery != ToY)
    {
      int temp = rand()%100;

      if(p[referx][refery].value != '.' && p[referx][refery].value != '|' )
	{
	  p[referx][refery].value = '#';
	  p[referx][refery].hardness = 0;

	  if(temp%88 == 0 && referx > 1)
	    {
	      referx--;
	      continue;
	    }
	  else if(temp%77 == 0 && referx <19)
	    {
	      referx++;
	      continue;
	    }
	  else
	    {
	      if(tempY<0)
		refery--;
	      else
		refery++;
	    }
	}
      else
	{
	  if(tempY<0)
	    refery--;
	  else
	    refery++;
	}
    }



  tempX = ToX - referx;

  while(referx != ToX)
    {

      if(p[referx][refery].value != '.' && p[referx][refery].value != '|')
	{
	  p[referx][refery].value = '#';
	  p[referx][refery].hardness = 0;

	  if(tempX<0)
	    referx--;
	  else
	    referx++;

	}
      else
	{
	  if(tempX<0)
	    referx--;
	  else
	    referx++;
	}


    }
}

void playerlocate(struct room *r , int size , struct point p[21][80], int loco[2])
{
  int x,y;
  int rooml = 0;
  //rooml = rand()%size;
  x = (r+rooml)->x;
  y = (r+rooml)->y;

  p[x][y].value = '@';

  loco[0] = p[x][y].x;
  loco[1] = p[x][y].y;

}

void ConvertToEndian(uint32_t *i)
{
  *i = htobe32(*i);
}

void ConvertToHost(uint32_t *i)
{
  *i = be32toh(*i);
}

void hardnessMerge(struct point p[21][80] , uint8_t hardness[1680])
{

  int i,j;
  for(i = 0 ; i < 21 ; i ++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{
	  p[i][j].hardness  = (int) hardness[(80*i)+j];
	  if(p[i][j].hardness == 255)
	    {
	      if(i==0 || i == 20)
		{
		  p[i][j].value = '-';
		  p[i][j].x =i;
		  p[i][j].y = j;
		}
	      else if(j==0 || j==79)
		{
		  p[i][j].value = '|';
		  p[i][j].x =i;
		  p[i][j].y = j;
		}
	    }
	  else if(p[i][j].hardness == 0)
	    {
	      p[i][j].value = '#';
	      p[i][j].x =i;
	      p[i][j].y = j;
	    }
	  else
	    {
	      p[i][j].value = ' ';
	      p[i][j].x =i;
	      p[i][j].y = j;
	    }

	}
    }


}

void WriteFile(int size, int playerloco[2] , struct point Base[21][80], struct room *r , char *fname)
{


  if(size != 0)
    {
      int i,j;
      uint8_t roomp[size*4];
      uint8_t *rloco = roomp;
      int n = 0;
      for(i = 0 ; i< sizeof(roomp) ; i +=4)
	{
	  *(rloco+i) = (r+n)->y; 
	  *(rloco+(i+1)) = (r+n)->x;
	  *(rloco+(i+2))= (r+n)->rw;
	  *(rloco+(i+3))=(r+n)->rl;
	  n++;
	}



      FILE *f;
      char *str = "RLG327-F2018";
      uint32_t *Filev;
      uint32_t *fz;


		
      f = fopen(fname , "wb");

		

      uint8_t ploco[] = {playerloco[1] , playerloco[0]};
      uint8_t hardness[1680];
      uint8_t *hs = hardness;



      for(i = 0 ; i < 21;i++)
	{
	  for(j = 0 ;j < 80 ; j ++)
	    {
	      *(hs+(80*i)+j) = Base[i][j].hardness;
	    }
	}

      Filev = (uint32_t*)malloc(sizeof(uint32_t));
      fz = (uint32_t*)malloc(sizeof(uint32_t));

      *Filev = 0;
      *fz = (1702+(size*4));

      ConvertToEndian(Filev);
      ConvertToEndian(fz);

      fwrite(str, 1 , 12 , f);
      fwrite(Filev , 4 , 1 , f);
      fwrite(fz , 4, 1 ,f);
      fwrite(ploco, 1 , 2 , f);
      fwrite(hardness,1,1680,f);
      fwrite(roomp,1, size*4 ,f);

      fclose(f);

    }
}

void loadFile(struct point p[21][80], struct room *r , int *size , char *fname ,int PlayLocation[2])
{

  FILE *read;
  read = fopen("hello.rlg327" , "rb");

  int i,j ,n;


  char str[12];
  uint32_t Filec;
  uint32_t rz;
  uint8_t hardness[1680];
  uint8_t ploco[2];
  //uint8_t hs = hardness;
  //uint8_t po = ploco;   

  fread(str , 1 ,12,read);
  fread(&Filec , 4 , 1 , read);
  fread(&rz , 4, 1 ,read);
  fread(ploco,1,2,read);
  fread(hardness,1,1680,read);

  hardnessMerge(p,hardness);

  ConvertToHost(&rz);
  ConvertToHost(&Filec);


  *size = ((int)(rz)-1702)/4;
  uint8_t roomp[*size*4];
  uint8_t *rp = roomp;

  fread(rp,1,(*size)*4,read);

  r = (struct room*)malloc(*size*sizeof(struct room));

  n = 0;

  for(i = 0 ; i < sizeof(roomp) ; i +=4)
    {
      (r+n)->x = (int)roomp[i];
      (r+n)->y = (int)roomp[i+1];
      (r+n)->rl = (int)roomp[i+2];
      (r+n)->rw = (int)roomp[i+3];
      n++;
    }


  //struct point temp[21][80];
  //initialBase (temp);

  n= 0;

  while(n != *size)
    {
      for(i = 0 ; i < (r+n)->rw ; i ++)
	{
	  for(j = 0 ; j<(r+n)->rl; j ++)
	    {
	      p[((r+n)->y)+i][((r+n)->x)+j].value = '.';
	      p[((r+n)->y)+i][((r+n)->x)+j].x = i;
	      p[((r+n)->y)+i][((r+n)->x)+j].y = j;

	    }
	}
      n++;
    }



  p[ploco[1]][ploco[0]].value = '@';
  p[ploco[1]][ploco[0]].x = ploco[1];
  p[ploco[1]][ploco[0]].y = ploco[0];

  PlayLocation[0]=ploco[1];
  PlayLocation[1]=ploco[0];

  for (i = 0; i < 21; i++)
    {
      for (j = 0; j < 80; j++)
	{
	  printf ("%c", p[i][j].value);
	}
      printf ("\n");
    }


  fclose(read);

} 

void generatemap(struct point Base[21][80] , int *size , struct room *rooms , int playlocation[2])
{

  int i, j;

  do
    {
      //   initialRoom (rooms);
      initialBase (Base);
      *size = CreatRoom (Base, rooms);
    }
  while (*size < 5);

  for( i = 0 ; i < *size ; i ++)
    {
      printf("x: %d " , (rooms+i)->x);
      printf("y: %d ", (rooms+i)->y);
      printf("#: %d ", i);
      printf("address: %p",(rooms+i));
      printf("\n");
    }
	
  for (i = 0; i < *size; i++)
    {
      int fromx, tox , fromy , toy;

      if (i == *size - 1)
	{
	  fromx = ((rooms+i)->x) + rand () % ( (rooms+i)->rl );
	  tox = (rooms -> x) +  rand () % (rooms->rl);
	  fromy = ((rooms+i)->y) +rand () % ( ((rooms+i)->rw) );
	  toy = (rooms -> y) + rand () % ( (rooms->rw));
	  makeCodder (Base, fromx, fromy,
		      tox, toy);
	}
      else
	{
	  fromx = ((rooms+i)->x) + rand () % ( (rooms+i)->rl );
	  tox = ((rooms +i+1)-> x) +rand () %  ((rooms+i+1)->rl);
	  fromy = ((rooms+i)->y) + rand () % ( (rooms+i)->rw );
	  toy = ((rooms+i+1) -> y) + rand () % ( (rooms+i+1)->rw);
	  makeCodder (Base, fromx, fromy,
		      tox, toy);
	}


    }



  playerlocate(rooms,*size,Base,playlocation);


  for (i = 0; i < 21; i++)
    {
      for (j = 0; j < 80; j++)
	{
	  printf ("%c", Base[i][j].value);
	}
      printf ("\n");
    }

}

int calculateindex(int x , int y)
{
  return (80*x)+y; 
}

void printPath(int dis[1680] ,Node **head , struct point *source)
{
  int i,j;

  for(i = 0 ; i < 21 ;i++)
    {
      for(j = 0 ; j < 80 ; j++)
	{
	  if(source->x ==i && source->y==j)
	    {
	      printf("%c" , '@');
	    }
	  else if(dis[calculateindex(i,j)] !=-1)
	    {
	      int n= dis[calculateindex(i,j)]%10;
	      printf("%d", n);
	    }
	  else
	    {
	      printf("%c" , ' ');
	    }
	}

      printf("\n");
    }
}

void printhardness(struct point base[21][80])
{
  int i, j;

  for(i = 0 ; i < 80 ; i++)
    {
      printf("%d",i%10);

    }

  for(j = 0 ;j < 1680 ; j ++)
    {
      if(j%80 ==0)
	printf("\n");

      printf("%d" , base[j/80][j%80].hardness/85);
    }
  printf("\n" );


}

int getLength(int  p)
{
  if(p == 255)
    {
      return 3;
    }
  else if(p == 0)
    {
      return 1;
    }
  else
    {
      return 1 + (p/85);
    }


}

void FindShortestPath(struct point base[21][80], struct point *source, int dis[1680])
{
  int i,j;
  int movex[8] = {-80,-80,-80,0,0,80,80,80};
  int movey[8] = {-1,0,1,-1,1,-1,0,1};
  int alt;
  Node* pq = newNode(calculateindex(source->x,source->y));
  dis[calculateindex(source->x, source->y)] = 0;

  for(i = 0 ; i < 21 ; i++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{
	  if(base[i][j].value =='.' || base[i][j].value == '#' )
	    {
	      dis[calculateindex(i,j)] = INT_MAX;
	      insert(&pq,calculateindex(i,j),dis);
	    }
	  else if(base[i][j].value =='@')
	    {
	      dis[calculateindex(i,j)] = 0;
	    }
	  else
	    {
	      dis[calculateindex(i,j)] = -1;
	    }
	}
    }
  //	printPath(dis , &pq);

  while(!isEmpty(&pq))
    {

      int u = pop(&pq);

      for(i = 0 ; i < 8 ; i ++)
	{
	  alt =0;
	  int v =u+movex[i]+movey[i];
	  if(v<0 || v>1680)
	    {
	      continue;
	    }

	  if(dis[v]>=0)
	    {
	      alt = dis[u]+ 1;

	      if(alt < dis[v])
		{
		  dis[v] = alt;
		  insert(&pq , v,dis);
		}

	    }	
	}	
    }

  //	printPath(dis , &pq ,source);
  free(pq);
}

void printWallPath(int dis[1680] ,struct point *source)
{
  int i,j;

  for(i = 0 ; i < 21 ;i++)
    {
      for(j = 0 ; j < 80 ; j++)
	{
	  if(source->x == i && source->y== j)
	    {
	      printf("%c" , '@');
	    }
	  else if(dis[calculateindex(i,j)] != -1)
	    {
	      int n= dis[calculateindex(i,j)]%10;
	      printf("%d" , n );
	    }
	  else{
	    printf(" ");
	  }
	}

      printf("\n");
    }
}



void FindShortestPathWithWall(struct point base[21][80], struct point *source , int dis[1680])
{
  int i,j;
  int movex[8] = {-80,-80,-80,0,0,80,80,80};
  int movey[8] = {-1,0,1,-1,1,-1,0,1};
  int alt;
  Node* pq = newNode(calculateindex(source->x,source->y));
  dis[calculateindex(source->x, source->y)] = 0;

  for(i = 0 ; i < 21 ; i++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{


	  if(base[i][j].value != '@' && base[i][j].value != '|' && base[i][j].value != '-')
	    {
	      dis[calculateindex(i,j)] = 99999;
	      insert(&pq,calculateindex(i,j),dis);
	    }
	  else if(base[i][j].value != '@')
	    {
	      dis[calculateindex(i,j)] = -1;
	    }

	}
    }
  //	printhardness(base);
  int count = 0 ;
  while(!isEmpty(&pq))
    {
      int u = pop(&pq);

      for (i = 0 ; i < 8 ; i ++)
	{
	  alt =0;

	  int v = u+movex[i]+movey[i];

	  if(v<0 || v>1680)
	    {
	      continue;
	    }

	  if(dis[v]>=0 )
	    {
	      alt = dis[u]+getLength(base[u/80][u%80].hardness);

	      if(alt < dis[v])
		{			 
		  dis[v] = alt;
		  insert(&pq , v , dis);
		}

	    }

	}

    }


  //	printWallPath(dis ,source);
  free(pq);
}

char Mtype(int a, int b , int c ,int d)
{
  long int bin , hex= 0 , i =1 , temp;
  bin = (rand()+1)%a + ((rand()+1)%b*10)+ ((rand()+1)%c*100)+ ((rand()+1)%d*1000);
  while(bin != 0)
    {
      temp = bin%10;
      hex += temp*i;
      i = i*2;
      bin = bin/10;
    }

    
  return hex;
    
    
}


int isSamePlace(struct Monster *Monsters , int mc , int x , int y)
{

  int i;
  for(i = 0 ; i < mc ; i ++ )
    {
      if((Monsters+i)->x == x && (Monsters+i)->y == y)
	{
	  return i;
	}
    }
  return -1;
}


int GeneStair(struct point base[21][80])
{
  int i,j , x;

  x =0;
  
  for(i = 0 ; i < 21 ; i ++)
    {
      for(j = 0 ; j < 80 ; j++)
	{
	  if(base[i][j].value == '.')
	    {
	      base[i][j].value = '<';
	      return i*80+j;
	    }
	} 
    }


  
}


void PrintMonster(WINDOW **game ,struct Monster *ms , int mc , struct point base[21][80] , int px , int py , int stair)
{
  int i,j;
  
  char temp[mc];

  

  for(i = 0 ; i < 21 ; i ++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{
	  if(base[i][j].value == ' ' && base[i][j].hardness == 0)
	    {
	      base[i][j].value = '#';
	    }

	  if(i == stair/80 && j == stair%80)
	    {
	       base[i][j].value ='<';
	       // mvwprintw(*game,i,j,"%c" , base[i][j].value);
	       //refresh();
	    }

	  int temp = isSamePlace(ms,mc,i,j);
	  if(temp  != -1)
	    {
	      mvwprintw(*game,i,j,"%lx" , (ms+temp)->type);
	      //refresh();
	    }
	  else
	    {
	      mvwprintw(*game,i,j,"%c" , base[i][j].value);
	      //refresh();
	    }

	   if(i == px && j == py)
	  {
	   mvwprintw(*game,i,j,"%c" , '@');
	  // refresh();
	  }
	  
	}
    }
  //refresh();

}



bool IfPC(struct room *r , struct point base[21][80])
{
  int i,j;

  for(i = (r->x) ; i < ((r->x)+(r->rw)) ; i ++)
    {
      for(j = (r->y) ; j < ((r->y)+(r->rl)); j ++)
	{
	  if(base[i][j].value == '@')
	    {
	      return true;
	    }
	}
    }
  
  return false;
}


void GMonster(struct room *rooms , struct Monster *Monsters , int size , struct point base[21][80] , int mc)
{
  int MonsterCount = 0;
  int i;

  while(MonsterCount < mc)
    {
      int random = (rand()%size);
      if(!IfPC(rooms+random, base))
	{
	  (Monsters+MonsterCount)->x = ((rooms+random)->x)+(rand()%(rooms+random)->rl);
	  (Monsters+MonsterCount)->y = ((rooms+random)->y)+(rand()%(rooms+random)->rw);
	  (Monsters+MonsterCount)->type = Mtype(2,2,2,2);
	  (Monsters+MonsterCount)->speed = 0;
	  (Monsters+MonsterCount)->s = (rand()%16)+5;
	  MonsterCount++;
	}
    }
  

}

bool EMove(struct Monster *Monsters,struct Monster *Ori , int mc , int px , int py ,struct point base[21][80] , char temp)
{
  bool dead = false;
  
  switch(temp)
    {
    case 0 :
      dead = Moverand(Monsters,base, mc, false , px , py , Ori);
      break;
    case 1:
      if(Monsters->x == px || Monsters->y == py)
	dead = Move(Monsters,mc,Ori,base,px,py,false);
      else
	dead = Moverand(Monsters,base, mc, false , px , py , Ori);
      break;
    case 2:
      dead = MoveSix(Monsters,px ,py ,base , mc , false, Ori);
      break;
    case 3:
      dead = Move(Monsters,mc,Ori,base,px,py,false);
      break;
    case 4:
      dead = Moverand(Monsters,base,mc,true,px,py,Ori);
      break;
    case 5:
      if(Monsters->x == px || Monsters->y == py)
	dead = Move(Monsters,mc,Ori,base,px,py,true);
      else
	dead = Moverand(Monsters,base, mc, true , px , py , Ori);
      break;
    case 6:
      dead = MoveSix(Monsters , px , py , base ,mc ,true,Ori);
      break;
    case 7:
      dead = Move(Monsters,mc,Ori,base,px,py,true);
      break;
    }

  return dead;

}

void PrintLose(struct Monster *Monsters)
{
  int i, j;
  for(i = 0 ; i < 21 ; i ++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{
	  if(i == 21/2 && j == 80/2)
	    {
	      printf("YOU DEAD!!!!   ");
	      printf("%lx KILLED YOU", Monsters->type);
	    }
	  else
	    {
	      printf(" ");
	    }
	}
      printf("\n");
    }


}

void addPlayer(struct Monster *M , int mc , int px , int py)
{
  (M+mc)->x = px;
  (M+mc)->y = py;
  (M+mc)->type = '@';
  (M+mc)->s = 10;
  (M+mc)->speed = 0;
}

void PrintList(WINDOW **list,int mc, int px ,int py,struct Monster *M,int n)
{
  int i,j;

  //mvwprintw(*list,0,9 , "MonsterList");

  
  for(i =0  ; i < 5 ; i++)
    {
      int Rx = px - (M+i+n)->x;
      int Ry = py - (M+i+n)->y;
	  
      if(Rx > 0 && Ry>0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d North and %d West ",(M+i+n)->type , Rx , Ry);
	}
      else if(Rx > 0 && Ry < 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d North and %d East ",(M+i+n)->type , Rx , (Ry*-1));
	}
      else if(Rx < 0 && Ry > 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d South and %d West ",(M+i+n)->type , Rx*-1 , Ry);
	}
      else if(Rx < 0 && Ry < 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d South and %d East ",(M+i+n)->type , Rx*-1 , Ry*-1);
	}
      else if(Rx > 0 && Ry == 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d North",(M+i+n)->type , Rx);
	}
      else if(Rx < 0 && Ry == 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d South",(M+i+n)->type , Rx*-1);
	}
      else if(Rx == 0 && Ry < 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d West ",(M+i+n)->type , Ry*-1);
	}
      else if(Rx == 0 && Ry > 0)
	{
	  mvwprintw(*list,i+1,1,"%lx, %d East ",(M+i+n)->type , Rx*-1);
	}
       
    }

   

}

void MonsterList(struct Monster *M, int mc , int px , int py)
{
  int i = 0;
  int n = 0;

  WINDOW *list;
  list = newwin(8,30,10,20);
  keypad(list,true);
  wborder(list,'*','*','*','*','*','*','*','*');
  while(i != 1)
    {
      PrintList(&list,mc,px,py,M,n);
      int ch = wgetch(list);
      switch(ch)
	{
	case 'e':
	  i =1;
	  break;
	case KEY_DOWN:
	  if(n+5<mc)
	    n++;
	  break;
	case KEY_UP:
	  if(n>0)
	    n--;
	  break;
	}
      
    }
  

  //werase(list);
  wclrtoeol(list);
  wrefresh(list);
  delwin(list);
  //endwin();
  
  
}

char PCMove(struct Monster *M , struct point base[21][80], WINDOW **game , char store, struct Monster *Ori,int mc,int stair)
{

  base[M->x][M->y].value = store;
  bool check = true;

   
    
   while(check == true)
  {
       
      int ch = wgetch(*game);
      switch(ch)
	{
	case KEY_DOWN:
	  if(base[(M->x)+1][M->y].hardness ==0)
	    {
	      M->x = (M->x)+1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_UP:
	  if(base[(M->x)-1][M->y].hardness ==0)
	    {
	      M->x = (M->x)-1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_LEFT:
	  if(base[M->x][(M->y)-1].hardness ==0)
	    {
	      M->y = (M->y)-1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_RIGHT:
	  if(base[M->x][(M->y)+1].hardness ==0)
	    {
	      M->y = (M->y)+1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_HOME:
	  if(base[(M->x)-1][(M->y)-1].hardness ==0)
	    {
	      M->y = (M->y)-1;
	      M->x = (M->x)-1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_END:
	  if(base[(M->x)-1][(M->y)+1].hardness ==0)
	    {
	      M->y = (M->y)+1;
	      M->x = (M->x)-1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_PPAGE:
	  if(base[(M->x)+1][(M->y)-1].hardness ==0)
	    {
	      M->y = (M->y)-1;
	      M->x = (M->x)+1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case KEY_NPAGE:
	  if(base[(M->x)+1][(M->y)+1].hardness ==0)
	    {
	      M->y = (M->y)+1;
	      M->x = (M->x)+1;
	      store =  base[M->x][M->y].value;
	      base[M->x][M->y].value = '@';
	      check = false;
	    }
	  break;
	case 32:
	  check =false;
	  store =  base[M->x][M->y].value;
	  break;
	case 'q':
	  check = false;
	  store = '!';
	  break;
	case 'm':
	  MonsterList(Ori,mc,M->x,M->y);
	  PrintMonster(game, Ori , mc,base,M->x,M->y,stair);
	  break;
	case 'i':
	  if(M->x == stair/80 && M->y == stair%80)
	    {
	      store = '^';
	      check = false;
	    }
	  break;
	      
	}
      }

 	
  return store;

  
}

void tempprint(WINDOW** temp)
{
  int i , j ;
  for(i = 0 ; i < 21 ; i++)
    {
      for(j = 0 ; j <80;j++)
	{
	  mvwprintw(*temp,i,j,"%c" , '*');
	}
    }
}

bool MonsterMove(struct Monster *Monsters , int mc, struct point base[21][80] , int px , int py)
{
  addPlayer(Monsters , mc , px ,py);
  int i,j;
  bool dead = false;
  Node* mq = newNode(mc);
  bool change = false;
  bool seeP = false;
  char store = '.';
  const int stair = GeneStair(base);

  
  for(i = 0 ; i < mc ; i++)
    {
      Minsert(&mq , i , Monsters);
    }

 
   
  initscr();
  noecho();
  cbreak();

  WINDOW *game;
  game = newwin(24,80,0,0);

  keypad(game,true);
   
     
  while(!dead)
    {
      int  n = pop(&mq);

      switch((Monsters+n)->type)
	{
	case 0:
	  dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	  break;
	case 1:
	  if((Monsters+n)->x == px || (Monsters+n)->y == py)
	    dead = Move((Monsters+n),mc,Monsters,base,px,py,false);
	  else
	    dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	  break;
	case 2:
	  dead = MoveSix((Monsters+n),px ,py ,base , mc , false,Monsters);
	  break;
	case 3:
	  dead = Move((Monsters+n),mc,Monsters,base,px,py,false);
	  break;
	case 4:
	  dead = Moverand((Monsters+n),base,mc,true,px,py,Monsters);
	  break;
	case 5:
	  if((Monsters+n)->x == px || (Monsters+n)->y == py || change ==true)
	    {
	      dead = Move((Monsters+n),mc,Monsters,base,px,py,true);
	      change = true;
	    }
	  else
	    {
	      dead = Moverand((Monsters+n),base, mc, true , px , py , Monsters);
	    }
	  break;
	case 6:
	  dead = MoveSix((Monsters+n) , px , py , base ,mc ,true,Monsters);
	  break;
	case 7:
	  dead = Move((Monsters+n),mc,Monsters,base,px,py,true);
	  break;
	case 8:
	  dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	  break;
	case 9:
	  if(rand()%2 == 0)
	    {
	      if((Monsters+n)->x == px || (Monsters+n)->y == py || seeP ==true)
		{
		  dead = Move((Monsters+n),mc,Monsters,base,px,py,false);
		  seeP = true;
		}
	      else
		{
		  dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
		}
	    }
	  else
	    {
	      dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	    }
	  break;
	case 10:
	  if(rand()%2 ==0)
	    {
	      dead = MoveSix((Monsters+n),px ,py ,base , mc , false , Monsters);
	    }
	  else
	    {
	      dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	    }
	  break;
	case 11:
	  dead = EMove((Monsters+n),Monsters, mc , px , py,base, Mtype(1,1,2,2));
	  break;
	case 12:
	  if(rand()%2 ==0)
	    {
	      dead = Moverand((Monsters+n),base,mc,true,px,py,Monsters);
	    }
	  else
	    {
	      dead = Moverand((Monsters+n),base, mc, false , px , py , Monsters);
	    }
	  break;
	case 13:
	  dead =  EMove((Monsters+n),Monsters, mc , px , py,base, Mtype(1,2,1,2));
	  break;
	case 14:
	  dead =  EMove((Monsters+n),Monsters, mc , px , py,base , Mtype(1,2,2,1));
	  break;
	case 15:
	  dead =  EMove((Monsters+n),Monsters, mc , px , py,base, Mtype(1,2,2,2));
	  break;
	case '@':
	  usleep(250000);
	  PrintMonster(&game,Monsters, mc , base,px,py , stair);
	  //tempprint(&game);
	  store = PCMove((Monsters+n),base,&game,store,Monsters,mc,stair);
	  px = (Monsters+n)->x;
	  py = (Monsters+n)->y;
	  break;
	}

      if(store == '!')
	{
	  clrtoeol();
	  refresh();
	  endwin();
	  printf("\n YourQuitGame!!!D:\n");
	  break;
	}

      if(store == '^')
	{
	  clrtoeol();
	  refresh();
	  endwin();
	  return true;
	}
	 
      if(dead)
	{
	  clrtoeol();
	  refresh();
	  endwin();
	  PrintLose(Monsters+n);
	  break;  
	}

	  
      (Monsters+n)->speed += (Monsters+n)->s;
      Minsert(&mq , n , Monsters);


    }

  return false;
       
}


bool Move(struct Monster *M, int mc , struct Monster *Ori , struct point base[21][80],int px, int py, bool check)
{
  int movex[8] = {-80,-80,-80,0,0,80,80,80};
  int movey[8] = {-1,0,1,-1,1,-1,0,1};
  int i,j;
  int x = 0;
  int y = 0;
  int dis[1680];

  if(check == true)
    FindShortestPathWithWall(base , &base[px][py],dis);
  else
    FindShortestPath(base,&base[px][py],dis);
  

  int min = dis[calculateindex(M->x,M->y)];
   

   
  for(i = 0 ; i < 8 ; i ++)
    {

      int v = calculateindex(M->x,M->y) + movex[i] + movey[i];

      if( v<=0 || v>=1680)
	{
	  continue;
	}
     
      if(dis[v] != -1 )
	{
        
	  if(dis[v] < min  && isSamePlace(Ori , mc , v/80 , v%80) == -1)
	    {	
	      x = v/80;
	      y = v%80;
	      min = dis[v];
	    }

	  
	}

    }

  if(M->x == px && M->y == py)
    {
      return true;
    }
  
  if(dis[calculateindex(M->x,M->y)]- dis[calculateindex(x,y)] > 1  )
    {
      dis[calculateindex(x,y)]++;
    }
  else
    {

      if(x != 0 && y !=0)
	{
	  (M->x)= x;
	  (M->y)= y;
	  base[x][y].hardness = 0;
        }

      if(M->x == px && M->y == py)
	{
	  return true;
	}

    }
  
  return false;
     
}

bool MoveSix(struct Monster *M, int px , int py , struct point base[21][80], int mc , bool check, struct Monster *Ori)
{
  int referx = px - M->x;
  int refery = py - M->y;

  if((referx == 0 && refery ==1) || (referx == 0 && refery ==-1))
    {
      return true;
    }

  
  if(referx != 0)
    {
      if(referx > 0)
	{
	  
	  if(base[(M->x)+1][M->y].value != ' ' && isSamePlace(Ori , mc , (M->x)+1 , (M->y)) == -1 && check == false)
	    {
	      M->x = (M->x)+1;
	      base[M->x][M->y].hardness = 0;
	    }
	  else if(isSamePlace(Ori , mc , (M->x)+1 , (M->y)) == -1 && check == true)
	    {
	      if(base[(M->x)+1][M->y].hardness/85 > 0)
		{
		  base[(M->x)+1][M->y].hardness -= 85;
		}
	      else
		{
		  M->x = (M->x)+1;
		  base[M->x][M->y].hardness = 0;
		}
	    }
	}
      else if(referx < 0)
	{
	  if(base[(M->x)-1][M->y].value != ' ' && isSamePlace(Ori , mc , (M->x)-1 , (M->y)) == -1 && check == false)
	    {
	      M->x = (M->x)-1;
	      base[M->x][M->y].hardness = 0;
	    }
	  else if(isSamePlace(Ori , mc , (M->x)-1 , (M->y)) == -1 && check == true)
	    {
	      if(base[(M->x)-1][M->y].hardness/85 > 0)
		{
		  base[(M->x)-1][M->y].hardness -= 85;
		}
	      else
		{
		  M->x = (M->x)-1;
		  base[M->x][M->y].hardness = 0;
		}
	    }

	}
    }
  else if(refery != 0 || (referx == (px - M->x) && referx != 0))
    {

      if(refery > 0)
	{
	  if(base[M->x][(M->y)+1].value != ' ' && isSamePlace(Ori , mc , (M->x) , (M->y)+1) == -1 && check == false)
	    {
	      M->y = (M->y) +1;
	      base[M->x][M->y].hardness = 0;
	    }
	  else if(isSamePlace(Ori , mc , (M->x) , (M->y)+1) == -1 && check == true)
	    {
	      if(base[M->x][(M->y)+1].hardness/85 > 0)
		{
		  base[M->x][(M->y)+1].hardness -=85;
		}
	      else
		{
		  M->y = (M->y)+1;
		  base[M->x][M->y].hardness = 0;
		}
	    }
	}
      else if(refery <0)
	{
	  if(base[M->x][(M->y)-1].value != ' ' && isSamePlace(Ori , mc , (M->x) , (M->y)-1) == -1 && check == false)
	    {
	      M->y = (M->y) -1;
	      base[M->x][M->y].hardness = 0;
	    }
	  else if(isSamePlace(Ori , mc , (M->x) , (M->y)-1) == -1 && check == true)
	    {
	      if(base[M->x][(M->y)-1].hardness/85 > 0)
		{
		  base[M->x][(M->y)-1].hardness -=85;
		}
	      else
		{
		  M->y = (M->y)-1;
		  base[M->x][M->y].hardness = 0;
		}
	    }
	}

    }
  else
    {
      return true;
    }

  return false;

}

bool Moverand(struct Monster *M ,struct point base[21][80] , int mc , bool check , int px ,int py,struct Monster *Ori)
{
  int movex[8] = {-1,-1,-1,0,0,1,1,1};
  int movey[8] = {-1,0,1,-1,1,-1,0,1};
  int i = rand()%8;

  int  x = (M->x)+movex[i];
  int  y = (M->y)+movey[i];
  if(x > 19 || x < 1  || y >78 || y <1 )
    {
      return false;
    }
   
  if(check == false)
    {

      if(base[x][y].hardness == 0 && isSamePlace(Ori , mc , x, y) == -1)
	{
	  M->x = x;
	  M->y = y;
	}
    }
  else
    {
      if( isSamePlace(M , mc , x, y) == -1)
	{
	  if(base[x][y].hardness/85 > 0)
	    {
	      base[x][y].hardness -= 85;
	    }
	  else
	    {
	      M->x = x;
	      M->y = y;
	      base[M->x][M->y].hardness = 0;
	    }
	}
    }
   
  if(M->x == px && M->y == py)
    {
      return true;
    }

  return false;
}


int main (int argc , char *argv[])
{
  int i,n;
  struct point Base[21][80];
  srand (time(NULL));
  int size = 0;
  int MonsterCount = 10;
  struct room *rooms;
  int playlocation[2];
  bool issave = false;
  bool isload = false;
  int dis[1680];
  int disw[1680];
  struct Monster *Monsters;
	

  rooms = (struct room*)malloc(10*sizeof(struct room));

  char *home = getenv("HOME");
  char *dir = strcat(home , "/111.rlg327");
  //dir = strcat(dir, "/dungeon");

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

  Monsters = (struct Monster*)malloc((MonsterCount+1)*sizeof(struct Monster));
	
  if(isload)
    {
      loadFile(Base , rooms , &size , dir , playlocation );
    }
  else
    {
      generatemap(Base , &size , rooms , playlocation);	  
    }

		
		
  if(issave)
    {
      WriteFile(size , playlocation , Base , rooms , dir);
    }
		
  GMonster(rooms , Monsters , size ,Base , MonsterCount);
	       
  //PrintMonster(Monsters , MonsterCount, Base,playlocation[0],playlocation[1]);	   
  bool check = MonsterMove(Monsters , MonsterCount, Base , playlocation[0] , playlocation[1]);

  while(check)
    {
      generatemap(Base , &size , rooms , playlocation);
      GMonster(rooms , Monsters , size ,Base , MonsterCount);
      //  PrintMonster(Monsters , MonsterCount, Base,playlocation[0],playlocation[1]);	   
      check = MonsterMove(Monsters , MonsterCount, Base , playlocation[0] , playlocation[1]);
    }
			
			
			
	       
  return 0;


}

