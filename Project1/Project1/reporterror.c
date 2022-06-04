/*
* reporterror.c
programmer - 1976336 �����
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern line(int);
extern yylex();

/*
yyerror() - error �Լ�
*/
yyerror(s)
char* s;
{

}

void printError(ERRORtypes err)
{
	switch (err)
	{
		case overst: //�����÷ο찡 �߻��� ���, ���������� ����ϰ� ���ݱ����� �ؽ����̺��� ����ϰ� ������ ����
			line(cLine);
			printf("Error\tOverflow\n");
			exit(0);
			break;
		case illchar: // ������ ���� �����ڸ� ����� ���
			line(cLine);
			printf("Error\tillegal Character\n");
			break;
		case illid:
			line(cLine);
			printf("Error\tillegal Identifier\n");
			break;
		case wrong_st: //wrong_St
			line(cLine);
			printf("Error\twrong statement\n");
			break;
		case wrong_funcdef: //wrong_funcdef
			line(cLine);
			printf("Error\twrong function definition\n");
			break;
		case nosemi: //nosemi
			line(cLine);
			printf("Error\tno semicolon\n");
			break;
		case nobrace: //no brace
			line(cLine);
			printf("Error\tno brace\n");
			break;
		case nobracket: //no bracket
			line(cLine);
			printf("Error\tno bracket\n");
			break;
	}
	cErrors++;
	//err = noerror;
}