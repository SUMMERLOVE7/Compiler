/*
 2022.04.24
 1976336 장민지
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
int cLine = 1; //줄 넘버
char errStr[1000] = ""; // 유효하지 않은 identifier를 저장할 문자 배열

char seperators[] = " .,;:?!\t\n";

// PrintHeading	- 헤더 부분 단순 출력 함수
void PrintHeading() {
	printf("\n\n");
	printf("-------------        ------------		------------		-----------\n");
	printf(" Line number          Token type		  ST-index		     Token\n");
	printf("-------------        ------------		------------		-----------\n");
	printf("\n");
}

//Initialize - 입력받은 txt파일을 한 문자씩 읽음
void initialize() {
    //fp = fopen_s(&fp, FILE_NAME, "r");
    fopen_s(&fp, FILE_NAME, "r");
    if (fp == NULL) printf("실패");
    input = fgetc(fp);
}

//isSeperator - seperator가 한 글자로 입력된 letter가 구분자인지 확인함.
int isSeperator(char c) {
    int i;
    int sep_len;

    //구분자를 저장한 char배열의 길이
    sep_len = strlen(seperators);

    //줄바꿈 문자 판별
    if (c == seperators[sep_len - 1]) {
        cLine++;
        printf("        %d      LINE CHANGE\n", cLine);
        return 2; //줄바꿈문자이다
    }

    //해당 길이 만큼 반복하여, 배열 내에 존재하는 경우
    for (i = 0; i < sep_len-1; i++) {
        if (c == seperators[i]) return 1; // 구분자이다
    }

    return 0; // 존재하지 않는 경우 구분자가 아님
}

//void PrintHStable();

void PrintError(ERRORtypes err) {
    printf("        %d      ", cLine);

    switch (err) {
    case overst: //오버플로우가 발생한 경우, 오류문구를 출력하고 지금까지의 해시테이블을 출력하고 완전히 종료
        printf("   ...Error... OVERFLOW ");
        //PrintHStable();
        exit(0);
        break;
    case illsp: // 허용되지 않은 구분자를 사용한 경우
        printf("   ...Error...   %c is illegal seperator \n", input);
        break;
    case illid:
        printf("   ...Error...    ");
        //숫자이고 문자인데도 오류인 경우
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

    int check[HTsize] = { 0 }; //이미 해당 인텍스의 Hash Table에 어떤 값이 있는지 판별하기 위한 배열

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
        if (check[i] >= 1) printf("\n"); //다른 인덱스일 때만 엔터치고 만약 같은 인덱스 위치에서 링크드리스트로 이어진다면 한 줄에 출력.
    }
    printf("\n\n ***** %5d characters are used in the string table     \n ", nextfree);

}


/* Skip Seperators -
*       skip over strings of spaces, tabs, newlines, .,; : ? !
*       if illegal seperators, print out error message
*/
void SkipSeperators() {

    // \ !(a||b) 는 !a && !b : 즉, a,b모두 아니어야
    while (input != EOF && !(isLetter(input) || isDigit(input))) { //문자도 아니고 숫자도 아니고 마지막 글자도 아닌 경우
        if ((!isSeperator(input)) && (isSeperator(input) != 2)) { //구분자가 아니면
            err = illsp; //문자 X 숫자 X 구분자 X 인 경우의 errType : 올바르지 못한 구분자
            PrintError(err); //에러 출력
        }
        input = fgetc(fp); //다음 글자를 읽어서 반복
    }
    //문자 or 숫자이면, while loop 탈출
}

