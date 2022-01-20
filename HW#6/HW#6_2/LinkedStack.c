#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"

// ���齺�� ����, create a empty stack
Stack* createStack() {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S->top = NULL;
	return S;
}

// ������ ��ȭ�������� Ȯ���ϴ� ����, operations to determine if the stack is full
int isFull(Stack* S) {
	return 0;
}

// ������ ����������� Ȯ���ϴ� ����, operations to determine if the stack is empty
int isEmpty(Stack* S) {
	return S->top == NULL;
}

// ������ top�� ��Ҹ� �߰��ϴ� ����, operations that add elements to top of stack
void push(Stack* S, element x) {
	stackNode* newNode = (stackNode*)malloc(sizeof(stackNode));
	newNode->data = x;
	newNode->link = S->top;
	S->top = newNode;
}

// ���ÿ��� �������� ����� ��� ���� �� ��ȯ�ϴ� ����, operations to delete and return the last stored element on the stack
element pop(Stack* S) {
	stackNode* temp; element e;
	if (isEmpty(S)) {
		//printf("[ERROR] Stack is EMPTY!!\n");
		return ERROR;
	}
	else {
		temp = S->top;
		e = temp->data;
		S->top = temp->link;
		free(temp);
		//printf("%d ����\n", e);
		return e;
	}
}

// ���ÿ��� �������� ����� ��Ҹ� ��ȯ�ϴ� ����, operations that return the last stored element in the stack
element peek(Stack* S) {
	element e;
	if (isEmpty(S)) {
		//printf("[ERROR] Stack is EMPTY!!\n");
		return ERROR;
	}
	else
		return S->top->data;
}

// ������ ��� ��� ���, output all elements in the stack
void displayStack(Stack* S) {
	stackNode* p = S->top;
	printf("STACK [ ");
	while(p) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf(" ]\n");
}

// ���� ����, empth stack
void clear(Stack* S) {
	stackNode* p;
	while(S->top) {
		p = S->top;
		S->top = S->top->link;
		free(p);
		p = NULL;
	}
}