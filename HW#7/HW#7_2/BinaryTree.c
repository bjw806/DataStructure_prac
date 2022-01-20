#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

// ���� ���� Ʈ�� ���� ����
BinTree* createBT(){
	BinTree* bt = (BinTree*)malloc(sizeof(BinTree));
	bt->key = EMPTY;
	bt->left = NULL;
	bt->right = NULL;
	return bt;
}

// ���� Ʈ���� ����ִ��� �˻��ϴ� ����
int isBTEmpty(BinTree* bt) {
	if (bt->left == NULL && bt->right == NULL && bt->key == EMPTY)
		return TRUE;
	else
		return FALSE;
}

// ���� ����Ʈ���� bt1, ������ ����Ʈ���� bt2, x���� ������ ��带 ��Ʈ�� �ϴ� ����Ʈ�� ��ȯ
BinTree* makeBT(BinTree* bt1, BTData x, BinTree* bt2) {
	BinTree* bt = (BinTree*)malloc(sizeof(BinTree));
	bt->key = x;
	bt->left = bt1;
	bt->right = bt2;
	return bt;
}

// bt2�� bt1�� ���� ����Ʈ���� ����
void makeLSubtree(BinTree* bt1, BinTree* bt2) {
	bt1->left = bt2;
}

// bt2�� bt1�� ������ ����Ʈ���� ����
void makeRSubtree(BinTree* bt1, BinTree* bt2) {
	bt1->right = bt2;
}

// bt�� ���� ����Ʈ���� ��ȯ
BinTree* getLSubtree(BinTree* bt) {
	return bt->left;
}

// bt�� ������ ����Ʈ���� ��ȯ
BinTree* getRSubtree(BinTree* bt) {
	return bt->right;
}

// bt�� root ��忡 x �� ����
void setData(BinTree* bt, BTData x) {
	bt->key = x;
}

// bt�� root�� ����� �����͸� ��ȯ
BTData getData(BinTree* bt) {
	return bt->key;
}

// bt�� ����Ű�� ��带 ��Ʈ�� �ϴ� Ʈ�� ���� �Ҹ�
void deleteBT(BinTree* bt) {
	if(bt == NULL)
		return;
	
	deleteBT(bt->left);
	deleteBT(bt->right);
	
	printf("delete tree data: %d \n", bt->key);
	free(bt);
}

// ���� ��ȸ, inorder traversal
void InorderTraverse(BinTree* bt, visitFuncPtr action) {
	if (bt != NULL) {//(������ ������ ����)
		InorderTraverse(bt->left, action);
		printf("%d ", bt->key);//������ �߰���
		InorderTraverse(bt->right, action);
	}
}

// ������ x�� ����� ��� Ž��
BinTree* searchBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	
	// Fill your code
	while (p != NULL) {
		if(x == p->key) //ã���� ��ȯ
			return p;
		if (x < p->key)
			p = p->left;
		else 
			p = p->right;
	}
	return NULL;
}

// ������ x ����
void insertBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* parent = NULL;	
	
	// ������ ��� Ž��
	int i=0;//1�̸� ����, 2�� ������ ����
	while (p != NULL) {
		parent = p; //NULL���� ��带 �θ��
		if (x < p->key) {//�˻�(�� NULL����)
			i=1;
			p = p->left;
		}
		else {
			i=2;
			p = p->right;
		}
	}

	// ������ ��� ����
	BinTree* pp = createBT();
	setData(pp, x);

	// ���� ��� ����
	switch (i) {
	case 1:
		makeLSubtree(parent, pp);//pp�� �θ�� ��������
		break;
	case 2:
		makeRSubtree(parent, pp);
		break;
	}
}

// ������ x ��� ����
void deleteBST(BinTree* bt, BTData x) {
	BinTree* p = bt;
	BinTree* parent = NULL;

	if (!searchBST(bt,x)) {//������ ��尡 ������
		printf("������ ��尡 �����ϴ�.\n");
		return NULL;
	}

	while (p != NULL) {
		parent = p; //NULL���� ��带 �θ��
		if (x < p->key) {//�˻�(�� NULL����)
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

	if (p->left == NULL && p->right == NULL) {//������ 0�ΰ��
		if (parent->left == p)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	else if (p->left || p->right == NULL) {//������ 1�ΰ��
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
	else if (p->left == NULL && p->right == NULL) {//������ 2�ΰ��
		BinTree* q = maxNode(p->left);//���� ū ��带 �İ��� ����
		p->key = q->key;
		deleteBST(p->left, q->key);
	}
}	

BinTree* maxNode(BinTree* bt) {//���� ū �뽺 ����
	BinTree* p = bt;

	while (p != NULL) {
		if (p->right != NULL) {//�����ʿ� �ִ� ��尡 ���� ŭ
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
	// ������ ��尡 ���� ���
	// Fill your code
	if (searchBST(bt, x)) {
		printf("������ ��尡 �����ϴ�.\n");
		return;
	}
	else {
		while (p != NULL) {
			parent = p; //NULL���� ��带 �θ��
			if (x == p->key)
				break;
			if (x < p->key) {//�˻�(�� NULL����)
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

	if (p->left != NULL)//���� �Ⱥ������ +1
		j++;
	if (p->right != NULL)//������ �Ⱥ������ +1
		j++;

	switch(j) {//LR�Ѵ� �����
	case 0:// CASE 1: ������ ����� ������ 0�� ���
		deleteBT(p, x);
		break;
	case 1:// CASE 2: ������ ����� ������ 1�� ���
		if (p->left == NULL)//p�� ������ ������
			switch (i) {//p�� �θ��� �����ʰ� p�� ������ �̾��ش�
			case 1:
				makeLSubtree(parent, p->right);
				break;
			case 2:
				makeRSubtree(parent, p->right);
				break;
			}
		else if (p->right == NULL) {
			switch (i) {//�θ�� �̾��ش�
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
	case 2:// CASE 3: ������ ����� ������ 2�� ���
		//p�� �ٲ�
		//p�� �θ�->left, right ����
		p = p->left;
		while (p != NULL) {//���� ����Ʈ������ ���� ū ���� ã��
			if (p->right != NULL) {
				p = p->right;
			}
			else {
				break;
			}
		}

		if (p->left == NULL)//p�� ������ ������
			switch (i) {//p�� �θ��� �����ʰ� p�� ������ �̾��ش�
			case 1:
				makeLSubtree(parent, p->right);
				break;
			case 2:
				makeRSubtree(parent, p->right);
				break;
			}
		else if (p->right == NULL) {
			switch (i) {//�θ�� �̾��ش�
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