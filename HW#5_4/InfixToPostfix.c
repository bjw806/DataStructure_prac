#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"
#include "InfixToPostfix.h"

// ������, �ǿ�����, ��ȣ -> enueration type ��ȯ, operator, operand, parenthesis -> enueration type transform
precedence getToken(char ch) {
	precedence token;
	switch(ch) {
		case '(':	token = lparen;		break;
		case ')': 	token = rparen;		break;
		case '+':	token = plus;		break;
		case '-':	token = minus;		break;
		case '*':	token = multiply;	break;
		case '/':	token = divide;		break;
		case '%':	token = mod;		break;
		case '\0':	token = eos;		break;
		default:	token = operand;
	}
	
	return token;
}

// enumeration type�� ���� ������, ��ȣ ���, operator, parenthesis display according to enumeration type
char printToken(precedence token) {
	char ch;
	switch(token) {
		case lparen:	ch = '(';	break;
		case rparen:	ch = ')';	break;
		case plus:		ch = '+';	break;
		case minus:		ch = '-';	break;
		case multiply:	ch = '*';	break;
		case divide:	ch = '/';	break;
		case mod:		ch = '%';	break; 
	}
	
	return ch;
}

// ������ �켱���� ���: ��ȣ < +, - < *, /, %, calculate operator priority : parentheses < +, - < *, /, %
int prec(precedence symbol) {
	switch(symbol) {
		case lparen:
		case rparen:	return 0;
		case plus:
		case minus:		return 1;
		case multiply:
		case divide:
		case mod:		return 2;
	}
}

// ����ǥ��� -> ����ǥ��� ��ȯ ����, inflix notation -> postfix notation transform operation
char* toPostfix(Stack* S, char* exp) {
	static char result[256] = "";
	int len = 0, n = 0;
	char symbol = exp[0];
	precedence token = getToken(symbol);		// �������� ���� ���, recording the type of operator
	
	int i = 0;
	len = strlen(exp);
	S = create();
	while (n < len) {//�ձ��ں��� ������ �ݺ�
		symbol = exp[n];

		switch (symbol) {//�����ڸ� ������
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			while (TRUE) {
				if (isEmpty(S)) {
					push(S, symbol);
					break;
				}
				else if (symbol == '(') {
					push(S, symbol);
					break;
				}
				else {
					if (peek(S) == '(') {
						push(S, symbol);
						break;
					}
					else if (prec(getToken(symbol)) > prec(getToken(peek(S)))) {//top���� �����ڰ� �� ������
						push(S, symbol);
						break;
					}
					else {//���ų� ������
						result[i++] = pop(S);
					}
				}
			}
			break;
		case ')': {
			char s = pop(S);
			while (s != '(') {// )�� ������
				result[i++] = s;
				s = pop(S);
			}
			break; }
		default://�ǿ����ڴ� �״�� ���
			result[i++] = symbol;
			break;
		}
		n++;
	}

	if (!isEmpty(S)) {
		while (S->top != NULL) {
			result[i++] = pop(S);
		}
	}
	return result;
}

// ����ǥ����� ��� ����, computation of postfix notaion
float evalPostfix(Stack* S, char* exp) {
	int op1, op2;
	int n = 0;
	char symbol = exp[0];
	precedence token = getToken(symbol);
	
	int i = 0;
	while(exp[i] != NULL) {//exp�� ó���� ���ڰ� ���� ������
		symbol = exp[i];
		if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/'){//�ǿ�����
			n = symbol - '0';
			push(S, n);
		}
		else{//������
			op2 = pop(S);
			op1 = pop(S);
			switch (symbol)
			{
			case '+':
				push(S, op1 + op2);
				break;
			case '-':
				push(S, op1 - op2);
				break;
			case '*':
				push(S, op1 * op2);
				break;
			case '/':
				push(S, op1 / op2);
				break;
			}
		}
		i++;
	}
	return pop(S);
}