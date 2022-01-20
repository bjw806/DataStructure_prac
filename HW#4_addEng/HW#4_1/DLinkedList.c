#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

linkedList* initList() {
	linkedList* L;
	L = (linkedList*)malloc(sizeof(linkedList));
	L->head = NULL;
	L->length = 0;
	return L;
}

int getLength(linkedList* L) {
	return L->length;
}


void insert(linkedList* L, listNode* pre, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	
	// Fill your code
	

}

void insertFirst(linkedList* L, element x) {
	listNode* newNode;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;

	// Fill your code


}

void insertLast(linkedList* L, element x) {
	listNode *newNode, *temp;
	newNode = (listNode*)malloc(sizeof(listNode));
	newNode->data = x;
	
	// Fill your code


}

int deleteNode(linkedList* L, listNode* p) {

	// Fill your code


}

listNode* search(linkedList* L, element x) {
	listNode* temp = L->head;
	
	while(temp != NULL) {
		if(temp->data == x)
			return temp;
		else
			temp = temp->rlink;
	}
	return temp;
}

void displayList(linkedList* L) {
	listNode* p;
	printf("L=(");
	p = L->head;
	while(p != NULL) {
		printf("%d", p->data);
		p = p->rlink;
		if(p != NULL) printf(", ");
	}
	printf(")\n");
}

void clear(linkedList* L) {
	listNode* p;
	while(L->head != NULL) {
		p = L->head;
		L->head = L->head->rlink;
		free(p);
		p = NULL;
	}
}

