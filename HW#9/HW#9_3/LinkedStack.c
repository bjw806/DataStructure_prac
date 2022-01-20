#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"

// ���齺�� ����, create a empty stack
Stack* create() {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S->top = NULL;
	return S;
}


// ������ ����������� Ȯ���ϴ� ����, operations to determine if the stack is empty		
int isEmpty(Stack* S) {
	// Fill your code
	return S->top == NULL;
}

// ������ top�� ��Ҹ� �߰��ϴ� ����, operations that add elements to top of stack		
void push(Stack* S, element x) {
	// Fill your code
	stackNode* p= (stackNode*)malloc(sizeof(stackNode));
	//���� �߰�
	p->data = x;
	p->link = S->top;
	S->top = p;
}

// ���ÿ��� �������� ����� ��� ���� �� ��ȯ�ϴ� ����, operations to delete and return the last stored element on the stack
element pop(Stack* S) {
	// Fill your code
	stackNode* p;
	element e;
	if (isEmpty(S)) {
		printf("[ERROR] Stack is EMPTY!\n");
		return ERROR;
	}
	else {//pop
		p = S->top;
		e = p->data;
		S->top = p->link;
		free(p);
		return e;
	}
}

// ���� ����, empty stack
void clear(Stack* S) {
	stackNode* p;
	while(S->top) {
		p = S->top;
		S->top = S->top->link;
		free(p);
		p = NULL;
	}
}