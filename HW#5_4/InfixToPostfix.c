#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"
#include "InfixToPostfix.h"

// 연산자, 피연산자, 괄호 -> enueration type 변환, operator, operand, parenthesis -> enueration type transform
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

// enumeration type에 따라 연산자, 괄호 출력, operator, parenthesis display according to enumeration type
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

// 연산자 우선순위 계산: 괄호 < +, - < *, /, %, calculate operator priority : parentheses < +, - < *, /, %
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

// 중위표기식 -> 후위표기식 변환 연산, inflix notation -> postfix notation transform operation
char* toPostfix(Stack* S, char* exp) {
	static char result[256] = "";
	int len = 0, n = 0;
	char symbol = exp[0];
	precedence token = getToken(symbol);		// 연산자의 종류 기록, recording the type of operator
	
	int i = 0;
	len = strlen(exp);
	S = create();
	while (n < len) {//앞글자부터 끝까지 반복
		symbol = exp[n];

		switch (symbol) {//연산자를 만나면
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
					else if (prec(getToken(symbol)) > prec(getToken(peek(S)))) {//top보다 연산자가 더 높으면
						push(S, symbol);
						break;
					}
					else {//같거나 낮으면
						result[i++] = pop(S);
					}
				}
			}
			break;
		case ')': {
			char s = pop(S);
			while (s != '(') {// )를 만나면
				result[i++] = s;
				s = pop(S);
			}
			break; }
		default://피연산자는 그대로 출력
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

// 후위표기식의 계산 연산, computation of postfix notaion
float evalPostfix(Stack* S, char* exp) {
	int op1, op2;
	int n = 0;
	char symbol = exp[0];
	precedence token = getToken(symbol);
	
	int i = 0;
	while(exp[i] != NULL) {//exp에 처리할 문자가 남아 있으면
		symbol = exp[i];
		if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/'){//피연산자
			n = symbol - '0';
			push(S, n);
		}
		else{//연산자
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