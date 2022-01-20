#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"

int testPair(char* exp) {
	Stack* S = (Stack*)malloc(sizeof(Stack));
	S = create();
	char symbol, lparen;
	int i, length = strlen(exp);

	i = 0;
	while (i < length) {//앞글자부터 끝까지 반복
		symbol = exp[i];
		
		switch (symbol){//괄호일 경우만 해당
		case '(':
		case '{':
		case '[':
			push(S, symbol);//열린괄호는 push
			break;
		case ')':
		case '}':
		case ']':
			lparen = pop(S);//닫힌괄호는 pop
			switch (symbol) {//반대 짝으로 비교해야함
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
		default://다른 문자들은 그냥 넘김
			break;
		}
		i++;
	}
	
	if (!isEmpty(S))//스택이 차있으면 안됨
		return FALSE;
	return TRUE;
}

int main() {
	int i;
	char* x[4] = {"(A - B) * C) + D", "(A - B) * C + ( D", "A [ B ( C ] )", "{A / (B - C)}"};
	
	for(i=0; i<4; i++) {
		printf("%s ", x[i]);
		if(testPair(x[i]))
			printf("-> 수식의 괄호가 올바르게 사용되었습니다!\n");
		else
			printf("-> 수식의 괄호가 틀렸습니다!\n");
	}
	
	return 0;
}