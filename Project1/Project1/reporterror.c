/*
* reporterror.c
programmer - 1976336 장민지
*/

#include <stdio.h>
#include <stdlib.h>
#include "tn.h"
#include "glob.h"
extern line(int);
extern yylex();

/*
yyerror() - error 함수
*/
yyerror(s)
char* s;
{

}

void printError(ERRORtypes err)
{
	switch (err)
	{
		case overst: //오버플로우가 발생한 경우, 오류문구를 출력하고 지금까지의 해시테이블을 출력하고 완전히 종료
			line(cLine);
			printf("Error\tOverflow\n");
			exit(0);
			break;
		case illchar: // 허용되지 않은 구분자를 사용한 경우
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