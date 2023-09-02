#include "list.h"


// reference to --->> https://codimd.mcl.math.ncu.edu.tw/s/B1rd5-sM4   

Node* current, * first, * previous;




void Push_back(u16 a) 
{                           
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->data = a;
	newnode->nextnode = NULL;
	if ((first->data == NULL)|(first == NULL)) {
		first = newnode;
	}
	else {
		Node* current = first;
		while (current->nextnode != NULL) {
			current = current->nextnode;
		}
		current->nextnode = newnode;
	}
}

void FreeList(Node* first) 
{                     
	Node* current, * tmp;
	current = first->nextnode; // this line will keep first node safe
	while (current != NULL) {
		tmp = current;
		current = current->nextnode;
		free(tmp);
	}
	first->nextnode = NULL; 
	first->data = NULL;// this line will keep first node safe
}
 
/*
void PrintList(Node* first) {                   
	Node* node = first;
	if (first == NULL) {
		printf("List is empty!\n");
	}
	else {
		while (node != NULL) {
			printf("%d ", node->data);
			node = node->nextnode;
		}
		//printf("\n");
	}
}
*/


/*
void Linkedlist_init()
{	
	u16 num[] = { 0xFFFF };                
	int i;
	for (i = 0; i < 1; i++) {
		current = (Node*)malloc(sizeof(Node));
		if (i == 0) {
			first = current;
		}
		else {
			previous->nextnode = current;
		}
		current->data = num[i];
		current->nextnode = NULL;
		previous = current;
	}
	
	//FreeList(first);
}
*/
