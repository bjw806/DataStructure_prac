#include <stdio.h>
#include <stdlib.h>
#include "ArrayGraph.h"
#include "ArrayStack.h"

// 공백 그래프를 생성하는 연산, operations that generate a empty graph
Graph* createGraph() {
	int i, j;
	Graph* G = (Graph*)malloc(sizeof(Graph));	
	G->n = 0;
	for(i=0; i<MAX_SIZE; i++) {
		for(j=0; j<MAX_SIZE; j++) {
			if(i==j)
				G->cost[i][j] = 0;
			else
				G->cost[i][j] = INF;
			G->A[i][j] = INF;
		}
		G->dist[i] = INF;
		G->pred[i] = NONE;
		G->S[i] = 0;
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
		printf("[ERROR] 그래프 정점의 개수 초과\n");	// [ERROR] Exceeding the number of graph vertices
		return;
	}
	G->n++;
}

// 그래프 G에 간선(u, v)를 삽입, insert edge(u, v) into graph G
void insertEdge(Graph* G, int u, int v, int weight) {
	G->cost[u][v] = weight;	
}

// 그래프 G에 정점 v를 삭제하고 연결된 모든 간선 삭제, delete vertex v in graph G and delete all connected edges
void deleteVertex(Graph* G, int v) {
	int i;
	for(i=0; i<G->n; i++) {
		G->cost[i][v] = INF;
		G->cost[v][i] = INF;
	}	
}

// 그래프 G에 간선 (u, v)를 삭제, delete edge(u, v) on graph G
void deleteEdge(Graph* G, int u, int v) {
	G->cost[u][v] = INF;
}

// 그래프 G의 리소스 해제, unresource graph G
void destroyGraph(Graph* G) {
	int i, j;
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++) {
			if(i != j)
				G->cost[i][j] = INF;
	}
		G->dist[i] = INF;
		G->pred[i] = NONE;
	}
	G->n = 0;
}

// 그래프 G의 인접 행렬 정보 출력, display adjacency matrix information for graph G
void displayGraph(Graph* G) {
	int i, j;
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++){
			if(G->cost[i][j] == INF)
				printf("INF\t");
			else
				printf("%2d\t", G->cost[i][j]);
		}			
		printf("\n");
	}
}

// 최소 비용을 갖는 다음 정점을 찾는 연산, operation that finds the next vertex with a minimum cost
// Dijkstra Algorithm 구현시 필요할 경우 이용, use when needed to implement Dijkstra Algorithm 
int nextVertex(Graph* G) {
	int i, minCost, minVertex;
	minCost = INF;
	minVertex = -1;
	for (i = 0; i < G->n; i++) {
		if (G->dist[i] < minCost && i != G->S[i]) {//기존코드 잘못됨... i!= 추가
			minCost = G->dist[i];
			minVertex = i;
		}
	}
	return minVertex;
}	

// Dijkstra Algorithm
void dijkstra(Graph* G, int v) {
	//S=정점 집합
	//방문한 집합에 추가.
	G->S[0] = v;//0
	for (int i = 0; i < G->n; i++) {
		G->dist[i] = G->cost[v][i];//최초의 dist까지 가는 비용 저장
		if (G->cost[v][i] != INF)//간선이 연결되어있으면 (시작정점에서 바로 갈수있음)
			G->pred[i] = v;
		else //시작에서 바로 갈 수 없음
			G->pred[i] = NULL;
	}
	 
	for (int i = 0; i < G->n; i++) {
		int u = nextVertex(G);//최소정점
		G->S[i+1] = u;//S에 추가
		//relaxation
		for (int w = 0; w < G->n; w++) {
			if (w != G->S[i] && G->dist[w] > G->dist[u] + G->cost[u][w] ) {
				G->dist[w] = G->dist[u] + G->cost[u][w];
				G->pred[w] = u;
			}
		}
	}
}

// Bellman-Ford Algorithm
int bellmanFord(Graph* G, int v) {
	// Fill your code
	int n = G->n;
	G->dist[v] = 0;
	for (int k = 0; k < n; k++)
		for (int w = 0; w < n; w++)//모든 정점
			for (int u = 0; u < n; u++)//모든 간선
				if (G->dist[w] > G->dist[u] + G->cost[u][w]) {//더 크면
					G->dist[w] = G->dist[u] + G->cost[u][w];//갱신
					G->pred[w] = u;
				}
	return TRUE;
}

// Floyd-Warshall Algorithm
void floyd(Graph* G){
	// Fill your code
	int n = G->n;
	for (int i = 0; i < n;i++)//정점의 개수만큼
		for (int j = 0; j < n;j++)
			G->A[i][j] = G->cost[i][j];
	for (int k = 0; k < n; k++)//n개
		for (int i = 0; i < n; i++)//n개
			for (int j = 0; j < n; j++)//n개
				if (G->A[i][k] + G->A[k][j] < G->A[i][j])
					G->A[i][j] = G->A[i][k] + G->A[k][j];
}	

// 최단경로 출력, display shortest path
void printShortestPath(Graph* G, int src, int dst) {
	printf("%c -> %c 최단 경로: %c", src+65, dst+65, src+65);	// "%c -> %c Shortest Path: %c"
	int v = dst;
	Stack* stack = createStack();

	// Fill your code
	push(stack, v);
	while (v) {//dst부터 stack에 저장
		push(stack, v);
		v = G->pred[v];
	}

	v = pop(stack);//일단 한개 pop

	while (stack->top >= 0) {//거꾸로 출력
		printf("     %c", v + 65);
		v = pop(stack);
	}

	printf("\n");
	clearStack(stack);
}	

// 최단경로 비용 출력, display shortest path cost
int printShortestPathCost(Graph* G, int src, int dst) {
	printf("%c -> %c 최단 경로 비용: %d\n", src+65, dst+65, G->dist[dst]);	// "%c -> %c Shortest Path Cost: %d"
}

// 모든 정점 쌍 사이의 최단 경로 비용 출력, display shorteet path cost between all pairs of vertices
void printAllPairShortestCost(Graph* G) {
	int i, j;
	
	for(i=0; i<G->n; i++) {
		for(j=0; j<G->n; j++) {
			if(G->A[i][j] == INF)
				printf("INF\t");
			else
				printf("%2d\t", G->A[i][j]);
		}			
		printf("\n");
	}
}		
