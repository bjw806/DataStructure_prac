#include <stdio.h>
#include <stdlib.h>
#include "ListGraph.h"

// ���� �׷����� �����ϴ� ����, operations to generate a empty graph
Graph* createGraph(int type) {
	int i;
	Graph* G = (Graph*)malloc(sizeof(Graph));	
	G->n = 0;
	G->type = type;
	for(i=0; i<MAX_SIZE; i++) {
		G->adjList_H[i] = NULL;
	}
	return G;
}

// �׷����� �������� �˻�, check if the graph is empth
int isEmpty(Graph* G) {
	return G->n == 0;
}

// �׷��� G�� ���� v�� ����, insert vertex v into graph G
void insertVertex(Graph* G, int v) {
	if((G->n)+1 > MAX_SIZE) {
		printf("[ERROR] �׷��� ������ ���� �ʰ�\n");	// [ERROR] Graph vertex exceeded
		return;
	}
	G->n++;
}

// �׷��� G�� ����(u, v)�� ����, insert a edge(u, v) into graph G
void insertEdge(Graph* G, int u, int v) {
	// Fill your code
	graphNode* p;
	for (int i = 0; i < G->n; i++) {
		if (!G->adjList_H[u])
			break;
		else {
			p = G->adjList_H[u];
			while (p) {//������ �̹� ������
				if (p->vertex == v)
					return;
				p = p->link;
			}
		}
	}
	graphNode* GN1 = (graphNode*)malloc(sizeof(graphNode));
	//��ũ ����
	GN1->vertex = v;
	GN1->link = G->adjList_H[u];
	G->adjList_H[u] = GN1;

	GN1 = (graphNode*)malloc(sizeof(graphNode));
	if (!G->type) {//Undirect��
		GN1->link = G->adjList_H[v];
		GN1->vertex = u;
		G->adjList_H[v] = GN1;
	}
}

// �׷��� G�� ���� v�� �����ϰ� ����� ��� ���� ����, delete vertex v to graph G and delete all connected edges
void deleteVertex(Graph* G, int v) {
	// Fill your code
	graphNode* p;//��
	graphNode* q;//��

	for (int i = 0; i < G->n; i++) {
		if (G->adjList_H[i] == NULL)//Ż��
			break;
		p = G->adjList_H[i];//��
		q = p->link;//��
		if (i == 2) {//�ش� ������ ���� ��� ����
			G->adjList_H[i] = NULL;
		}

		if (p->vertex == v) {//ù��°�ϰ��
			p->vertex = NULL;
			G->adjList_H[i] = p->link;
		}
		while (q) {//2��° ����
			if (q->vertex == v) {
				q->vertex = NULL;
				p->link = q->link;
			}
			p = q;
			q = q->link;//next
		}
	}
}

// �׷��� G�� ���� (u, v)�� ����, delete the edge(u, v) to graph G
void deleteEdge(Graph* G, int u, int v) {
	// Fill your code
	graphNode* p;
	graphNode* q;

	for (int i = 0; i < G->n; i++) {
		if (G->adjList_H[i] == NULL)//Ż��
			break;
		p = G->adjList_H[i];
		q = p->link;
		if (i == u) {//u�ϰ��
			
			if (p->vertex == v) {//ù��°�ϰ��
				p->vertex = NULL;
				G->adjList_H[i] = p->link;
			}
			while (q) {//2��° ����
				if (q->vertex == v) {
					q->vertex = NULL;
					p->link = q->link;
				}
				p = q;
				q = q->link;//next
			}
		}

		if (i == v) {//�ݴ�
			if (p->vertex == u) {//ù��°�ϰ��
				p->vertex = NULL;
				G->adjList_H[i] = p->link;
			}
			while (q) {//2��° ����
				if (q->vertex == u) {
					q->vertex = NULL;
					p->link = q->link;
				}
				p = q;
				q = q->link;//next
			}
		}

	}
}

// �׷��� G�� ���ҽ� ����, unresource graph G
void destroyGraph(Graph* G) {
	int i;
	for(i=0; i<G->n; i++) {
		if(G->adjList_H[i] != NULL)
			free(G->adjList_H[i]);
	}
	free(G);
}

// �׷��� G�� ���� ����Ʈ ���� ���, display adjacent list information for graph G
void displayGraph(Graph* G) {
	int i;
	graphNode* p;
	for(i=0; i<G->n; i++) {
		printf("���� %d�� ��������Ʈ", i);	// Adjacent list of vertex %d
		p = G->adjList_H[i];
		while(p) {
			printf(" -> %d ", p->vertex);
			p = p->link;
		}			
		printf("\n");
	}
}

