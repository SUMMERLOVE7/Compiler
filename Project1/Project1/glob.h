/*
glob.h - global variable for the project
programmer - ����� 1976336
*/

/*#pragma once*/
#define FILE_NAME "testdata.dat"
#define STsize 1000
#define HTsize 100

#define TRUE 1
#define FALSE 0

int nextid; //���� identifier�� ���� index
int nextfree; //ST���� ���� character�� ���Ե� ���� index
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

int length; // identifier�� ���̸� �����ϱ� ���� ����

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
