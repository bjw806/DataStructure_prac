#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#define TRUE 1
#define FALSE 0
#define EMPTY 123456789

typedef int BTData;

typedef struct BinaryTreeNode {
	BTData data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BinTree;

BinTree* createBT();			// 공백 이진 트리 생성 연산
int isBTEmpty(BinTree* bt);		// 이진 트리가 비어있는지 검사하는 연산
BinTree* makeBT(BinTree* bt1, BTData x, BinTree* bt2); 	// 왼쪽 서브트리가 bt1, 오른쪽 서브트리가 bt2, x값을 가지는 노드를 루트로 하는 이진트리 반환
void makeLSubtree(BinTree* bt1, BinTree* bt2);		// bt2를 bt1의 왼쪽 서브트리로 연결
void makeRSubtree(BinTree* bt1, BinTree* bt2);		// bt2를 bt1의 오른쪽 서브트리로 연결
BinTree* getLSubtree(BinTree* bt);		// bt의 왼쪽 서브트리를 반환
BinTree* getRSubtree(BinTree* bt);		// bt의 오른쪽 서브트리를 반환
void setData(BinTree* bt, BTData x);	// bt의 root 노드에 x 값 저장
BTData getData(BinTree* bt);			// bt의 root에 저장된 데이터를 반환
void deleteBT(BinTree* bt);	// bt가 가리키는 노드를 루트로 하는 트리 전부 소멸

typedef void visitFuncPtr(BTData x);						// 노드 방문시 action 정의
void InorderTraverse(BinTree* bt, visitFuncPtr action);		// 중위 순회
void PreorderTraverse(BinTree* bt, visitFuncPtr action);	// 전위 순회
void PostorderTraverse(BinTree* bt, visitFuncPtr action);	// 후위 순회

#endif
