/*
glob.h - global variable for the project
programmer - 장민지
date - 2022.04.24
*/
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include "tn.h"

#define FILE_NAME "testdata.dat"
#define STsize 1000
#define HTsize 100

#define TRUE 1
#define FALSE 0

int nextid, nextfree;
int hashcode;
int sameid;
int found;

enum errorTypes {
    noerror, illsp, illid, overst, overlength
};
typedef enum errorTypes ERRORtypes;
ERRORtypes err;

extern int cLine;

int length; // identifier의 길이를 저장하기 위한 변수

typedef struct HTentry* HTpointer;
typedef struct HTentry {
	int index; 	 //index of identifier in ST
	HTpointer next;  //pointer to next identifier
} HTentry;

HTpointer HT[HTsize];
char ST[STsize];

int i, j;


FILE* fp; //to be a pointer to FILE

