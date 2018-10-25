# ifndef PQUEUE_H
# define PQUEUE_H

#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdio.h>

class Monster
{
public:
  int x;
  int y;
  int speed;
  int s;
  char type;
};

class Node
{
public:
  int index;

   Node* next;
};

Node* newNode(int index);

void insert(Node **head, int index, int dis[1680]);

int pop(Node **head);

bool isEmpty(Node **head);

#endif