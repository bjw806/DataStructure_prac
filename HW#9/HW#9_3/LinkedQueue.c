#include <stdio.h>
#include <stdlib.h>
#include "LinkedQueue.h"

// ����ť ����, create s empty queue
Queue* createQueue() {
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// ť�� ����������� Ȯ���ϴ� ����, operations to determine if a queue is empty	
int isEmptyQueue(Queue* Q) {
	// Fill your code
	return Q->front == NULL;
}	

// ť�� rear�� ��Ҹ� �߰��ϴ� ����, operations that add elements to the rear of a queue
void enqueue(Queue* Q, element x) {
	// Fill your code
	queueNode* p = (queueNode*)malloc(sizeof(queueNode));
	p->data = x;
	p->link = NULL;
	if (isEmptyQueue(Q))//��������� �Ǿտ�
		Q->front = p;
	else
		Q->rear->link = p;
	Q->rear = p;
}	

// ť���� ���� ���� ����� ��� ���� �� ��ȯ�ϴ� ����, operations that delete and return the first stored element in a queue
element dequeue(Queue* Q) {
	// Fill your code
	queueNode* p = (queueNode*)malloc(sizeof(queueNode));
	element e;
	if (isEmptyQueue(Q))
		return ERROR;
	else {//��ť
		p = Q->front;
		e = p->data;
		Q->front = p->link;
		free(p);
		if (Q->front == NULL)//�Ѵ� �η�
			Q->rear = NULL;
		return e;
	}
}

// ť ����, empth queue		
void clearQueue(Queue* Q) {
	queueNode* p;
	while(Q->front) {
		p = Q->front;
		Q->front = Q->front->link;
		free(p);
		p = NULL;
	}
}			

