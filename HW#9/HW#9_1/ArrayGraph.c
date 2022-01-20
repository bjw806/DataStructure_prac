#include <stdio.h>
#include <stdlib.h>
#include "ArrayGraph.h"

// 공백 그래프를 생성하는 연산, operations to generate a empty graph
Graph* createGraph(int type) {
	int i, j;
	Graph* G = (Graph*)malloc(sizeof(Graph));	
	G->n = 0;
	G->type = type;
	for(i=0; i<MAX_SIZE; i++) {
		for(j=0; j<MAX_SIZE; j++)
			G->adjMatrix[i][j] = 0;
	}
	return G;
}

// 그래프가 공백인지 검사, check if the graph is empty
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
	G->adjMatrix[u][v] = 1;//공통부분
	if (!G->type)//타입이 UNDirect면
		G->adjMatrix[v][u] = 1;
}

// 그래프 G에 정점 v를 삭제하고 연결된 모든 간선 삭제, delete vertex v to graph G and delete all connected edges
void deleteVertex(Graph* G, int v) {
	// Fill your code
	for (int i = 0; i < G->n; i++) {//v와 연결된것 = 0
		G->adjMatrix[i][v] = 0;
		G->adjMatrix[v][i] = 0;
	}
}

// 그래프 G에 간선 (u, v)를 삭제, delete the edge(u, v) to graph G
void deleteEdge(Graph* G, int u, int v) {
	// Fill your code
	G->adjMatrix[u][v] = 0;//u,v 삭제
}

// 그래프 G의 리소스 해제, unresource graph G
void destroyGraph(Graph* G) {
	int i, j;
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++)
			G->adjMatrix[i][j] = 0;
	}
	G->n = 0;
}

// 그래프 G의 인접 행렬 정보 출력, display adjacent matrix information for graph G
void displayGraph(Graph* G) {
	int i, j;
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++)
			printf("%2d\t", G->adjMatrix[i][j]);
		printf("\n");
	}
}
