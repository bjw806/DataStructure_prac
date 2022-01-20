#include <stdio.h>
#include <stdlib.h>
#include "PolyList.h"

polyList* initList() {
	polyList* PL = (polyList*)malloc(sizeof(polyList));
	PL->head = NULL;
	PL->last = NULL;
	return PL;
}

void appendTerm(polyList* PL, float coef, int exp) {

	// Fill your code


}

polyList* subPoly(polyList* A, polyList* B) {
	polyList* C = initList();
	Node* polyA = A->head;
	Node* polyB = B->head;
	int sub = 0;
	
	// Fill your code

	
	return C;
}

void displayPoly(polyList* PL) {
	Node* p = PL->head;
	for (; p; p = p->link) {
		if (p->coef > 0)
			printf("\t+");
		else
			printf("\t");
		printf("%.0fx^%d", p->coef, p->exp);
	}
	printf("\n");
}
