#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#include "tn.h"
#include "glob.h"
#include "symboltable.c"


extern int yylex();
extern char* yytext;

char input;
int cLine = 1; //줄 넘버
enum tokentypes tn;

void PrintError(ERRORtypes err) {

    switch (err) {
    case overst: //오버플로우가 발생한 경우, 오류문구를 출력하고 지금까지의 해시테이블을 출력하고 완전히 종료
        printf("        ...Error... OVERFLOW \n");
        exit(0);
        break;
    case illsp: // 허용되지 않은 구분자를 사용한 경우
        printf("     %d      ", cLine);

        printf("        ...Error...   %c is illegal seperator \n", input);
        break;
    case illid:
        printf("         ...Error...    ");
        printf("%s  ", yytext);
        printf("    illegal identifier\n");
        break;
    case overlength:
        printf("     %d      ", cLine);
        printf("         ...Error...   too long identifier \n");
        break;
    }

}

/*
ComputeHS - Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT
*/
void ComputeHS(int nid, int nfree)
{
    int sum = 0;
    int k;
    for (k = nid; k < nfree; k++)
        sum = sum + ST[k];
    hashcode = sum % HTsize;
}

/*
LookupHS
For each indentifier, Look it up in the hashtable for previous occurrence of the identifier.
If find a match, set the found flag as true. Other wise false.
If find a match, save the starting index of ST in same id
*/
void LookupHS(int nid, int hscode) {
    HTpointer here; //HTentry를 가리키는 포인터
    int i, j;
    found = FALSE; //이미 HT에 들어간 문자열인 경우 TRUE 그렇지 아니면 FALSE

    //새로운 word가 hashtable에 저장되고자 하는 index(위치)가 비어있지 않으면,
    if (HT[hscode] != NULL) {
        here = HT[hscode]; // HT[hscode] 인덱스위치에 존재하는 HTpointer로 만듬

        //일단 HT내에서 같은 인덱스를 가진다는건 같은 hscode 를 가지기 때문에 이미 들어간 단어가 존재할 수도
        while (here != NULL && found == FALSE) {
            found = TRUE; //이미 존재하는 단어라고 가정해버림
            i = here->index; //HT[hscode] 에서 index 부분에 적힌 정수 ( 해당 HT index상에 존재하는 word의 첫 글자)
            j = nid;//word의 시작부분의 index(지금들어갈 단어의 첫 인덱스 )
            sameid = i;

            //HT의 해당 hscode에 index상에 저장된 단어가 이미있는 단어인지 검사해보려고 돌림
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {//이번에 들어온 단어가 이미 있는 단어라고 가정하고 한글자씩 같은지 비

                if (ST[i] == ST[j]) {
                    i++;
                    j++;
                }
                else {
                    found = FALSE; //한자한자 검사하면서 다른단어가 나오면 FALSE로 만들기 -> false가 되면 while이 끝남           
                }
            }
            here = here->next; //연결리스트를 이용해 다음 연결리스트에 저장된 word와 겹치는지 검사하기위해 다음으로 넘김
        }
    }
}

