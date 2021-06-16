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

//
#define TAILLE_ADRESSE 18

typedef struct IPv4 {
	int valeur1;
	int valeur2;
	int valeur3;
	int valeur4;
	int masque;
}IPv4;

void constrIP(char adresse[], IPv4* ip);
char trouverClasse(IPv4 ip);
bool isAddressPrivate(IPv4 ip);


char* getInput();
void clearBuffer();

int isAddressValid(char* input);

int main(int argc, const char** argv)
{
	while (true)
	{
		//GREET USER
		printf("Veuillez enter une adress ip avec masque : ");

		//READ INPUT, ex: "192.168.1.13/24"
		char input[50]; //= "192.168.1.9/24";
		scanf("%s", input);
		printf("\n");
		printf("L'adresse que vous venez de rentrer : %s\n", input);
		
		//CHECK IF INPUT IS VALID
		if (isAddressValid(&input))
			printf("L'adress est valide\n");
		else
		{
			printf("L'adress n'est pas valide..\n");
			printf("-------------------------------------------\n");
			continue;
		}

		//CONVERT INPUT INTO IP STRUCT
		IPv4 ip;
		constrIP(input, &ip);

		printf("\n");
		printf("valeur1 = %d\n", ip.valeur1);
		printf("valeur2 = %d\n", ip.valeur2);
		printf("valeur3 = %d\n", ip.valeur3);
		printf("valeur4 = %d\n", ip.valeur4);
		printf("masque =  %d\n", ip.masque);

		//FIND IP CLASS (A,B,C)
		char classe = trouverClasse(ip);

		printf("\n");
		printf("Classe : %c\n", classe);

		//FIND IP public/private
		char type[10] = ""; 
		if (isAddressPrivate(ip))
			strncat(type, "private");
		else
			strncat(type, "public");

		printf("Type : %s\n", type);

		//FIND @network, @host

		//AFFICHAGE

		//SAUVEGARDER VERS FICHIER
		FILE* fptr = fopen("ip.txt", "a");
		if (fptr == NULL)
		{
			printf("Could not open file");
			return 0;
		}
		fprintf(fptr, "%s\n", input);
		
		fclose(fptr);
		
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
	if (false)
	{
		printf("----------------------- \n");
		printf("Resultats\n");
		printf("VALEUR: %s\n", valeurs[0]);
		printf("VALEUR: %s\n", valeurs[1]);
		printf("VALEUR: %s\n", valeurs[2]);
		printf("VALEUR: %s\n", valeurs[3]);
		printf("MASK: %s\n", mask);
		printf("---------------- \n\n");
	}

	return isValid;
}

void constrIP(char input[], IPv4* ip) {
	char adresse[18] = "";
	strncat(adresse, input);

	char sep[] = "./";
	char* p = strtok(adresse, sep);
	ip->valeur1 = atoi(p);
	p = strtok(NULL, sep);
	ip->valeur2 = atoi(p);
	p = strtok(NULL, sep);
	ip->valeur3 = atoi(p);
	p = strtok(NULL, sep);
	ip->valeur4 = atoi(p);
	p = strtok(NULL, sep);
	ip->masque = atoi(p);
}

char trouverClasse(IPv4 ip) {
	signed char classe;
	if (ip.valeur1 >= 0 && ip.valeur1 < 127)
		classe = 'A';
	if (ip.valeur1 >= 128 && ip.valeur1 < 192)
		classe = 'B';
	if (ip.valeur1 >= 192 && ip.valeur1 < 224)
		classe = 'C';
	if (ip.valeur1 >= 224 && ip.valeur1 < 240)
		classe = 'D';
	if (ip.valeur1 >= 240 && ip.valeur1 < 256)
		classe = 'E';
	if (ip.valeur1 >= 127 && ip.valeur1 < 128)
		classe = 'L';

	return classe;
}

bool isAddressPrivate(IPv4 ip) {
	bool a = false;
	if (ip.valeur1 == 10)
		a = true;
	if (ip.valeur1 == 172 && ip.valeur2 >= 16 && ip.valeur2 < 32)
		a = true;
	if (ip.valeur1 == 192 && ip.valeur2 == 168)
		a = true;

	return a;
}

