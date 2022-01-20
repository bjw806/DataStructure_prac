#include <stdio.h>
#include "LinkedStack.h"

int main() {
	Stack* S;
	element item;
	int i;
	
	printf("\n(1) 공백 스택 생성하기\n");	
	S = create();
	displayStack(S);

	printf("\n(2) 스택에 10, 20을 차례로 삽입\n");
	push(S, 10);
	displayStack(S);
	push(S, 20);
	displayStack(S);

	printf("\n(3) 현재 top의 요소를 출력\n");
	printf("TOP에 저장된 요소: %d\n", peek(S));

	printf("\n(4) 스택에서 요소 삭제\n");
	if (peek(S) != ERROR) {//ERROR가 아닐때만(비어있지 않으면)
		i = peek(S);
		pop(S);
		printf("%d 삭제\n", i);
	}
	displayStack(S);

	printf("\n(5) 스택에서 요소 삭제\n");
	if (peek(S) != ERROR) {//ERROR가 아닐때만(비어있지 않으면)
		i = peek(S);
		pop(S);
		printf("%d 삭제\n", i);
	}
	displayStack(S);

	printf("\n(6) 스택에서 요소 삭제\n");	
	if (peek(S) != ERROR) {//ERROR가 아닐때만(비어있지 않으면)
		i = peek(S);
		pop(S);
		printf("%d 삭제\n", i);
	}
	displayStack(S);

	printf("\n(7) 스택에 1부터 10까지 자연수를 차례로 삽입\n");
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
	
	printf("\n(8) 스택 비우기\n");
	clear(S);
	displayStack(S);
	

	return 0;
}

