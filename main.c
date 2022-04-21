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

#define FILE_NAME "testdata.dat"

extern int yylex();
extern char* yytext;
void printtoken(tn);
char input;
int cLine = 1; //�� �ѹ�
char errStr[1000] = ""; // ��ȿ���� ���� identifier�� ������ ���� �迭

char seperators[] = " .,;:?!\t\n";

// PrintHeading	- ��� �κ� �ܼ� ��� �Լ�
void PrintHeading() {
	printf("\n\n");
	printf("-------------        ------------		------------		-----------\n");
	printf(" Line number          Token type		  ST-index		     Token\n");
	printf("-------------        ------------		------------		-----------\n");
	printf("\n");
}

//Initialize - �Է¹��� txt������ �� ���ھ� ����
void initialize() {
    //fp = fopen_s(&fp, FILE_NAME, "r");
    fopen_s(&fp, FILE_NAME, "r");
    if (fp == NULL) printf("����");
    input = fgetc(fp);
}

//isSeperator - seperator�� �� ���ڷ� �Էµ� letter�� ���������� Ȯ����.
int isSeperator(char c) {
    int i;
    int sep_len;

    //�����ڸ� ������ char�迭�� ����
    sep_len = strlen(seperators);

    //�ٹٲ� ���� �Ǻ�
    if (c == seperators[sep_len - 1]) {
        cLine++;
        printf("        %d      LINE CHANGE\n", cLine);
        return 2; //�ٹٲ޹����̴�
    }

    //�ش� ���� ��ŭ �ݺ��Ͽ�, �迭 ���� �����ϴ� ���
    for (i = 0; i < sep_len-1; i++) {
        if (c == seperators[i]) return 1; // �������̴�
    }

    return 0; // �������� �ʴ� ��� �����ڰ� �ƴ�
}

//void PrintHStable();

void PrintError(ERRORtypes err) {
    printf("        %d      ", cLine);

    switch (err) {
    case overst: //�����÷ο찡 �߻��� ���, ���������� ����ϰ� ���ݱ����� �ؽ����̺��� ����ϰ� ������ ����
        printf("   ...Error... OVERFLOW ");
        //PrintHStable();
        exit(0);
        break;
    case illsp: // ������ ���� �����ڸ� ����� ���
        printf("   ...Error...   %c is illegal seperator \n", input);
        break;
    case illid:
        printf("   ...Error...    ");
        //�����̰� �����ε��� ������ ���
        while (input != EOF && (isLetter(input) || isDigit(input))) {
            printf("%c", input);
            input = fgetc(fp);
        }
        printf("    start with digit \n");
        break;
    case overlength:
        printf("   ...Error...   too long identifier ");
        break;
    }

}

/* PrintHStable - Prints the hash table write out the hashcode and the list of identifiers
associated with each hashcode, but only for non-empty lists.
Print out the number of characters used up in ST. */
void PrintHStable() {
    int i, j;
    HTpointer here;

    int check[HTsize] = { 0 }; //�̹� �ش� ���ؽ��� Hash Table�� � ���� �ִ��� �Ǻ��ϱ� ���� �迭

    printf("\n\n\n\n <  Hash Table  > \n\n");
    for (i = 0; i < HTsize; i++) {
        if (HT[i] != NULL) {
            printf("    Hash Code %4d : ", i);
            check[i] = 1;
        }

        for (here = HT[i]; here != NULL; here = here->next) {
            j = here->index;

            while (ST[j] != '\0' && j < STsize) {
                printf("%c", ST[j++]);
            }

            if (check[i] == 1) {
                check[i]++;
                printf("    ");
            }
        }
        if (check[i] >= 1) printf("\n"); //�ٸ� �ε����� ���� ����ġ�� ���� ���� �ε��� ��ġ���� ��ũ�帮��Ʈ�� �̾����ٸ� �� �ٿ� ���.
    }
    printf("\n\n ***** %5d characters are used in the string table     \n ", nextfree);

}


/* Skip Seperators -
*       skip over strings of spaces, tabs, newlines, .,; : ? !
*       if illegal seperators, print out error message
*/
void SkipSeperators() {

    // \ !(a||b) �� !a && !b : ��, a,b��� �ƴϾ��
    while (input != EOF && !(isLetter(input) || isDigit(input))) { //���ڵ� �ƴϰ� ���ڵ� �ƴϰ� ������ ���ڵ� �ƴ� ���
        if ((!isSeperator(input)) && (isSeperator(input) != 2)) { //�����ڰ� �ƴϸ�
            err = illsp; //���� X ���� X ������ X �� ����� errType : �ùٸ��� ���� ������
            PrintError(err); //���� ���
        }
        input = fgetc(fp); //���� ���ڸ� �о �ݺ�
    }
    //���� or �����̸�, while loop Ż��
}

