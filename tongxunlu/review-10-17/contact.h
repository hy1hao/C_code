#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <search.h>

#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDRESS 30

//#define MAX 1000
#define InitSpace 3
//不同编码中，一个中文占2-3个字节
enum OPTION
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	SHOW,
	SAVE
};

enum MODIFY
{
	EXIT,
	NAME,
	SEX,
	AGE,
	TELE,
	ADDR
};

typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char address[MAX_ADDRESS];
}PeoInfo;

typedef struct Contact
{
	PeoInfo* data;
	int size;
	int space;
}Contact;

void InitContact(Contact* ps);
void AddContact(Contact* ps);
void ShowContact(Contact* ps);
void DelContact(Contact* ps);
void SearchContact(Contact* ps);
void ModifyContact(Contact* ps);
void SortContact(Contact* ps);
void SaveContact(Contact* ps);
void DestroyContact(Contact* ps);
