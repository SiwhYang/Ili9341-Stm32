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
 

Node_8* current_8, * first_8, * previous_8;


void Push_back_8(u8 a) 
{                           
	Node_8* newnode_8 = (Node_8*)malloc(sizeof(Node_8));
	newnode_8->data = a;
	newnode_8->nextnode_8 = NULL;
	if ((first_8->data == NULL)|(first_8 == NULL)) {
		first_8 = newnode_8;
	}
	else {
		Node_8* current_8 = first_8;
		while (current_8->nextnode_8 != NULL) {
			current_8 = current_8->nextnode_8;
		}
		current_8->nextnode_8 = newnode_8;
	}
}

void FreeList_8(Node_8* first_8) 
{                     
	Node_8* current_8, * tmp_8;
	current_8 = first_8->nextnode_8; // this line will keep first node safe
	while (current_8 != NULL) {
		tmp_8 = current_8;
		current_8 = current_8->nextnode_8;
		free(tmp_8);
	}
	first_8->nextnode_8 = NULL; 
	first_8->data = NULL;// this line will keep first node safe
}
 
