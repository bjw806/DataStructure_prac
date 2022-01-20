#include <stdio.h>
#include <stdlib.h>
#include "ListGraph.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"

// 공백 그래프를 생성하는 연산, operations to generate a empty graph
Graph* createGraph(int type) {
	int i;
	Graph* G = (Graph*)malloc(sizeof(Graph));	
	G->n = 0;
	G->type = type;
	for(i=0; i<MAX_SIZE; i++) {
		G->adjList_H[i] = NULL;
		G->visited[i] = FALSE;
		G->pred[i] = -1;
	}
	return G;
}

// 그래프가 공백인지 검사, check if the graph is empty
int isEmptyGraph(Graph* G) {
	return G->n == 0;
}

// 그래프 G에 정점 v를 삽입, insert vertex v into graph G
void insertVertex(Graph* G, int v) {
	if((G->n)+1 > MAX_SIZE) {
		printf("[ERROR] 그래프 정점의 개수 초과\n");	// [ERROR] Exceeding the number of graph vertices
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
		printf("정점 %d의 인접리스트", i);	// Adjacent list with vertex %d
		p = G->adjList_H[i];
		while(p) {
			printf(" -> %d ", p->vertex);
			p = p->link;
		}			
		printf("\n");
	}
}

// visited[], pred[] 초기화, initialized visited[], pre[]
void initSearch(Graph* G) {
	int i;
	for(i=0; i<G->n; i++) {
		G->visited[i] = FALSE;
		G->pred[i] = -1;
	}
}

// 깊이 우선 탐색 iterative version, depth first search iterative version
void dfs_iter(Graph* G, int v) {
	// Fill your code 스택
	graphNode* w = (graphNode*)malloc(sizeof(graphNode));
	Stack* S = create();
	G->visited[v] = TRUE;
	push(S, v);
	printf("     %d", v);
	while (!isEmpty(S)) {
		v = pop(S);
		w = G->adjList_H[v];//w<-v의 인접정점
		while (w) {
			if (!G->visited[w->vertex]) {//w가 방문되지 않았으면
				push(S, v);
				G->visited[w->vertex] = TRUE;
				printf("     %d", w->vertex);
				v = w->vertex;
				w = G->adjList_H[v]->link;//w=v의 인접정점
			}
			else
				w = w->link;
		}
	}
}	

// 깊이 우선 탐색 recursive version, depth first search recursive version
void dfs_recur(Graph* G, int v)	{//재귀이용
	// Fill your code 스택
	printf("     %d", v);
	G->visited[v] = TRUE;
	graphNode* w;
	graphNode* p;
	w = G->adjList_H[v];
	for (; w; w = w->link) {//w가 v의 인접정점 안에 있다면
		if (!G->visited[w->vertex]) {
			G->pred[w->vertex] = v;
			dfs_recur(G, w->vertex);//재귀
		}
	}
}

// 너비 우선 탐색, width first search
void bfs(Graph* G, int v) {
	// Fill your code 큐
	Queue* Q = createQueue();
	G->visited[v] = TRUE;
	enqueue(Q, v);
	printf("     %d", v);
	graphNode* w;
	while (!isEmptyQueue(Q)){
		v = dequeue(Q);
		w = G->adjList_H[v];//^오^ 밖이 아니라 안에 선언해야한다...(=dfs_iter)
		for (; w; w = w->link) {//w가 v의 인접정점 안에 있다면
			if (!G->visited[w->vertex]) {
				enqueue(Q, w->vertex);
				G->visited[w->vertex] = TRUE;
				printf("     %d", w->vertex);
			}
		}
	}
}		
