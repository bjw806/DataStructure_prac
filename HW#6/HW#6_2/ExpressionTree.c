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
		if (isdigit(exp[i]))//�ǿ����ڸ� ���ڸ� ������ �ٲ㼭 ����
			setData(bNode, exp[i] - '0');
		else {//�����ڸ�
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
	if (getLSubtree(bt) == NULL && getRSubtree(bt) == NULL)//Ż������
		return getData(bt);

	op1 = evalExpTree(getLSubtree(bt));//����� ����
	op2 = evalExpTree(getRSubtree(bt));
	switch (getData(bt)) {//�����ڿ� ���� �����ϱ�
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
	if(0<=x && x<=9)			// �ǿ����� ���, operand output
		printf("%d ", x);
	else						// ������ ���, operator output
		printf("%c ", x);
}

void showPrefixExp(BinTree* bt) {
	// Fill your code
	if (bt == NULL)
		return;
	showNodeData(bt->data);//������ ���� ���
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
	
	showInfixExp(bt->left);		// ù ��° �ǿ����� ���, first operand output
	showNodeData(bt->data);		// ������ ���, operator output
	showInfixExp(bt->right);	// �� ��° �ǿ����� ���, second operand output
	
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
	showNodeData(bt->data);//������ ���߿� ���
}
