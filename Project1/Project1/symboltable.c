/*
symboltable.c
programmer - 장민지 1976336
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tn.h"
#include "glob.h"

extern int yylex();
extern char* yytext;

char input;
int cLine = 1; //줄 넘버

/*
ComputeHS - Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT
*/
void ComputeHS(int nid, int nfree)
{
    int i, func = 0;

    for(i=nid; i<nfree-1; i++){
	func += (int)ST[nid++];
    }
    hashcode = func % HTsize;

    /*int sum = 0;
    int k;
    for (k = nid; k < nfree; k++)
        sum = sum + ST[k];
    hashcode = sum % HTsize;
    */
}

/*
LookupHS
For each indentifier, Look it up in the hashtable for previous occurrence of the identifier.
If find a match, set the found flag as true. Other wise false.
If find a match, save the starting index of ST in same id
*/
void LookupHS(int nid, int hscode) {
    HTpointer here; //HTentry를 가리키는 포인터(현재 노드를 가리키는 포인터)
    int i, j, k;
    int htid = 0; 
    int stid = 0;
    found = FALSE; //이미 HT에 들어간 문자열인 경우 TRUE 그렇지 아니면 FALSE

    //새로운 word가 hashtable에 저장되고자 하는 index(위치)가 비어있지 않으면,
    if (HT[hscode] != NULL) {
        here = HT[hscode]; // HT[hscode] 인덱스위치에 존재하는 HTpointer로 만듦(hscode에 해당하는 노드가 있으면 here가 그 노드를 가리킴)

        //일단 HT내에서 같은 인덱스를 가진다는건 같은 hscode 를 가지기 때문에 이미 들어간 단어가 존재할 수도
        while (here != NULL && found == FALSE) {
            found = TRUE; //이미 존재하는 단어라고 가정해버림
            i = here->index; //HT[hscode] 에서 index 부분에 적힌 정수 ( 해당 HT index상에 존재하는 word의 첫 글자)
            j = nid;//word의 시작부분의 index(지금들어갈 단어의 첫 인덱스 )
            sameid = i;

	        for(k = i; ST[k] != '\0'; k++) 
		        htid++;
	        for(k = j; ST[k] != '\0'; k++)
		        stid++;
	        if(htid != stid) found = FALSE;

            //HT의 해당 hscode에 index상에 저장된 단어가 이미있는 단어인지 검사해보려고 돌림
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {//이번에 들어온 단어가 이미 있는 단어라고 가정하고 한글자씩 같은지 비

                if (ST[i] == ST[j]) {
                    i++;       //같은 character이면 그 다음 문자를 비교
                    j++;
                }
                else {
                    found = FALSE; //한글자씩 검사하면서 같은 character가 아니면 찾지 않은 것으로 간주해 FALSE로 만들기 -> false가 되면 while이 끝남.            
                }
            }
	    if(found == TRUE) return;
            here = here->next; //연결리스트를 이용해 다음 연결리스트에 저장된 word와 겹치는지 검사하기위해 다음 노드로 이동
        }
    }
}

// ADDHT	-	Add a new identifier to the hash table.
//			If list head ht[hashcode] is null, simply add a list element with
//			starting index of the identifier in ST.
//			IF list head is not a null , it adds a new identifier to the head of the chain ?
void ADDHT(int hscode)
{
    //HT에 추가되지 않은 identifier인 경우
    //index는 ST의 index, next는 null 인 새로운 HTEntry를 생성
    //기존 HT에 추가
    HTpointer tmp; //임시 포인터 변수

    if(HT[hscode] == NULL){	//이전에 생성된 노드가 없는 경우
    	tmp = (HTpointer)malloc(sizeof(struct HTentry));
		tmp->type = 0;
		tmp->next = NULL;
		HT[hscode] = tmp;
    		tmp->index = nextid;
    }
    else{	//이전에 생성된 노드가 있는 경우 해당 노드의 앞에 새로운 노드 삽입
		tmp = (HTpointer)malloc(sizeof(struct HTentry));
		tmp->type = 0;
		tmp->index = nextid;
    		tmp->next = HT[hscode];
    		HT[hscode] = tmp;
     }
     look_id = tmp;
}


/*
printHStable() - 해시테이블에 저장된 identifier들을 출력
*/
void PrintHStable()
{
	HTpointer here;
	int i, j;
	printf("\n\t[Hash Table  : Identifier Information] \n");
	printf("\n====================================================\n");

	for(i = 0; i< 100; i++){
		if(HT[i] != NULL){
			here = HT[i];
			do{
				printf("\tHashCode %4d : (", i );
				for(j=here->index; ST[j] != '\0'; j++) printf("%c", ST[j]);
				printf(" : ");
				switch(here->type){
					case 1 : printf("integer scalar variable)\n"); break;
					case 2 : printf("void scalar variable)\n"); break;
					case 3 : printf("array integer variable)\n"); break;
					case 4 : printf("function name)\n"); break;
					case 5 : printf("not defined identifier/function)\n"); break;
					default : printf("identifier about parse error)\n");
				}
				here = here->next;
			}while(here != NULL);
		}
	}
	printf("\n====================================================\n");
	printf("\t< %d characters are used in the string table >\n\t", nextfree-1);
}
