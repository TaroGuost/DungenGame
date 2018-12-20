#include"print.h"

void PrintMonster(WINDOW **game , Monster *ms , int mc ,  point base[21][80] , int px , int py , int stair , int Dstair,bool check , vector<objects> ob , Player *p)
{
  int i,j;

  //werase(*game);
  
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
	    }

	   if(i == Dstair/80 && j == Dstair%80)
	    {
	       base[i][j].value ='>';	     
	    }

	       FakeValue(px,py,base);
	   

	  int temp = isSamePlace(ms,mc,i,j);
	   if(!check)
	    {
	      if(temp  != -1 && IsAround(i,j,px,py) )
		{
		  int n = (*(ms+temp)).usefulColor();

		  init_pair(n, n, COLOR_BLACK);
		  wattron(*game,COLOR_PAIR(n));
		  mvwprintw(*game,i,j,"%c", (ms+temp)->Sybol);
		  wattroff(*game,COLOR_PAIR(n));
		}
	      else
		{		  
		  if(base[i][j].ob != '.')
		    {
		      int n = ob.at(base[i][j].position).SelectColor();
		      init_pair(n, n, COLOR_BLACK);
		      wattron(*game,COLOR_PAIR(n));
		      mvwprintw(*game,i,j,"%c" , base[i][j].fake);
		      wattroff(*game,COLOR_PAIR(n));
		    }
		  else
		    mvwprintw(*game,i,j,"%c" , base[i][j].fake);
	 
		}
	    }
	  else
	    {
	      if(temp  != -1)
		{
		  int n = (*(ms+temp)).usefulColor();

		  init_pair(n, n, COLOR_BLACK);
		  wattron(*game,COLOR_PAIR(n));
		  mvwprintw(*game,i,j,"%c", (ms+temp)->Sybol);
		  wattroff(*game,COLOR_PAIR(n));
		}
	      else
		{
		  if(base[i][j].ob != '.')
		    {
		      int n = ob.at(base[i][j].position).SelectColor();
		      init_pair(n, n, COLOR_BLACK);
		      wattron(*game,COLOR_PAIR(n));
		      mvwprintw(*game,i,j,"%c" , base[i][j].ob);
		      wattroff(*game,COLOR_PAIR(n));
		    }
		  else
		    mvwprintw(*game,i,j,"%c" , base[i][j].value);
		  
		  refresh();
		}
	    }
	  
	  if(i == px && j == py)
	    {
	      mvwprintw(*game,i,j,"%c" , '@');
	    }
  
	}
    }

  mvwprintw(*game , 22 , 3 , "                        ");
  mvwprintw(*game, 22 , 3 , "Player HP: %d" , p->HP);
  
}


void PrintLose(Charactor *Monsters)
{
  int i, j;
  for(i = 0 ; i < 21 ; i ++)
    {
      for(j = 0 ; j < 80 ; j ++)
	{
	  if(i == 21/2 && j == 80/2)
	    {
	      printf("YOU DEAD!!!!   ");
	      printf("%c KILLED YOU", ((Monster*)Monsters)->Sybol);
	    }
	  else
	    {
	      printf(" ");
	    }
	}
      printf("\n");
    }


}



void PrintList(WINDOW **list,int mc, int px ,int py, Monster *M,int n)
{
  int i;

  int x = 5;

  if(x > mc)
    x =mc;
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattron(*list, COLOR_PAIR(1));
  for(i = 0  ; i<x ; i++)
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

   wattroff(*list,COLOR_PAIR(1));

}

void MonsterList( Monster *M, int mc , int px , int py)
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
	case 27:
	  i =1;
	  break;
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



void PCteleport( WINDOW **game, point base[21][80] , Player* M , bool fog)
{

  int ch;
  int x =10;
  int y = 40;
  char temp = base[x][y].fake;
  bool check = false;
    
  
  mvwprintw(*game, x , y ,"%c" , '*' );

  while(!check)
    {
      ch = wgetch(*game);
      
      switch(ch)
	{
	case KEY_UP:
	  if(x-1 > 0)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      x--;
	      if(fog)
		temp = base[x][y].fake;
	      else
		temp = base[x][y].value;
	      mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_DOWN:
	  if(x+1 <=19)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      x++;
	      if(fog)
		temp = base[x][y].fake;
	      else
		temp = base[x][y].value;
		  mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_LEFT:
	  if(y-1 >0)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      y--;
	      if(fog)
		temp = base[x][y].fake;
	      else
		temp = base[x][y].value;
		  mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_RIGHT:
	  if(y+1 <=78)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      y++;
	      if(fog)
		temp = base[x][y].fake;
	      else
		temp = base[x][y].value;
	      mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case 'g':
	  check = true;
	  break;
	case 'r':
	  mvwprintw(*game, x , y , "%c" , temp);
	  x = (rand()%19)+1;
	  y = (rand()%78)+1;
	  check = true;
	  break;
	}
      
    }

  M->x = x;
  M->y = y;

}