void PrintTokentypes()
{
    switch (tn) {
    case TLBRACE:	printf("        TLBRACE		%22s\n", yytext); break;
    case TRBRACE:	printf("        TRBRACE		%22s\n", yytext); break;
    case TLBRACKET:	printf("        TLBRACKET		%22s\n", yytext); break;
    case TRBRACKET:	printf("        TRBRACKET		%22s\n", yytext); break;
    case TCONST:	printf("        TCONST		%22s\n", yytext); break;
    case TELSE:		printf("        TELSE		%22s\n", yytext); break;
    case TIF:		printf("        TIF			%22s\n", yytext); break;
    case TINT:		printf("        TINT		%22s\n", yytext); break;
    case TRETURN:	printf("        TRETURN		    %22s\n", yytext); break;
    case TVOID:		printf("        TVOID		   %22s\n", yytext); break;
    case TWHILE:		printf("        TWHILE		%22s\n", yytext); break;
    case TSTAR:		printf("        TSTAR		%22s\n", yytext); break;
    case TSLASH:		printf("        TSLASH			%22s\n", yytext); break;
    case TEQUAL:	printf("        TEQUAL		%22s\n", yytext); break;
    case TNOTEQU:	printf("        TNOTEQU		%22s\n", yytext); break;
    case TLESS:		printf("        TLESS			%22s\n", yytext); break;
    case TGREAT:		printf("        TGREAT		%22s\n", yytext); break;
    case TNOT:		printf("        TNOT			%22s\n", yytext); break;
    case TAND:		printf("        TAND			%22s\n", yytext); break;
    case TOR:		printf("        TOR			%22s\n", yytext); break;
    case TINC:		printf("        TINC			%22s\n", yytext); break;
    case TDEC:		printf("        TDEC			%22s\n", yytext); break;
    case TADDASSIGN:	printf("        TADDASSIGN	        %22s\n", yytext); break;
    case TSUBASSIGN:	printf("        TSUBASSIGN		%22s\n", yytext); break;
    case TMULASSIGN:	printf("        TMULASSIGN	    %22s\n", yytext); break;
    case TDIVASSIGN:	printf("        TDIVASSIGN		%22s\n", yytext); break;
    case TMODASSIGN:	printf("        TMODASSIGN	    %22s\n", yytext); break;
    case TIDENT:		printf("        TIDENT		%10d        %22s\n", nextid, yytext); break;
    case TNUMBER:	printf("        TNUMBER		%22s\n", yytext); break;
    case TMINUS:        printf("        TMINUS      %22s\n", yytext); break;
    case TASSIGN:	printf("        TASSIGN		%22s\n", yytext); break;
    case TSEMI:		printf("        TSEMI			%22s\n", yytext); break;
    case TLPAREN:	printf("        TLAPAREN    	%22s\n", yytext); break;
    case TRPAREN:	printf("        TRPAREN		%22s\n", yytext); break;
    case TCOMMA:	printf("        TCOMMA		%22s\n", yytext); break;
    case TFLOAT:		printf("         TFLOAT		%22s\n", yytext); break;
    case TNEWLINE:      cLine++;  break;
    case TERROR:     break;
    }
}



nextfree = 0;
int SymbolTable()
{
    if (nextfree == STsize) {
        err = overst;
        PrintError(err);
    }
    if (strlen(yytext) > 12) {
        err = overlength;
        PrintError(err);
        return 1;
    }

    nextid = nextfree;

    for (j = 0; yytext[j] != '\0'; j++) {
        if (nextfree == STsize) {
            err = overst;
            PrintError(err);
        }
        ST[nextfree] = yytext[j];
        nextfree++;
    }
    if (tn != TNEWLINE) printf("     %d      ", cLine);
    if (tn == TERROR) {
        err = illid; PrintError(err);
    }
    ComputeHS(nextid, nextfree); //입력 word의 hashcode : hashtable상에 저장될 index 계산
    LookupHS(nextid, hashcode);

    return 0;
}


/*
MAIN
    Read the identifier from the file directly into ST.
    Compute its hashcode.
    Look up the identifier in hashtable HT[hashcode]
    If matched, delete the identifier from ST and print ST-index of the matching identifier.
    If not matched, add a new element to the list, pointing to new identifier.
    Print the identifier, its index in ST, and whether it was entered or present.
    Print out the hashtable, and number of characters used up in ST
*/
int main() {
    int i;


    printf("\n\n");
    printf("-------------        ------------	  ------------		-----------\n");
    printf(" Line number          Token type	 ST-index		Token\n");
    printf("-------------        ------------	  ------------		-----------\n");
    printf("\n");

    while ((tn = yylex()) != TEOF) {
        if(SymbolTable() != 1) PrintTokentypes();
    }
}
