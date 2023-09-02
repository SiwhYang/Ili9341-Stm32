#ifndef __LIST_H__
#define __LIST_H__
#include "stm32f30x.h"
#include "STDLIB.H" // for the using of malloc

typedef struct Node
{
	u16 data;
	struct Node *nextnode;
}Node, *Nodeptr;

void Linkedlist_init();
void Push_back(u16 a);
void FreeList(Node* first);


#endif
