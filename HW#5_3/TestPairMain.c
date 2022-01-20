#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"

int testPair(char* exp) {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S = create();
	char symbol, lparen;
	int i, length = strlen(exp);

	i = 0;
	while (i < length) {//�ձ��ں��� ������ �ݺ�
		symbol = exp[i];
		
		switch (symbol){//��ȣ�� ��츸 �ش�
		case '(':
		case '{':
		case '[':
			push(S, symbol);//������ȣ�� push
			break;
		case ')':
		case '}':
		case ']':
			lparen = pop(S);//������ȣ�� pop
			switch (symbol) {//�ݴ� ¦���� ���ؾ���
			case ')':
				if ('(' != lparen) {
					return FALSE;
				}
				break;
			case '}':
				if ('{' != lparen) {
					return FALSE;
				}
				break;
			case ']':
				if ('[' != lparen) {
					return FALSE;
				}
				break;
			}
			break;
		default://�ٸ� ���ڵ��� �׳� �ѱ�
			break;
		}
		i++;
	}
	
	if (!isEmpty(S))//������ �������� �ȵ�
		return FALSE;
	return TRUE;
}

int main() {
	int i;
	char* x[4] = {"(A - B) * C) + D", "(A - B) * C + ( D", "A [ B ( C ] )", "{A / (B - C)}"};
	
	for(i=0; i<4; i++) {
		printf("%s ", x[i]);
		if(testPair(x[i]))
			printf("-> ������ ��ȣ�� �ùٸ��� ���Ǿ����ϴ�!\n");
		else
			printf("-> ������ ��ȣ�� Ʋ�Ƚ��ϴ�!\n");
	}
	
	return 0;
}