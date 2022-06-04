%{
/*
scanner.l - lexical analyzer for the MiniC
Programmer - 장민지 1976336
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tn.h"
#include "glob.h"

extern ComputeHS(int nid, int nfree);
extern LookupHS(int nid, int nfree);
extern ADDHT(int hscode);
extern PrintHStable();
extern yyerror(char *s);

int i;
%}

%s CMT

%%
"const" 				return(TCONST);
"else" 					return(TELSE);
"if" 					return(TIF);
"int"					return(TINT);
"return"				return(TRETURN);
"void" 				return(TVOID);
"while" 				return(TWHILE);

"+" 				return(TPLUS);
"-" 				return(TMINUS);
"*" 				return(TMULTIPLY);
"/" 				return(TDIVIDE);
"%" 				return(TMOD);

"=" 				return(TASSIGN);
"+=" 				return(TADDASSIGN);
"-=" 				return(TSUBASSIGN);
"*=" 				return(TMULASSIGN);
"/=" 				return(TDIVASSIGN);
"%=" 				return(TMODASSIGN);

"!" 				return(TNOT);
"&&" 				return(TAND);
"||" 				return(TOR);

"==" 				return(TEQUAL);
"!="	 			return(TNOTEQU);
"<" 				return(TLESS);
">" 				return(TGREAT);
"<=" 				return(TLESSE);
">=" 				return(TGREATE);

"++" 				return(TINC);
"--" 				return(TDEC);

"(" 				return(TLPAREN);
")" 				return(TRPAREN);
"," 				return(TCOMMA);
"{"				return(TLBRACE);
"}"				return(TRBRACE);
"["				return(TLBRACKET);
"]"				return(TRBRACKET);
";" 				return(TSEMICOLON);
[0-9]+"."[0-9]+(e[+-]?[0-9]+)?		return(TFLOAT);

[A-Za-z_][A-Za-z0-9_]* 		{ 
					if(nextfree >= STsize){
						printf("\tError>> \tOVERFLOW\n");
						PrintHStable();
						exit(1);   
					}
					nextid=nextfree;
					nextfree += (yyleng+1);
					for(i=0; i<yyleng; i++) //identifier를 스트링테이블에 insert
						ST[nextid+i] = yytext[i];
					ComputeHS(nextid, nextfree);
					LookupHS(nextid, hashcode);

					if(!found){ //found==0 ->해시테이블에 ADD
						ADDHT(hashcode);
					}
					else{ //found!=0 ->스트링테이블에서 Delete
						for(i=nextid; i<nextfree-1; i++){
							ST[i] = '\0';
						}
						nextfree=nextid;
					}
					return(TIDENT);
				}
0|[1-9][0-9]*			return(TNUMBER);
[0-9]+[A-Za-z_][A-Za-z0-9_]+ 		{ err = illid; printError(err); return(TERROR); }

"//".*				;
"/*"([^*]|\*+[^*/])*\**"*/"		{
								for(i=0;i<yyleng;i++)
									if(yytext[i]=='\n') cLine++;}
[ \t]			 	;
"\n" 				{cLine++; }

. 				{ err = illchar; printError(err); return(TERROR); }
%%

int yywrap()
{
  return 1;
}