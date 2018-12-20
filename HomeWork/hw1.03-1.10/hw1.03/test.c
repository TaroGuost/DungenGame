#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <endian.h>
#include<limits.h>
#include<math.h>


struct point
{
  int x;
  int y;
  bool check;
  char value;
  int hardness;
};

void printhardness(struct point base[21][80]);


struct room
{
  int x;
  int y;
  int rw;
  int rl;
  

};

typedef struct Node
{
  int index;
  
  struct Node* next;
}Node;

Node* newNode(int index)
{
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->index = index;
	temp->next = NULL;

	return temp;
	
}

void insert(Node** head , int index  )
{
  //	Node* temp = (*head);
	
	Node* New = newNode(index);

	New->next = *head;
	(*head) = New;	
}

int pop(Node **head , int dis[1680])
{
        int n = INT_MAX;
	Node* temp = (*head);
	Node* min = (*head);

	if(dis[(*head)->index]<n)
	  {
	    n = temp->index;
	  }

	while(temp->next != NULL)
	{
	  if(dis[((temp->next)->index)] < n)
		{
			min = temp;
			n = (temp->next)->index;
		}
		
		temp = temp->next;
	}

	temp = min->next;

	if(min->next !=NULL)
	  {
	    if(min == *head)
	      {
		temp = *head;
		(*head) = (*head)->next;
		free(temp);
	      }
	    else
	      {
		min->next = (temp)->next;
		//	free(temp);
	      }
	  }
	else
	  {
	   
	    if(min == (*head))
	      {
		*head = NULL;
		free(*head);
	      }
	  }

	return n;
}

bool isEmpty(Node ** head)
{
	return (*head) == NULL;
}

int
build (struct point p[21][80], int x, int y, int width, int length,
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

int
CreatRoom (struct point p[21][80], struct room *r)
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
	    }
	}
    }


  return check;
}


void
initialBase (struct point b[21][80])
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
  int rooml;
  rooml = rand()%size;
  x = (r+rooml)->x;
  y = (r+rooml)->y;

  p[x][y].value = '@';
  
  loco[0] = p[x][y].x;
  loco[1] = p[x][y].y;
  
}

void ConvertToEndian(int *i)
{
*i = htobe32(*i);
}

void ConvertToHost(int *i)
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
   
    f = fopen(fname , "wb");

    char str[] = "RLG327-F2018";
    char *pt = str;
    uint32_t *Filev;
    uint32_t *fz;


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
    
    
   
    

    Filev = (int*)malloc(sizeof(int));
    fz = (int*)malloc(sizeof(int));

    *Filev = 0;
    *fz = (1702+(size*4));

    ConvertToEndian(Filev);
    ConvertToEndian(fz);

    
    
    fwrite(pt, 1 , 12 , f);
    fwrite(Filev , 4 , 1 , f);
    fwrite(fz , 4, 1 ,f);
    fwrite(ploco, 1 , 2 , f);
    fwrite(hardness,1,1680,f);
    fwrite(roomp,1, size*4 ,f);

    

   
   fclose(f);
    
    }
}

void loadFile(struct point p[21][80], struct room *r , int *size , char *fname ,int PlayLocation[2] )
{

    FILE *read;
    read = fopen("101.rlg327" , "rb");

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

int printPath(int dis[1680] ,Node **head , struct point *source)
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

void FindShortestPath(struct point base[21][80], struct point *source)
{
	int i,j;
	int dis[1680];
	int pre[1680];
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
				insert(&pq,calculateindex(i,j));
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
	  
		int u = pop(&pq , dis);
		
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
				  insert(&pq , v);
				}
			    
			}	
		}	
	}
	
	printPath(dis , &pq ,source); 
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



void FindShortestPathWithWall(struct point base[21][80], struct point *source)
{
	int i,j;
	int dis[1680];
	int movex[8] = {-80,-80,-80,0,0,80,80,80};
	int movey[8] = {-1,0,1,-1,1,-1,0,1};
	int alt;
	int count =0;
	Node* pq = newNode(calculateindex(source->x,source->y));
       	dis[calculateindex(source->x, source->y)] = 0;
	
	for(i = 0 ; i < 21 ; i++)
	{
		for(j = 0 ; j < 80 ; j ++)
		{
			
			
		  if(base[i][j].value != '@' && base[i][j].value != '|' && base[i][j].value != '-')
		  {
				dis[calculateindex(i,j)] = INT_MAX;
				insert(&pq,calculateindex(i,j));
		  }
		  else if(base[i][j].value != '@')
		   {
		                dis[calculateindex(i,j)] = -1;
		   }

		}
	}
	

	//	printhardness(base);

	while(!isEmpty(&pq))
	{
	  
	
		int u = pop(&pq , dis);
		//bool check = (getLength(base[u/80][u%80].hardness)==1);
   
	        
		for(i = 0 ; i < 8 ; i ++)
		{
		        alt =0;
			
			
			int v =u+movex[i]+movey[i];

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
					      	insert(&pq , v);
				}
				
				}
			
			
		
			
		}
		
	}

        
	printWallPath(dis ,source); 
}




int main (int argc , char *argv[])
{
  int i,n;
  struct point Base[21][80];
  srand (time(NULL));
  int size = 0;
  struct room *rooms;
  int playlocation[2];
  bool issave = false;
  bool isload = false;
  
  rooms = (struct room*)malloc(sizeof(struct room));
  
  char *home = getenv("HOME");
  char *dir = strcat(home , "/.rlg327");
  dir = strcat(dir, "/dungeon");

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
    }

  //if(isload)
  //{
      loadFile(Base , rooms , &size , dir , playlocation );
  //	  	  	 }
  //	   else
  //	  {
  //      generatemap(Base , &size , rooms , playlocation);	  
  //	   }


  //	  if(issave)
  //	  {
  //	    WriteFile(size , playlocation , Base , rooms , dir);
  //}

    
	  FindShortestPath(Base ,&Base[playlocation[0]][playlocation[1]]);
	  FindShortestPathWithWall(Base , &Base[playlocation[0]][playlocation[1]]);
    
  return 0;

     
}

