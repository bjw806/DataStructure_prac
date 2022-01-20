#include <stdio.h>
#include <stdlib.h>
#include "ListGraph.h"

// 공백 그래프를 생성하는 연산, operations to generate a empty graph
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

// 그래프가 공백인지 검사, check if the graph is empth
int isEmpty(Graph* G) {
	return G->n == 0;
}

// 그래프 G에 정점 v를 삽입, insert vertex v into graph G
void insertVertex(Graph* G, int v) {
	if((G->n)+1 > MAX_SIZE) {
		printf("[ERROR] 그래프 정점의 개수 초과\n");	// [ERROR] Graph vertex exceeded
		return;
	}
	G->n++;
}

// 그래프 G에 간선(u, v)를 삽입, insert a edge(u, v) into graph G
void insertEdge(Graph* G, int u, int v) {
	// Fill your code
	graphNode* p;
	for (int i = 0; i < G->n; i++) {
		if (!G->adjList_H[u])
			break;
		else {
			p = G->adjList_H[u];
			while (p) {//같은게 이미 있으면
				if (p->vertex == v)
					return;
				p = p->link;
			}
		}
	}
	graphNode* GN1 = (graphNode*)malloc(sizeof(graphNode));
	//링크 연결
	GN1->vertex = v;
	GN1->link = G->adjList_H[u];
	G->adjList_H[u] = GN1;

	GN1 = (graphNode*)malloc(sizeof(graphNode));
	if (!G->type) {//Undirect면
		GN1->link = G->adjList_H[v];
		GN1->vertex = u;
		G->adjList_H[v] = GN1;
	}
}

// 그래프 G에 정점 v를 삭제하고 연결된 모든 간선 삭제, delete vertex v to graph G and delete all connected edges
void deleteVertex(Graph* G, int v) {
	// Fill your code
	graphNode* p;//뒤
	graphNode* q;//앞

	for (int i = 0; i < G->n; i++) {
		if (G->adjList_H[i] == NULL)//탈출
			break;
		p = G->adjList_H[i];//뒤
		q = p->link;//앞
		if (i == 2) {//해당 정점의 간선 모두 삭제
			G->adjList_H[i] = NULL;
		}

		if (p->vertex == v) {//첫번째일경우
			p->vertex = NULL;
			G->adjList_H[i] = p->link;
		}
		while (q) {//2번째 부터
			if (q->vertex == v) {
				q->vertex = NULL;
				p->link = q->link;
			}
			p = q;
			q = q->link;//next
		}
	}
}

// 그래프 G에 간선 (u, v)를 삭제, delete the edge(u, v) to graph G
void deleteEdge(Graph* G, int u, int v) {
	// Fill your code
	graphNode* p;
	graphNode* q;

	for (int i = 0; i < G->n; i++) {
		if (G->adjList_H[i] == NULL)//탈출
			break;
		p = G->adjList_H[i];
		q = p->link;
		if (i == u) {//u일경우
			
			if (p->vertex == v) {//첫번째일경우
				p->vertex = NULL;
				G->adjList_H[i] = p->link;
			}
			while (q) {//2번째 부터
				if (q->vertex == v) {
					q->vertex = NULL;
					p->link = q->link;
				}
				p = q;
				q = q->link;//next
			}
		}

		if (i == v) {//반대
			if (p->vertex == u) {//첫번째일경우
				p->vertex = NULL;
				G->adjList_H[i] = p->link;
			}
			while (q) {//2번째 부터
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

// 그래프 G의 리소스 해제, unresource graph G
void destroyGraph(Graph* G) {
	int i;
	for(i=0; i<G->n; i++) {
		if(G->adjList_H[i] != NULL)
			free(G->adjList_H[i]);
	}
	free(G);
}

// 그래프 G의 인접 리스트 정보 출력, display adjacent list information for graph G
void displayGraph(Graph* G) {
	int i;
	graphNode* p;
	for(i=0; i<G->n; i++) {
		printf("정점 %d의 인접리스트", i);	// Adjacent list of vertex %d
		p = G->adjList_H[i];
		while(p) {
			printf(" -> %d ", p->vertex);
			p = p->link;
		}			
		printf("\n");
	}
}

