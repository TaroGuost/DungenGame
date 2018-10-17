#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>

void TestPrint(WINDOW **temp, char c)
{
  int i ,j;
  for(i = 0 ; i < 100; i ++)
    {
      for(j = 0 ; j < 100;j++)
	{
	  if(i==0 || j==0)
	    {
	      mvwprintw(*temp,i,j, "%c" , c);
	      refresh();
	    }
	  else
	    {
	      mvwprintw(*temp,i,j, "%c" , ' ');
	      refresh();
	    }
	}
    }
}

void p(WINDOW** temp)
{
  int i,j;
  for(i = 0 ; i < 10;i++)
    {
      for(j = 0 ; j< 10 ; j ++)
	{
	  mvwprintw(*temp, i,j,"%c",'^');
	}
    }
  
}

void AWindow()
{
  WINDOW *temp;
  int n = 0;
  temp = newwin(20,20,20,20);
  
  while(n != 1)
    {
      int t = wgetch(temp);
      p(&temp);
      switch(t)
	{
	case 'w':	  
	  break;
	case 'q':
	  n = 1;
	  break;
	}
    }

  clrtoeol();
  refresh();
  // delwin(temp);
  endwin();
  
}

int main()
{

  int ts = 123;
  char c = '.';
 

  initscr();
  noecho();
  cbreak();
  WINDOW *game;
  game = newwin(100,100,0,0);

  keypad(game,true);
  int temp = 0;
  //int ch;

  while(1)
    {

      //      TestPrint();
      TestPrint(&game,c);
     int  ch = wgetch(game);
      
      
      switch(ch)
	{
	case KEY_DOWN:
	  c = '%';
	  refresh();
	  break;
	case KEY_LEFT:
	  AWindow();
	  break;
	case 'd':
	  temp =1;
	  endwin();
	  break;
	}

      if(temp ==1){break;}
    }
        clrtoeol();
	refresh();
	endwin();

	return 0;
	

      
    }
