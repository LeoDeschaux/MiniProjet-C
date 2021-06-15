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
	while (true)
	{
		//READ INPUT, ex: "192.168.1.13/24"
		char ip[50]; //= "192.168.1.9/24";
		scanf("%s", ip);
		printf("voici l'adresse : %s\n\n", ip);
		
		//CHECK IF INPUT IS VALID
		if (isAddressValid(&ip))
			printf("address is valid\n");
		else
			printf("adress n'est pas valide..\n");

		//CONVERT INPUT INTO IP STRUCT

		//FIND IP CLASS (A,B,C) & public/private

		//FIND @network, @host

		//PRINT IP & save in file 

		printf("-------------------------------------------\n");
	}

	printf("\n");

	return 0;
}

int isAddressValid(char* input)
{
	enum state { record_valeur, record_mask };
	enum state state = record_valeur;

	char valeurs[4][3 + 1] = {"", "xxx", "xxx", "xxx"};
	int valeurIndex = 0; 
	char mask[3] = "xx";

	int longueurValeur = 0;

	bool isValid = false;

	int i = 0;
	while (*(input + i) != '\0' && i < 20)
	{
		char currentChar = { *(input + i) };

		if (state == record_valeur)
		{
			if (isdigit(currentChar))
			{
				if (longueurValeur >= 3)
					return false;

				strncat(valeurs[valeurIndex], &currentChar, 1);
				longueurValeur++;
			}
			else if (currentChar == '.')
			{
				if (longueurValeur == 0)
					return false;

				if (valeurIndex < 3)
				{
					valeurIndex++;
					memset(valeurs[valeurIndex], 0, sizeof(valeurs[valeurIndex]));
					longueurValeur = 0;
				}
				else
					return false;
			}
			else if (valeurIndex == 3 && currentChar == '/')
			{
				state = record_mask;
				memset(mask, 0, sizeof(mask));
				longueurValeur = 0;
			}
			else
				return false;
		}
		
		else if (state == record_mask)
		{
			if (isdigit(currentChar))
			{
				if (longueurValeur >= 2)
					return false;

				strncat(mask, &currentChar, 1);
				longueurValeur++;
			}
			else
				return false;
		}
		
		i++;
	}

	//CHECK IF ALL FIELDS HAVE BEEN SET
	if (strcmp(valeurs[0], "xxx") == 0 ||
		strcmp(valeurs[1], "xxx") == 0 ||
		strcmp(valeurs[2], "xxx") == 0 ||
		strcmp(valeurs[3], "xxx") == 0 ||
		strcmp(mask, "xx") == 0)
	{
		return false;
	}

	//CHECK IF VALUES ARE VALID
	if (atoi(valeurs[0]) <= 255 &&
		atoi(valeurs[1]) <= 255 &&
		atoi(valeurs[2]) <= 255 &&
		atoi(valeurs[3]) <= 255 &&
		atoi(mask) <= 32)
	{
		isValid = true;
	}

	//DEBUG: PRINT @IP
	printf("----------------------- \n");
	printf("Resultats\n");
	printf("VALEUR: %s\n", valeurs[0]);
	printf("VALEUR: %s\n", valeurs[1]);
	printf("VALEUR: %s\n", valeurs[2]);
	printf("VALEUR: %s\n", valeurs[3]);
	printf("MASK: %s\n",   mask);
	printf("---------------- \n\n");

	return isValid;
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