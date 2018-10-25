#include "pQueue.h"


Node* newNode(int index)
{
  Node *temp = (Node*)malloc(sizeof(Node));

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
