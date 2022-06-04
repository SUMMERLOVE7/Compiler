/*
symboltable.c
programmer - ����� 1976336
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tn.h"
#include "glob.h"

extern int yylex();
extern char* yytext;

char input;
int cLine = 1; //�� �ѹ�

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
    HTpointer here; //HTentry�� ����Ű�� ������(���� ��带 ����Ű�� ������)
    int i, j, k;
    int htid = 0; 
    int stid = 0;
    found = FALSE; //�̹� HT�� �� ���ڿ��� ��� TRUE �׷��� �ƴϸ� FALSE

    //���ο� word�� hashtable�� ����ǰ��� �ϴ� index(��ġ)�� ������� ������,
    if (HT[hscode] != NULL) {
        here = HT[hscode]; // HT[hscode] �ε�����ġ�� �����ϴ� HTpointer�� ����(hscode�� �ش��ϴ� ��尡 ������ here�� �� ��带 ����Ŵ)

        //�ϴ� HT������ ���� �ε����� �����ٴ°� ���� hscode �� ������ ������ �̹� �� �ܾ ������ ����
        while (here != NULL && found == FALSE) {
            found = TRUE; //�̹� �����ϴ� �ܾ��� �����ع���
            i = here->index; //HT[hscode] ���� index �κп� ���� ���� ( �ش� HT index�� �����ϴ� word�� ù ����)
            j = nid;//word�� ���ۺκ��� index(���ݵ� �ܾ��� ù �ε��� )
            sameid = i;

	        for(k = i; ST[k] != '\0'; k++) 
		        htid++;
	        for(k = j; ST[k] != '\0'; k++)
		        stid++;
	        if(htid != stid) found = FALSE;

            //HT�� �ش� hscode�� index�� ����� �ܾ �̹��ִ� �ܾ����� �˻��غ����� ����
            while (ST[i] != '\0' && ST[j] != '\0' && found == TRUE) {//�̹��� ���� �ܾ �̹� �ִ� �ܾ��� �����ϰ� �ѱ��ھ� ������ ��

                if (ST[i] == ST[j]) {
                    i++;       //���� character�̸� �� ���� ���ڸ� ��
                    j++;
                }
                else {
                    found = FALSE; //�ѱ��ھ� �˻��ϸ鼭 ���� character�� �ƴϸ� ã�� ���� ������ ������ FALSE�� ����� -> false�� �Ǹ� while�� ����.            
                }
            }
	    if(found == TRUE) return;
            here = here->next; //���Ḯ��Ʈ�� �̿��� ���� ���Ḯ��Ʈ�� ����� word�� ��ġ���� �˻��ϱ����� ���� ���� �̵�
        }
    }
}

// ADDHT	-	Add a new identifier to the hash table.
//			If list head ht[hashcode] is null, simply add a list element with
//			starting index of the identifier in ST.
//			IF list head is not a null , it adds a new identifier to the head of the chain ?
void ADDHT(int hscode)
{
    //HT�� �߰����� ���� identifier�� ���
    //index�� ST�� index, next�� null �� ���ο� HTEntry�� ����
    //���� HT�� �߰�
    HTpointer tmp; //�ӽ� ������ ����

    if(HT[hscode] == NULL){	//������ ������ ��尡 ���� ���
    	tmp = (HTpointer)malloc(sizeof(struct HTentry));
		tmp->type = 0;
		tmp->next = NULL;
		HT[hscode] = tmp;
    		tmp->index = nextid;
    }
    else{	//������ ������ ��尡 �ִ� ��� �ش� ����� �տ� ���ο� ��� ����
		tmp = (HTpointer)malloc(sizeof(struct HTentry));
		tmp->type = 0;
		tmp->index = nextid;
    		tmp->next = HT[hscode];
    		HT[hscode] = tmp;
     }
     look_id = tmp;
}


/*
printHStable() - �ؽ����̺� ����� identifier���� ���
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
