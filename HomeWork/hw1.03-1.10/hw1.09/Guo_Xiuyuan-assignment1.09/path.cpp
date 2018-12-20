#include "path.h"

int calculateindex(int x , int y)
{
  return (80*x)+y; 
}

void printPath(int dis[1680] ,Node **head ,  point *source)
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

void FindShortestPath( point base[21][80],  point *source, int dis[1680])
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

void printWallPath(int dis[1680] , point *source)
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



void FindShortestPathWithWall( point base[21][80],  point *source , int dis[1680])
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
