#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

// 공백 이진 트리 생성 연산
BinTree* createBT(){
	BinTree* bt = (BinTree*)malloc(sizeof(BinTree));
	bt->key = EMPTY;
	bt->left = NULL;
	bt->right = NULL;
	return bt;
}

// 이진 트리가 비어있는지 검사하는 연산
int isBTEmpty(BinTree* bt) {
	if (bt->left == NULL && bt->right == NULL && bt->key == EMPTY)
		return TRUE;
	else
		return FALSE;
}

// 왼쪽 서브트리가 bt1, 오른쪽 서브트리가 bt2, x값을 가지는 노드를 루트로 하는 이진트리 반환
BinTree* makeBT(BinTree* bt1, BTData x, BinTree* bt2) {
	BinTree* bt = (BinTree*)malloc(sizeof(BinTree));
	bt->key = x;
	bt->left = bt1;
	bt->right = bt2;
	return bt;
}

// bt2를 bt1의 왼쪽 서브트리로 연결
void makeLSubtree(BinTree* bt1, BinTree* bt2) {
	bt1->left = bt2;
}

// bt2를 bt1의 오른쪽 서브트리로 연결
void makeRSubtree(BinTree* bt1, BinTree* bt2) {
	bt1->right = bt2;
}

// bt의 왼쪽 서브트리를 반환
BinTree* getLSubtree(BinTree* bt) {
	return bt->left;
}

// bt의 오른쪽 서브트리를 반환
BinTree* getRSubtree(BinTree* bt) {
	return bt->right;
}

// bt의 root 노드에 x 값 저장
void setData(BinTree* bt, BTData x) {
	bt->key = x;
}

// bt의 root에 저장된 데이터를 반환
BTData getData(BinTree* bt) {
	return bt->key;
}

// bt가 가리키는 노드를 루트로 하는 트리 전부 소멸
void deleteBT(BinTree* bt) {
	if(bt == NULL)
		return;
	
	deleteBT(bt->left);
	deleteBT(bt->right);
	
	printf("delete tree data: %d \n", bt->key);
	free(bt);
}

// 중위 순회, inorder traversal
void InorderTraverse(BinTree* bt, visitFuncPtr action) {
	if (bt != NULL) {//(저번주 과제와 동일)
		InorderTraverse(bt->left, action);
		printf("%d ", bt->key);//중위는 중간에
		InorderTraverse(bt->right, action);
	}
}

// 데이터 x가 저장된 노드 탐색
BinTree* searchBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	
	// Fill your code
	while (p != NULL) {
		if(x == p->key) //찾으면 반환
			return p;
		if (x < p->key)
			p = p->left;
		else 
			p = p->right;
	}
	return NULL;
}

// 데이터 x 저장
void insertBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* parent = NULL;	
	
	// 삽입할 노드 탐색
	int i=0;//1이면 왼쪽, 2면 오른쪽 삽입
	while (p != NULL) {
		parent = p; //NULL전의 노드를 부모로
		if (x < p->key) {//검색(끝 NULL까지)
			i=1;
			p = p->left;
		}
		else {
			i=2;
			p = p->right;
		}
	}

	// 삽입할 노드 생성
	BinTree* pp = createBT();
	setData(pp, x);

	// 삽입 노드 연결
	switch (i) {
	case 1:
		makeLSubtree(parent, pp);//pp를 부모와 연결해줌
		break;
	case 2:
		makeRSubtree(parent, pp);
		break;
	}
}

// 데이터 x 노드 삭제
void deleteBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* parent = NULL;

	if (!searchBST(bt,x)) {//삭제할 노드가 없으면
		printf("삭제할 노드가 없습니다.\n");
		return NULL;
	}

	while (p != NULL) {
		parent = p; //NULL전의 노드를 부모로
		if (x < p->key) {//검색(끝 NULL까지)
			p = p->left;
			if (x == p->key)
				break;
		}
		else {
			p = p->right;
			if (x == p->key)
				break;
		}
	}

	if (p->left == NULL && p->right == NULL) {//차수가 0인경우
		if (parent->left == p)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	else if (p->left || p->right == NULL) {//차수가 1인경우
		if (p->left != NULL) {
			if (parent->left == p)
				parent->left = p->left;
			else
				parent->right = p->left;
		}
		else {
			if (parent->left == p)
				parent->left = p->right;
			else
				parent->right = p->right;
		}
	}
	else if (p->left == NULL && p->right == NULL) {//차수가 2인경우
		BinTree* q = maxNode(p->left);//가장 큰 노드를 후계자 노드로
		p->key = q->key;
		deleteBST(p->left, q->key);
	}
}	

BinTree* maxNode(BinTree* bt) {//가장 큰 노스 리턴
	BinTree* p = bt;

	while (p != NULL) {
		if (p->right != NULL) {//오른쪽에 있는 노드가 가장 큼
			p = p->right;
		}
		else
			break;
	}
	return p;
}

/*// Fill your code
	BinTree* p = bt;
	BinTree* parent = NULL;
	int i = 0, j = 0;
	// 삭제할 노드가 없는 경우
	// Fill your code
	if (searchBST(bt, x)) {
		printf("삭제할 노드가 없습니다.\n");
		return;
	}
	else {
		while (p != NULL) {
			parent = p; //NULL전의 노드를 부모로
			if (x == p->key)
				break;
			if (x < p->key) {//검색(끝 NULL까지)
				i = 1;
				p = p->left;
			}
			else {
				i = 2;
				p = p->right;
			}
		}
	}
	p = searchBST(bt, x);

	if (p->left != NULL)//왼쪽 안비었으면 +1
		j++;
	if (p->right != NULL)//오른쪽 안비었으면 +1
		j++;

	switch(j) {//LR둘다 비었음
	case 0:// CASE 1: 삭제할 노드의 차수가 0인 경우
		deleteBT(p, x);
		break;
	case 1:// CASE 2: 삭제할 노드의 차수가 1인 경우
		if (p->left == NULL)//p의 왼쪽이 없으면
			switch (i) {//p의 부모의 오른쪽과 p의 왼쪽을 이어준다
			case 1:
				makeLSubtree(parent, p->right);
				break;
			case 2:
				makeRSubtree(parent, p->right);
				break;
			}
		else if (p->right == NULL) {
			switch (i) {//부모와 이어준다
			case 1:
				makeLSubtree(parent, p->left);
				break;
			case 2:
				makeRSubtree(parent, p->left);
				break;
			}
		}
		deleteBT(p, x);
		break;
	case 2:// CASE 3: 삭제할 노드의 차수가 2인 경우
		//p와 바꿈
		//p의 부모->left, right 연결
		p = p->left;
		while (p != NULL) {//왼쪽 서브트리에서 가장 큰 값을 찾음
			if (p->right != NULL) {
				p = p->right;
			}
			else {
				break;
			}
		}

		if (p->left == NULL)//p의 왼쪽이 없으면
			switch (i) {//p의 부모의 오른쪽과 p의 왼쪽을 이어준다
			case 1:
				makeLSubtree(parent, p->right);
				break;
			case 2:
				makeRSubtree(parent, p->right);
				break;
			}
		else if (p->right == NULL) {
			switch (i) {//부모와 이어준다
			case 1:
				makeLSubtree(parent, p->left);
				break;
			case 2:
				makeRSubtree(parent, p->left);
				break;
			}
		}
		break;
	}*/