#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Heap.h"

// ���� �� ����
Heap* createHeap() {
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->numOfData = 0;
	return h;
}	

// ���� �������� �˻�		
int isEmpty(Heap* h) {
	return h->numOfData == 0 ? TRUE : FALSE;
}	

// ���� ������ ��ġ�� ���� x ����
void insertHeap(Heap* h, HData x) {
	if(h->numOfData == MAX_SIZE) {
		printf("ERROR: Heap is FULL!!\n");
		return;
	}
	
	// Fill your code 
	int idx = h->numOfData + 1;//�ڽ�2
	int idxx = floor(idx/2);//�θ�1
	while (idx != 1){
		if (x < h->heap[idxx]) {//�ڱ� �θ𺸴� ������
			h->heap[idx] = h->heap[idxx];//�θ�� �ٲ�
			idx = floor(idx / 2);
			idxx = floor(idx / 2);
		}
		else 
			break;
	} 
	h->heap[idx] = x;
	h->numOfData++;
}

// ������ Ű ���� ���� ���� ���� �����ϰ� ��ȯ
HData deleteHeap(Heap* h) {
	if(isEmpty(h)) {
		printf("ERROR: Heap is EMPTY!!\n");
		return 0;
	}
	
	HData item = h->heap[1];
	HData lastVal = h->heap[h->numOfData];
	int parentIdx = 1;
	int childIdx = 2;
	
	// Fill your code
	while (childIdx <= h->numOfData) {
		if ((childIdx < h->numOfData) && (h->heap[childIdx] > h->heap[childIdx + 1]))
			childIdx++;//����<������ �ڽ��̸�
		if (lastVal >= h->heap[childIdx]){
			h->heap[parentIdx] = h->heap[childIdx];
			parentIdx = childIdx;
			childIdx = childIdx * 2;
		}
		else
			break; 
	}
	h->heap[parentIdx] = lastVal;
	h->numOfData--;
	return item;
}			

// �θ� ����� �ε��� �� ��ȯ
int getParentIdx(int idx) {
	return idx/2;
}	

// ���� �ڽ� ����� �ε��� �� ��ȯ
int getLChildIdx(int idx) {
	return idx*2;
}

// ������ �ڽ� ����� �ε��� �� ��ȯ	
int getRChildIdx(int idx) {
	return idx*2+1;
}

void displayHeap(Heap* h) {
	int i;
	for(i=1; i<=h->numOfData; i++)
		printf("%d %d\n", i, h->heap[i]);
	printf("\n");
}	