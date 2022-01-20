#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BinaryTree.h"
#include "LinkedStack.h"

BinTree* createExpTree(char exp[]) {
	Stack* S = createStack();
	BinTree* bNode;
	int expLen = strlen(exp);
	int i;
	
	// Fill your code
	for (i = 0; i < expLen; i++) {
		bNode = createBT();
		if (isdigit(exp[i]))//피연산자면 문자를 정수로 바꿔서 저장
			setData(bNode, exp[i] - '0');
		else {//연사자면
			makeRSubtree(bNode, pop(S));
			makeLSubtree(bNode, pop(S));
			setData(bNode, exp[i]);
		}
		push(S, bNode);
	}
	return pop(S);
}

int evalExpTree(BinTree* bt) {
	int op1, op2;
	// Fill your code
	if (getLSubtree(bt) == NULL && getRSubtree(bt) == NULL)//탈출조건
		return getData(bt);

	op1 = evalExpTree(getLSubtree(bt));//재귀적 구성
	op2 = evalExpTree(getRSubtree(bt));
	switch (getData(bt)) {//연산자에 따라 연산하기
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}
	return 0;
}

void showNodeData(int x) {
	if(0<=x && x<=9)			// 피연산자 출력, operand output
		printf("%d ", x);
	else						// 연산자 출력, operator output
		printf("%c ", x);
}

void showPrefixExp(BinTree* bt) {
	// Fill your code
	if (bt == NULL)
		return;
	showNodeData(bt->data);//전위는 먼저 출력
	if (bt->left != NULL || bt->right != NULL)
		showPrefixExp(bt->left);
	if (bt->left != NULL || bt->right != NULL)
		showPrefixExp(bt->right);
}

void showInfixExp(BinTree* bt) {
	if(bt == NULL)
		return;
	
	if(bt->left != NULL || bt->right != NULL)
		printf(" ( ");
	
	showInfixExp(bt->left);		// 첫 번째 피연산자 출력, first operand output
	showNodeData(bt->data);		// 연산자 출력, operator output
	showInfixExp(bt->right);	// 두 번째 피연산자 출력, second operand output
	
	if(bt->left != NULL || bt->right != NULL)
		printf(" ) "); 
}

void showPostfixExp(BinTree* bt) {
	// Fill your code
	if (bt == NULL)
		return;
	if (bt->left != NULL || bt->right != NULL)
		showPostfixExp(bt->left);
	if (bt->left != NULL || bt->right != NULL)
		showPostfixExp(bt->right);
	showNodeData(bt->data);//후위는 나중에 출력
}
