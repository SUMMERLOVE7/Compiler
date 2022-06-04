/*
main.c - �� token�� ���� ��� ���� ����

Programmer - 1976336 �����
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"

extern int yyparse();
extern void PrintHStable();

void main()
{
	printf("\n\t[Error Report : Error Information]");
	printf("\n====================================================\n");

	cLine = 1;
	yyparse();

	if (cErrors == 0) printf("NO ERROR DETECTED");
	else printf("\n\t %d error(s) detected \n", cErrors);
	printf("\n====================================================\n");
	PrintHStable(); //identifier�� �� type�� print�ϴ� �Լ�
}