void printslot(WINDOW **list, Player *p , int highlight , vector<objects> *ob)
{
  for(int i = 0 ; i < (*ob).size(); i ++)
    {
      if(i == highlight)
	{
	  wattron(*list , A_REVERSE);
	  mvwprintw(*list , i+1 , 1,"Type:%s Name: %s" ,(*ob).at(i).type.c_str(), (*ob).at(i).name.c_str());
	  wattroff(*list , A_REVERSE);
	}
      else
	{
	  mvwprintw(*list , i+1 , 1,"Type:%s Name: %s" ,(*ob).at(i).type.c_str(), (*ob).at(i).name.c_str());
	}
    }
}

void printDesc(WINDOW **list , string temp)
{
   mvwprintw(*list , 0 , 0,"item name: %s" , temp.c_str());
}

void slotList(Player *p , point base[21][80] , vector<objects> *obj)
{
  bool show = false;
  int highlight = 0;
  bool check = false;
  WINDOW *slist;
  slist = newwin(13,60,8,20);
  keypad(slist,true);
  while(!check)
    {
      werase(slist);
      if(show == false)
	{
	  wborder(slist,'*','*','*','*','*','*','*','*');
	  printslot(&slist , p , highlight , &(p->slot));
	}
      else
	{
	  printDesc(&slist,p->slot.at(highlight).Desc);
	}
      int ch = wgetch(slist);
      switch(ch)
	{
	case 'e':
	  check = true;
	  break;
	case KEY_DOWN:
	  if(highlight < (p->slot.size()-1))
	    highlight++;
	  break;
	case KEY_UP:
	  if(highlight > 0)
	    highlight--;
	  break;
	case 'w':
	  if(p->slot.size()> 0)
	    {
	      p->puton(highlight);
	      highlight = 0;
	    }
	  break;
	case 'd':
	  if(p->slot.size() >0)
	    {
	      p->dropitem(highlight, base , obj);
	      highlight =0;
	    }
	  break;
	case 'x':
	  p->removeitem(highlight);
	  highlight = 0;
	  break;
	case 'I':
	  show = !show;
	  break;
	default:
	  break;
	}
    }

  wclrtoeol(slist);
  wrefresh(slist);
  delwin(slist);
  
}

void equiList(Player *p)
{
  int highlight = 0;
  bool check = false;
  WINDOW *slist;
  slist = newwin(13,60,8,20);
  keypad(slist,true);
  while(!check)
    {
      werase(slist);
      wborder(slist,'*','*','*','*','*','*','*','*');
      printslot(&slist , p , highlight , &(p->equi));
      int ch = wgetch(slist);
      switch(ch)
	{
	case 'e':
	  check = true;
	  break;
	case KEY_DOWN:
	  if(highlight < (p->equi.size()-1))
	    highlight++;
	  break;
	case KEY_UP:
	  if(highlight > 0)
	    highlight--;
	  break;
	case 't':
	  if(p->slot.size() < 10)
	    {
	      p->takeoff(highlight);
	      highlight = 0;
	    }
	  break;
	default:
	  break;
	}
    }

  wclrtoeol(slist);
  wrefresh(slist);
  delwin(slist);
  
}

void CheckMonster(WINDOW **game , Monster*Ori , point base[21][80] , int mc , bool fog)
{
  int ch;
  int x =10;
  int y = 40;
  char temp = base[x][y].fake;
  bool check = false;
    
  
  mvwprintw(*game, x , y ,"%c" , '*' );

  while(!check)
    {
      ch = wgetch(*game);
      
      switch(ch)
	{
	case KEY_UP:
	  if(x-1 > 0)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      x--;
	      if(fog)
		temp = base[x][y].fake;
	      else
		{
		  int index = isSamePlace(Ori,mc,x,y);
		  if(index != -1)
		    temp = (Ori+index)->Sybol;
		  else
		    temp = base[x][y].value;
		}
	      mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_DOWN:
	  if(x+1 <=19)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      x++;
	      if(fog)
		temp = base[x][y].fake;
	      else
		{
		  int index = isSamePlace(Ori,mc,x,y);
		  if(index != -1)
		    temp = (Ori+index)->Sybol;
		  else
		    temp = base[x][y].value;
		}
	      mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_LEFT:
	  if(y-1 >0)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      y--;
	      if(fog)
		temp = base[x][y].fake;
	      else
		{
		  int index = isSamePlace(Ori,mc,x,y);
		  if(index != -1)
		    temp = (Ori+index)->Sybol;
		  else
		    temp = base[x][y].value;
		}
	      mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case KEY_RIGHT:
	  if(y+1 <=78)
	    {
	      mvwprintw(*game, x , y , "%c" , temp);
	      y++;
	      if(fog)
		temp = base[x][y].fake;
	      else
		{
		  int index = isSamePlace(Ori,mc,x,y);
		  if(index != -1)
		    temp = (Ori+index)->Sybol;
		  else
		    temp = base[x][y].value;
		}
		  mvwprintw(*game, x , y, "%c" , '*');
	    }
	  break;
	case 'L':
	  check = true;
	  werase(*game);
	  break;
	case 't':
	  int n = isSamePlace(Ori,mc,x,y);
	  if(n != -1)
	    {
	      mvwprintw(*game, 20 , 0 , "Name : %s\nDesc : %s" ,(Ori+n)->name.c_str(),(Ori+n)->Desc.c_str() );
	      move(21,0);
	      clrtoeol();
	    }
	  break;
	}
      
    }
}
