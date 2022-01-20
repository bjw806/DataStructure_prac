#include <stdio.h>
#include <stdlib.h>
#include "ListGraph.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"

// ���� �׷����� �����ϴ� ����, operations to generate a empty graph
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

// �׷����� �������� �˻�, check if the graph is empty
int isEmptyGraph(Graph* G) {
	return G->n == 0;
}

// �׷��� G�� ���� v�� ����, insert vertex v into graph G
void insertVertex(Graph* G, int v) {
	if((G->n)+1 > MAX_SIZE) {
		printf("[ERROR] �׷��� ������ ���� �ʰ�\n");	// [ERROR] Exceeding the number of graph vertices
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
		printf("���� %d�� ��������Ʈ", i);	// Adjacent list with vertex %d
		p = G->adjList_H[i];
		while(p) {
			printf(" -> %d ", p->vertex);
			p = p->link;
		}			
		printf("\n");
	}
}

// visited[], pred[] �ʱ�ȭ, initialized visited[], pre[]
void initSearch(Graph* G) {
	int i;
	for(i=0; i<G->n; i++) {
		G->visited[i] = FALSE;
		G->pred[i] = -1;
	}
}

// ���� �켱 Ž�� iterative version, depth first search iterative version
void dfs_iter(Graph* G, int v) {
	// Fill your code ����
	graphNode* w = (graphNode*)malloc(sizeof(graphNode));
	Stack* S = create();
	G->visited[v] = TRUE;
	push(S, v);
	printf("     %d", v);
	while (!isEmpty(S)) {
		v = pop(S);
		w = G->adjList_H[v];//w<-v�� ��������
		while (w) {
			if (!G->visited[w->vertex]) {//w�� �湮���� �ʾ�����
				push(S, v);
				G->visited[w->vertex] = TRUE;
				printf("     %d", w->vertex);
				v = w->vertex;
				w = G->adjList_H[v]->link;//w=v�� ��������
			}
			else
				w = w->link;
		}
	}
}	

// ���� �켱 Ž�� recursive version, depth first search recursive version
void dfs_recur(Graph* G, int v)	{//����̿�
	// Fill your code ����
	printf("     %d", v);
	G->visited[v] = TRUE;
	graphNode* w;
	graphNode* p;
	w = G->adjList_H[v];
	for (; w; w = w->link) {//w�� v�� �������� �ȿ� �ִٸ�
		if (!G->visited[w->vertex]) {
			G->pred[w->vertex] = v;
			dfs_recur(G, w->vertex);//���
		}
	}
}

// �ʺ� �켱 Ž��, width first search
void bfs(Graph* G, int v) {
	// Fill your code ť
	Queue* Q = createQueue();
	G->visited[v] = TRUE;
	enqueue(Q, v);
	printf("     %d", v);
	graphNode* w;
	while (!isEmptyQueue(Q)){
		v = dequeue(Q);
		w = G->adjList_H[v];//^��^ ���� �ƴ϶� �ȿ� �����ؾ��Ѵ�...(=dfs_iter)
		for (; w; w = w->link) {//w�� v�� �������� �ȿ� �ִٸ�
			if (!G->visited[w->vertex]) {
				enqueue(Q, w->vertex);
				G->visited[w->vertex] = TRUE;
				printf("     %d", w->vertex);
			}
		}
	}
}		
