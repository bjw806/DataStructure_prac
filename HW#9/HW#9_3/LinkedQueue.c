#include <stdio.h>
#include <stdlib.h>
#include "LinkedQueue.h"

// 공백큐 생성, create s empty queue
Queue* createQueue() {
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// 큐가 공백상태인지 확인하는 연산, operations to determine if a queue is empty	
int isEmptyQueue(Queue* Q) {
	// Fill your code
	return Q->front == NULL;
}	

// 큐의 rear에 요소를 추가하는 연산, operations that add elements to the rear of a queue
void enqueue(Queue* Q, element x) {
	// Fill your code
	queueNode* p = (queueNode*)malloc(sizeof(queueNode));
	p->data = x;
	p->link = NULL;
	if (isEmptyQueue(Q))//비어잇으면 맨앞에
		Q->front = p;
	else
		Q->rear->link = p;
	Q->rear = p;
}	

// 큐에서 가장 먼저 저장된 요소 삭제 및 반환하는 연산, operations that delete and return the first stored element in a queue
element dequeue(Queue* Q) {
	// Fill your code
	queueNode* p = (queueNode*)malloc(sizeof(queueNode));
	element e;
	if (isEmptyQueue(Q))
		return ERROR;
	else {//디큐
		p = Q->front;
		e = p->data;
		Q->front = p->link;
		free(p);
		if (Q->front == NULL)//둘다 널로
			Q->rear = NULL;
		return e;
	}
}

// 큐 비우기, empth queue		
void clearQueue(Queue* Q) {
	queueNode* p;
	while(Q->front) {
		p = Q->front;
		Q->front = Q->front->link;
		free(p);
		p = NULL;
	}
}			

