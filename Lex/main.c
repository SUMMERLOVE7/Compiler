/*
 2022.04.24
 1976336 �����
*/

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
int cLine = 1; //�� �ѹ�
enum tokentypes tn;

void PrintError(ERRORtypes err) {

    switch (err) {
    case overst: //�����÷ο찡 �߻��� ���, ���������� ����ϰ� ���ݱ����� �ؽ����̺��� ����ϰ� ������ ����
        printf("        ...Error... OVERFLOW \n");
        exit(0);
        break;
    case illsp: // ������ ���� �����ڸ� ����� ���
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
    HTpointer here; //HTentry�� ����Ű�� ������
    int i, j;
    found = FALSE; //�̹� HT�� �� ���ڿ��� ��� TRUE �׷��� �ƴϸ� FALSE

    //���ο� word�� hashtable�� ����ǰ��� �ϴ� index(��ġ)�� ������� ������,
    if (HT[hscode] != NULL) {
        here = HT[hscode]; // HT[hscode] �ε�����ġ�� �����ϴ� HTpointer�� ����

        //�ϴ� HT������ ���� �ε����� �����ٴ°� ���� hscode �� ������ ������ �̹� �� �ܾ ������ ����
        while (here != NULL && found == FALSE) {
            found = TRUE; //�̹� �����ϴ� �ܾ��� �����ع���
            i = here->index; //HT[hscode] ���� index �κп� ���� ���� ( �ش� HT index�� �����ϴ� word�� ù ����)
            j = nid;//word�� ���ۺκ��� index(���ݵ� �ܾ��� ù �ε��� )
            sameid = i;

            //HT�� �ش� hscode�� index�� ����� �ܾ �̹��ִ� �ܾ����� �˻��غ����� ����
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {//�̹��� ���� �ܾ �̹� �ִ� �ܾ��� �����ϰ� �ѱ��ھ� ������ ��

                if (ST[i] == ST[j]) {
                    i++;
                    j++;
                }
                else {
                    found = FALSE; //�������� �˻��ϸ鼭 �ٸ��ܾ ������ FALSE�� ����� -> false�� �Ǹ� while�� ����           
                }
            }
            here = here->next; //���Ḯ��Ʈ�� �̿��� ���� ���Ḯ��Ʈ�� ����� word�� ��ġ���� �˻��ϱ����� �������� �ѱ�
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
    ComputeHS(nextid, nextfree); //�Է� word�� hashcode : hashtable�� ����� index ���
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