/* ReadID-
* Read identifiers from the input file the string table ST  directly into ST(append it to the previous identifier).
* An identifier is a string of letter ans digits, starting with a letter.
* If first letter is digit, print out error message.
* */
//txt에 적힌 하나의 word를 ST로 옮기는 함수
void ReadID() {
    HTpointer here;
    int j;
    //nextid : 문자가 시작하는 인덱스
    //nextfree : letter를 넣을 ST의 index를 넣으면 ++되기 때문에 다 넣으면 word 바로 다음 빈칸을 가리킴
    nextid = nextfree;

    if (isDigit(input)) { //숫자인 경우 숫자로 시작하는 문자는 에러
        err = illid; // 에러 타입 지정
        PrintError(err);
    }

    else { // 문자인 경우 ( 즉, 단어의 첫글자이면서 문자로 시작하는 경우)

     //위의 if - else 문으로 word의 첫 글자가 "문자"라는 조건까지 만족
     //(첫글자가 아니면 숫자도 가능하기때문에 word를 완성시키기 위해 구분자(허용되지 않은 구분포함) 등장 이전까지 while)
        while (input != EOF && (isLetter(input) || isDigit(input))) {

            //ST 테이블의 nextfree index에 글자를 삽입 ->  STsize를 초과해서 넣을 수는 없음
            if (nextfree == STsize) { //STsize를 초과해서 넣을 수는 없음
                err = overst; // 오버플로우 에러
                PrintError(err);
                //overflow면 PrintError에서 exit
            }
            //오버 플로우만 아니면, ST에 입력받은 input을 넣어줌
            ST[nextfree++] = input; //ST에 넣어줌.
            input = fgetc(fp);  //다음 letter를 읽어서 구분자(불법구분자 포함)이 나올때 까지 반복
        }
        //구분자가 등장하기 이전까지 한 word를 한자씩 읽어와서 ST에 저장해둠
    }
}

/*ComputeHS - Compute the hash code of identifier by summing the ordinal values of its
characters and then taking the sum modulo the size of HT */
void ComputeHS(int nid, int nfree) { //nid : word의 첫 시작 index , nfree : word의 마지막 letter + 1 index(공백저장됨)
    int code, i;
    code = 0; //word 아스키코드의 합을 저장할 변수
    for (i = nid; i < nfree - 1; i++) {
        code += (int)ST[i]; //아스키 코드 합
        hashcode = code % HTsize; // 아스키코드합 mod 해시테이블사이즈 -> hashcode
    }
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
    PrintHeading(); // header프린팅
    initialize(); //읽어들일 txt파일에서 "one letter"를 "input"변수에 넣음
    HTpointer here; //////////
    int j;//////////
    //input 변수에 들어간 글자가 마지막 글자가 아닌 동안 지속
    //즉, 파일을 끝까지 읽는동안 지속
    while (input != EOF) {

        err = noerror;//디폴트로 "noerror:에러가 아님"

        //word의 처음이 숫자/문자일 때 까지 반복함
        SkipSeperators(); //word의 처음이 구분자 -> skip , 잘못된 구분자 -> err출력

        //ReadID에 인자로 들어갈 수 있는 input은 문자/숫자 뿐
        ReadID(); //구분자(불법 구분자 포함)이 등장하기 전 까지 (start with 문자인)문자+숫자로 이루어진 word를 ST테이블에 저장

        printf("        %d      ", cLine);

        // ST에 넣어둔 word를 HT에 배치하는 코드
        // illid error의 경우 ST에도 들어가지 못했으므로 실행해서는 안됨
        if (input != EOF && err != illid) {

            //nextfree는 값을 넣은 후에 ++되므로, ++된 이후에 한번도 overflow검사를 진행하지 않았기에 한번더 실시
            if (nextfree == STsize) {
                err = overst;
                PrintError(err); //overflow가 되면 그대로 종료임
            }

            //하나의 word를 입력하면 자동으로 공백을 저장해줌
            ST[nextfree++] = '\0'; //한 덩어리 끝

            //nextid : word의 첫 시작 index , nextfree : word의 마지막 letter + 1 index(공백저장됨)
            ComputeHS(nextid, nextfree); //입력 word의 hashcode : hashtable상에 저장될 index 계산
            LookupHS(nextid, hashcode);

            if (nextfree - nextid - 1 > 12) { //단어가 12글자 초과하는 경우
                err = overlength;
                PrintError(err);
                printf("\n");
            }
            else if (!found && nextfree - nextid - 1 <= 12) {//FALSE면, 존재하지 않으므로 넣었다고 표시& 12글자 이하인 경우
                printf("   %10d	      ", nextid);
                for (i = nextid; i < nextfree - 1; i++)
                    printf("%c", ST[i]);
                //printf("	     (entered)\n");
                printf("\n");
                ADDHT(hashcode);
            }
            else {//TRUE면, -> 이미 존재하는 것 이라고 표시 (넣지않음)
                printf("   %10d	     ", sameid); //이미 있으므로 이미 존재하는 것의 index를 출력함
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