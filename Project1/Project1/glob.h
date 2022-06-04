/*
glob.h - global variable for the project
programmer - 장민지 1976336
*/

/*#pragma once*/
#define FILE_NAME "testdata.dat"
#define STsize 1000
#define HTsize 100

#define TRUE 1
#define FALSE 0

int nextid; //현재 identifier의 시작 index
int nextfree; //ST에서 다음 character가 삽입될 곳의 index
int hashcode;
int sameid;
int found;

enum errorTypes {
	noerror, illchar, illid, overst, overlength, wrong_st, wrong_funcdef, nosemi, nobrace, nobracket
};
typedef enum errorTypes ERRORtypes;
ERRORtypes err;

extern int cLine; //line number
int cErrors; //error count

int length; // identifier의 길이를 저장하기 위한 변수

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; 	 //index of identifier in ST
	int type;
	HTpointer next;  //pointer to next identifier
} HTentry;

HTpointer HT[HTsize];
char ST[STsize];

HTpointer look_id, look_tmp;

int i, j;
enum tokentypes tn;
