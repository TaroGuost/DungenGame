#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *test(const char *s);
void swap(int *i , int *j);
void freep(void *p);

int main()
{
  char *s = "llllssss";
  char *temp = test(s);
  int i = 0 ;
  int j = 2;
  int *f = (int*)malloc(sizeof(int));
  freep(f);
  char *tt ""\"fench"\"";
  
  swap(&i,&j);

  printf("i : %d , J: %d \n",i,j);
  
  
  printf("%s\n", tt);
}
void swap(int * i , int *j)
{
  int temp = *i;
  *i = *j;
  *j = temp;
}

char* test(const char *s)
{
  char *temp;
  temp = (char*)malloc(8);
  int i;
  for(i = 0 ; i < 8 ; i ++)
    {
      *(temp+i) = *(s+i);
    }

  return temp;
}

void freep(void *p)
{
  free(p);
  p = NULL;
}
