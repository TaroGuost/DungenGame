#include "monster.h"

void dices :: setup(vector<string> s )
{
  stringstream geek(s.at(0));
  geek >>base;
  vector<string> temp = Split(s.at(1) , 'd');
  stringstream gee(temp.at(1));
  gee >>side;
  stringstream ge(temp.at(0));
  ge >>Amount;
}

int dices :: Roll()
{
  int temp[Amount];
  int total = 0;
  
  for(int i = 0 ; i < Amount ; i++)
    {
      temp[i] = (rand()%side)+1;
      total += temp[i];
    }

  return base + total;
  
}

string dices :: toString()
{
  string temp;

  temp = to_string(base) + "+" + to_string(Amount) + "d" + to_string(side);

  return temp;
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

void Monster ::setType()
{
  long int bin =0, hex=0, i = 1 , temp=0;
  
  for(int i = 0 ; i < 9 ; i ++)
    {
      if(a[i]<=0)
	continue;
      else
	bin+= a[i];
     }
  
  while(bin != 0)
    {
      temp = bin%10;
      hex += temp*i;
      i = i*2;
      bin = bin/10;
    }

  type = hex;
}

string Monster :: displayAbil()
{
  string temp = "";

  for(int i = 0 ; i < 9 ; i++)
    {
      if(a[i] == NONE)
	continue;
      else if(a[i] == SMART)
	temp += "SMART ";
      else if(a[i] == TUNNEL)
	temp += "TUNNEL ";
      else if(a[i] == ERRATIC)
	temp += "ERRATIC ";
      else if(a[i] == TELE)
	temp += "TELE ";
      else if(a[i] == PASS)
	temp += "PASS ";
      else if(a[i] == PICKUP)
	temp += "PICKUP ";
      else if(a[i] == DESTORY)
	temp += "DESTORY ";
      else if(a[i] == UNIQ)
	temp += "UNIQ ";
      else if(a[i] == BOSS)
	temp += "BOSS ";
    }

  return temp;

}

void tempc(Monster *M , int size)
{
  

  for(int i = 0 ; i < size ; i ++)
    {
      cout << "Name " << (M+i)->name << endl;
      cout << "SYMB " << (M+i)->Sybol << endl;
      cout << "COLOR " << (M+i)->Color <<endl;
      cout << "DESC :" << (M+i)->Desc;
      cout << "Speed " << (M+i)->speed.toString() << endl;
      cout << "Damage " << (M+i)->Damage.toString() << endl;
      cout << "HP " << (M+i)->HP.toString() <<endl;
      cout << "Ability: " << (*(M+i)).displayAbil() << endl;
      cout << "RYYP: " << (M+i)->RRTY << endl;
    }
  
}

void GMonster( room *rooms ,  Monster *Monsters , int size ,  point base[21][80] , int mc)
{
  int MonsterCount = 0;

  while(MonsterCount < mc)
    {
      int random = (rand()%size);
      if(!IfPC(rooms+random, base))
	{
	  (Monsters+MonsterCount)->x = ((rooms+random)->x)+(rand()%(rooms+random)->rl);
	  (Monsters+MonsterCount)->y = ((rooms+random)->y)+(rand()%(rooms+random)->rw);
	  (Monsters+MonsterCount)->type = Mtype(2,2,2,2);
	  (Monsters+MonsterCount)->speed.base = (rand()%16)+5;
	  (Monsters+MonsterCount)->s = 0;
	  (Monsters+MonsterCount)->Dead = false;
	  MonsterCount++;
	}
    }
  

}

vector<string> Split(string s , char c)
{
  vector<string> result;
  string temp;
  istringstream tokenStream(s);
  while(getline(tokenStream,temp,c))
    {
      result.push_back(temp);
    }

  return result;
}

void setCount(string s , int *count)
{
  if(s.compare("BEGIN")==0)
    *count = 0;
  else if(s.compare("NAME") == 0)
    *count = 1;
  else if(s.compare("SYMB") == 0)
    *count = 2;
  else if(s.compare("COLOR") == 0)
    *count = 3;
  else if(s.compare("DESC") == 0)
    *count = 4;
  else if(s.compare("SPEED") == 0)
    *count = 5;
  else if(s.compare("DAM") == 0)
    *count = 6;
  else if(s.compare("HP") == 0)
    *count = 7;
  else if(s.compare("ABIL") == 0)
    *count = 8;
  else if(s.compare("RRTY") == 0)
    *count = 9;
  else if(s.compare("END") == 0)
    *count = -1;
  
}

int ImportMonster(Monster **M , string Filename)
{
  ifstream File;
  File.open(Filename);

  int count = -1;
  int size =0;
  string x;
  vector<string> content;
  vector<string> s;
  dices di;

  
  while(getline(File,x))
    {
      
      if(count != 4 && x != "")
	{
	  content = Split(x , ' ');
	  setCount(content.at(0),&count);
	}
      else
	{
	  if(x.compare(".")== 0)
	    {
	      count = -1;
	      continue;
	    }
	
	}
      
      if(count >4 && count < 8)
	{
	  int side , amount;
	  s = Split(content.at(1) , '+');
	  di.setup(s);
	}
      
      switch(count)
	{
	case -1:
	  break;
	case 0:
	  size++;
	  if(size != 1)
	    *M = (Monster*)realloc(*M,size*sizeof(Monster));
	  break;
	case 1:
	  for(int i = 1 ; i < content.size() ; i++)
	    (*M+size-1)->name +=  content.at(i) + " ";
	  break;
	case 2:
	  (*M+size-1)->Sybol = content.at(1)[0];
	  break;
	case 3:
	   for(int i = 1 ; i < content.size() ; i++)
	     (*M+size-1)->Color +=  content.at(i) + " ";
	  break;
	case 4:
	  if(x.compare(".") != 0
	     && x.compare("DESC") != 0)
	    {
	      (*M+size-1)->Desc += x;
	      (*M+size-1)->Desc.push_back('\n');
	    }
	  break;
	case 5:
	  (*M+size-1)->speed = di;
	  break;
	case 6:
	  (*M+size-1)->Damage =di;
	  break;
	case 7:
	  (*M+size-1)->HP = di;
	  break;
	case 8:
	  for(int i = 1 ; i < content.size() ; i++)
	    {
	      if(content.at(i).compare("SMART") == 0)
		(*M+size-1)->a[i-1] = SMART;
	      else if(content.at(i).compare("TELE") ==0 )
		(*M+size-1)->a[i-1] = TELE;
	      else if(content.at(i).compare("TUNNEL") == 0)
		(*M+size-1)->a[i-1] = TUNNEL;
	      else if(content.at(i).compare("ERRATIC") == 0)
		(*M+size-1)->a[i-1] = ERRATIC;
	      else if(content.at(i).compare("PICKUP") == 0)
		(*M+size-1)->a[i-1] = PICKUP;
	      else if(content.at(i).compare("PASS") == 0)
		(*M+size-1)->a[i-1] = PASS;
	      else if(content.at(i).compare("DESTORY") == 0)
		(*M+size-1)->a[i-1] = DESTORY;
	      else if(content.at(i).compare("UNIQ") == 0)
		(*M+size-1)->a[i-1] = UNIQ;
	      else if(content.at(i).compare("BOSS") == 0)
		(*M+size-1)->a[i-1] = BOSS;
	    }
	  
	  (*(*M+size-1)).setType();
	  break;
	case 9:
	  stringstream g(content.at(1));
	  g >> (*M+size-1)->RRTY;
	  break;
	  
	}
      
    }

  return size;
  
}

bool IfPC( room *r ,  point base[21][80])
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


void addPlayer( Player *p  , int px , int py)
{
  
  p->x = px;
  p->y = py;
  p->type = '@';
  p->speed.base = 10;
  p->s = 0;
  p->Dead = false;
}
