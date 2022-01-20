#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"

// ���齺�� ����, create a empty stack
Stack* create() {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S->top = -1;
	return S;
}

// ������ ��ȭ�������� Ȯ���ϴ� ����, operations to determine if the stack is full
int isFull(Stack* S) {
	return S->top == MAX_SIZE - 1;//top�� max-1(99)�� ������ �� ����
}

// ������ ����������� Ȯ���ϴ� ����, operations to determine if the stack is empty			
int isEmpty(Stack* S) {
	return S->top == -1;//top�� -1�̸� ����
}

// ������ top�� ��Ҹ� �߰��ϴ� ����, operations to add elements to the top of a stack
void push(Stack* S, element x) {
	if (isFull(S)) {//�� ���� �ʾ�����
		printf("[ERROR] Stack is FULL!!\n");
		return;
	}
	else {//top+1, ������������ �Ѿ
		S->top += 1;
		S->stack[S->top] = x;
	}
}

// ���ÿ��� �������� ����� ��� ���� �� ��ȯ�ϴ� ����, operations that delete and return the last stored element in the stack	
element pop(Stack* S) {
	if (isEmpty(S)) {//����ٸ�
		printf("[ERROR] Stack is EMPTY!!\n");
		return ERROR;
	}
	else {//top-1, e����
		element e = S->stack[S->top];
		S->top -= 1;
		return e;
	}
}

// ���ÿ��� �������� ����� ��Ҹ� ��ȯ�ϴ� ����, operations that return the last stored element in the stack
element peek(Stack* S) {
	if (isEmpty(S)) {//����ٸ�
		printf("[ERROR] Stack is EMPTY!!\n");
		return ERROR;
	}
	else {//top ��ȯ
		return S->stack[S->top];
	}
}

// ������ ��� ��� ���, display all elements in the stack
void displayStack(Stack* S) {
	int i;
	printf("STACK [ "); 
	for(i=0; i<=S->top; i++)
		printf("%d ", S->stack[i]);
	printf(" ]\ttop: %d\n", S->top);
}

// ���� ����, empty stack
void clear(Stack* S) {
	while (S->top != -1) {//top�� -1�϶�����
		pop(S);//����
	}
}				

