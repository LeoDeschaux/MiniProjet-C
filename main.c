/******************************************************************************
*  ASR => M2101                                                               *
*******************************************************************************
*                                                                             *
*  N° de Sujet : 2                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse d’adresses IP                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : Deschaux-Beaume-Léo                                          *
*                                                                             *
*  Nom-prénom2 : Ruiz-Nathan                                                  *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : main.c                                                    *
*                                                                             *
******************************************************************************/

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

#include <stdbool.h>

#define LG_MAX 15

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

char* getInput();
void clearBuffer();

int isAddressValid(char* input);

int main(int argc, const char** argv)
{
	//READ INPUT, ex: "192.168.1.13/24"
	
	char ip[50];
	scanf("%s", ip);
	printf("voici l'adresse : %s\n", ip);

	//CHECK IF INPUT IS VALID

	if (isAddressValid(&ip))
		printf("address is valid\n");
	
	//CONVERT INPUT INTO IP STRUCT
		//convert char to int

	//FIND IP CLASS (A,B,C) & public/private
	
	//FIND @network, @host

	//PRINT IP & save in file 

	return 0;
}

int isAddressValid(char* input)
{
	int i = 0;
	while (*(input + i) != '\0' && i < 20)
	{
		printf("%c", *(input + i));
		i++;
	}
	printf("\n");

	return 0;
}

char* getInput()
{
	char str[] = "123";
	return *str;
}

void clearBuffer()
{
	char c;
	c = getchar();
	
	while (c != '\n')
	{
		c = getchar();
	}
}