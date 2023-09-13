#ifndef __LIST_H__
#define __LIST_H__
#include "stm32f30x.h"
#include "STDLIB.H" // for the using of malloc

typedef struct Node
{
	u16 data;
	struct Node *nextnode;
}Node, *Nodeptr;

void Push_back(u16 a);
void FreeList(Node* first);


typedef struct Node_8
{
	u8 data;
	struct Node_8 *nextnode_8;
}Node_8, *Nodeptr_8;

void Push_back_8(u8 a);
void FreeList_8(Node_8* first_8);


#endif
