#include <stdio.h>
#include "LinkedStack.h"

int main() {
	Stack* S;
	element item;
	int i;
	
	printf("\n(1) ���� ���� �����ϱ�\n");	
	S = create();
	displayStack(S);

	printf("\n(2) ���ÿ� 10, 20�� ���ʷ� ����\n");
	push(S, 10);
	displayStack(S);
	push(S, 20);
	displayStack(S);

	printf("\n(3) ���� top�� ��Ҹ� ���\n");
	printf("TOP�� ����� ���: %d\n", peek(S));

	printf("\n(4) ���ÿ��� ��� ����\n");
	if (peek(S) != ERROR) {//ERROR�� �ƴҶ���(������� ������)
		i = peek(S);
		pop(S);
		printf("%d ����\n", i);
	}
	displayStack(S);

	printf("\n(5) ���ÿ��� ��� ����\n");
	if (peek(S) != ERROR) {//ERROR�� �ƴҶ���(������� ������)
		i = peek(S);
		pop(S);
		printf("%d ����\n", i);
	}
	displayStack(S);

	printf("\n(6) ���ÿ��� ��� ����\n");	
	if (peek(S) != ERROR) {//ERROR�� �ƴҶ���(������� ������)
		i = peek(S);
		pop(S);
		printf("%d ����\n", i);
	}
	displayStack(S);

	printf("\n(7) ���ÿ� 1���� 10���� �ڿ����� ���ʷ� ����\n");
	push(S, 1);
	push(S, 2);
	push(S, 3);
	push(S, 4);
	push(S, 5);
	push(S, 6);
	push(S, 7);
	push(S, 8);
	push(S, 9);
	push(S, 10);
	displayStack(S);
	
	printf("\n(8) ���� ����\n");
	clear(S);
	displayStack(S);
	

	return 0;
}