/* ReadID-
* Read identifiers from the input file the string table ST  directly into ST(append it to the previous identifier).
* An identifier is a string of letter ans digits, starting with a letter.
* If first letter is digit, print out error message.
* */
//txt�� ���� �ϳ��� word�� ST�� �ű�� �Լ�
void ReadID() {
    HTpointer here;
    int j;
    //nextid : ���ڰ� �����ϴ� �ε���
    //nextfree : letter�� ���� ST�� index�� ������ ++�Ǳ� ������ �� ������ word �ٷ� ���� ��ĭ�� ����Ŵ
    nextid = nextfree;

    if (isDigit(input)) { //������ ��� ���ڷ� �����ϴ� ���ڴ� ����
        err = illid; // ���� Ÿ�� ����
        PrintError(err);
    }

    else { // ������ ��� ( ��, �ܾ��� ù�����̸鼭 ���ڷ� �����ϴ� ���)

     //���� if - else ������ word�� ù ���ڰ� "����"��� ���Ǳ��� ����
     //(ù���ڰ� �ƴϸ� ���ڵ� �����ϱ⶧���� word�� �ϼ���Ű�� ���� ������(������ ���� ��������) ���� �������� while)
        while (input != EOF && (isLetter(input) || isDigit(input))) {

            //ST ���̺��� nextfree index�� ���ڸ� ���� ->  STsize�� �ʰ��ؼ� ���� ���� ����
            if (nextfree == STsize) { //STsize�� �ʰ��ؼ� ���� ���� ����
                err = overst; // �����÷ο� ����
                PrintError(err);
                //overflow�� PrintError���� exit
            }
            //���� �÷ο츸 �ƴϸ�, ST�� �Է¹��� input�� �־���
            ST[nextfree++] = input; //ST�� �־���.
            input = fgetc(fp);  //���� letter�� �о ������(�ҹ������� ����)�� ���ö� ���� �ݺ�
        }
        //�����ڰ� �����ϱ� �������� �� word�� ���ھ� �о�ͼ� ST�� �����ص�
    }
}

/*ComputeHS - Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT */
void ComputeHS(int nid, int nfree) { //nid : word�� ù ���� index , nfree : word�� ������ letter + 1 index(���������)
    int code, i;
    code = 0; //word �ƽ�Ű�ڵ��� ���� ������ ����
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i]; //�ƽ�Ű �ڵ� ��
        hashcode = code % HTsize; // �ƽ�Ű�ڵ��� mod �ؽ����̺������ -> hashcode
    }
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


/*
ADDHT
Add a new identifier to the hash table.
If list head ht[hashcode] is null, simply add a list element with
starting index of the identifier in ST.
IF list head is not a null, it adds a new idetifier to the head of the chain
*/
void ADDHT(int hscode) {
    HTpointer ptr;

    ptr = (HTpointer)malloc(sizeof(ptr));
    ptr->index = nextid;
    ptr->next = HT[hscode];
    HT[hscode] = ptr;
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
    PrintHeading(); // header������
    initialize(); //�о���� txt���Ͽ��� "one letter"�� "input"������ ����
    HTpointer here; //////////
    int j;//////////
    //input ������ �� ���ڰ� ������ ���ڰ� �ƴ� ���� ����
    //��, ������ ������ �дµ��� ����
    while (input != EOF) {

        err = noerror;//����Ʈ�� "noerror:������ �ƴ�"

        //word�� ó���� ����/������ �� ���� �ݺ���
        SkipSeperators(); //word�� ó���� ������ -> skip , �߸��� ������ -> err���

        //ReadID�� ���ڷ� �� �� �ִ� input�� ����/���� ��
        ReadID(); //������(�ҹ� ������ ����)�� �����ϱ� �� ���� (start with ������)����+���ڷ� �̷���� word�� ST���̺� ����

        printf("        %d      ", cLine);

        // ST�� �־�� word�� HT�� ��ġ�ϴ� �ڵ�
        // illid error�� ��� ST���� ���� �������Ƿ� �����ؼ��� �ȵ�
        if (input != EOF && err != illid) {

            //nextfree�� ���� ���� �Ŀ� ++�ǹǷ�, ++�� ���Ŀ� �ѹ��� overflow�˻縦 �������� �ʾұ⿡ �ѹ��� �ǽ�
            if (nextfree == STsize) {
                err = overst;
                PrintError(err); //overflow�� �Ǹ� �״�� ������
            }

            //�ϳ��� word�� �Է��ϸ� �ڵ����� ������ ��������
            ST[nextfree++] = '\0'; //�� ��� ��

            //nextid : word�� ù ���� index , nextfree : word�� ������ letter + 1 index(���������)
            ComputeHS(nextid, nextfree); //�Է� word�� hashcode : hashtable�� ����� index ���
            LookupHS(nextid, hashcode);

            if (nextfree - nextid - 1 > 12) { //�ܾ 12���� �ʰ��ϴ� ���
                err = overlength;
                PrintError(err);
                printf("\n");
            }
            else if (!found && nextfree - nextid - 1 <= 12) {//FALSE��, �������� �����Ƿ� �־��ٰ� ǥ��& 12���� ������ ���
                printf("   %10d	      ", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                //printf("	     (entered)\n");
                printf("\n");
                ADDHT(hashcode);
            }
            else {//TRUE��, -> �̹� �����ϴ� �� �̶�� ǥ�� (��������)
                printf("   %10d	     ", sameid); //�̹� �����Ƿ� �̹� �����ϴ� ���� index�� �����
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                //printf("	     (already existed)\n");
                printf("\n");
                nextfree = nextid;
            }
        }
    }
    //PrintHStable();
}