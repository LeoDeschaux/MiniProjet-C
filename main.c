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
*  Nom-prénom1 : Ruiz-Nathan                                                  *
*                                                                             *
*  Nom-prénom2 : Deschaux-Beaume-Léo                                          *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : main.c                                                    *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
//#include <stdlib.h>
//#include <string.h>

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

void sauvegarderVersFichier(char* input);

void printIP(IPv4 ip);
void trouverType(IPv4 ip);

const char* octetDecimalEnOctetBinaire(int octetDecimal);
int octetBinaireEnOctetDecimal(char* octetBinaire);

IPv4 convertBinaryToIPv4(char binaryIP[]);

int isAddressValid(char* input);

int main(int argc, const char** argv)
{
	while (true)
	{
		//GREET USER
		printf("Veuillez entrer une adress ip avec masque : ");

		//READ INPUT, ex: "192.168.1.13/24"
		char input[50];
		scanf("%s", input);
		printf("\n");
		printf("L'adresse que vous venez de rentrer : %s\n", input);
		
		//CHECK IF INPUT IS VALID
		if (isAddressValid(&input))
			printf("L'adresse est valide\n");
		else
		{
			printf("L'adresse n'est pas valide..\n");
			printf("-------------------------------------------\n");
			continue;
		}

		//CONVERT INPUT INTO IP STRUCT
		IPv4 ip;
		constrIP(input, &ip);

		printf("\n");
		printIP(ip);

		//FIND TYPE
		printf("\n");
		trouverType(ip);

		/*
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
		*/

		//AFFICHAGE
		

		//SAUVEGARDER VERS FICHIER
		//sauvegarderVersFichier(input);
		
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

void sauvegarderVersFichier(char* input)
{
	FILE* fptr = fopen("ip.txt", "a");
	if (fptr == NULL)
	{
		printf("Could not open file");
		return 0;
	}
	fprintf(fptr, "%s\n", input);

	fclose(fptr);
}

void trouverType(IPv4 ip)
{
	//constrIP("192.168.1.10/24", &ip);

	//printf("IP : 192.168.1.10/24\n");

	//IPv4 = "192.168.1.10/24";
	//binary= 1100 0000.1010 1000.0000 0001.0000 1010/24
	//convert ip to binary
	char binaryIP[32 + 1] = "";
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur1));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur2));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur3));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur4));

	printf("IP Binaire     : %s\n", binaryIP);

	//mask = 255.255.255.0
	//binary = 1111 1111.1111 1111.1111 1111.0000 0000
	//convert mask to binary
	char binaryMask[32 + 1] = "";

	int i;
	for (i = 0; i < ip.masque; i++)
	{
		strncat(binaryMask, "1", 1);
	}
	for (int j = i; j < 32; j++)
	{
		strncat(binaryMask, "0", 1);
	}

	printf("Masque Binaire : %s\n", binaryMask);

	//##########################################################################

	//printf("Type : ");

	if (ip.valeur1 == 127 && ip.masque == 8 && ip.valeur4 != 0)
	{
		//LOCALHOST
		// 127.255.255.255 c'est local host ???

		printf("LOCALHOST\n");
	}

	//MULTICAST
	//de 224.0.0.0 à 239.255.255.255 (adresses de classe D)

	//NETWORK
	//et logique ip + mask, exemple "127.15.0.15" + "255.255.255.0" = "127.15.1.0"
	char binaryNetwork[32 + 1] = "";

	printf("et logique     : ");
	for (int i = 0; i < 32; i++)
	{
		char cIP = binaryIP[i];
		char cMask = binaryMask[i];

		if (atoi(&cIP) == 0 || atoi(&cMask) == 0)
		{
			strncat(binaryNetwork, "0", 1);
			printf("0");
		}
		else
		{
			strncat(binaryNetwork, "1", 1);
			printf("1");
		}
	}

	//Convert binary ip to IPv4
	IPv4 networkIP;
	networkIP = convertBinaryToIPv4(binaryNetwork);

	printf("\n\n");
	printf("ADRESSE RESEAU : \n");
	printIP(networkIP);

	//BROADCAST
	printf("\n");

	printf("invert BrdCast : ");
	char binaryReverseMask[32 + 1] = "";
	//faire un inverse
	for (int i = 0; i < 32; i++)
	{
		char cMask = binaryMask[i];

		if (atoi(&cMask) == 0)
		{
			strncat(binaryReverseMask, "1", 1);
			printf("1");
		}
		else
		{
			strncat(binaryReverseMask, "0", 1);
			printf("0");
		}
	}

	char binaryBroadcast[32 + 1] = "";
	//faire un "ou logique"
	printf("\n");
	printf("Ou logique     : ");
	for (int i = 0; i < 32; i++)
	{
		char cIP = binaryIP[i];
		char cMask = binaryReverseMask[i];

		if (atoi(&cIP) == 0 && atoi(&cMask) == 0)
		{
			strncat(binaryBroadcast, "0", 1);
			printf("0");
		}
		else
		{
			strncat(binaryBroadcast, "1", 1);
			printf("1");
		}
	}

	//Convert binary ip to IPv4
	IPv4 broadcastIP;
	broadcastIP = convertBinaryToIPv4(binaryBroadcast);

	printf("\n\n");
	printf("ADRESSE BROADCAST : \n");
	printIP(broadcastIP);
	
	printf("\n");
}

char* trouverReseau(IPv4 ip);
char* trouverHost(IPv4 ip);

void printIP(IPv4 ip)
{
	printf("valeur1 = %d\n", ip.valeur1);
	printf("valeur2 = %d\n", ip.valeur2);
	printf("valeur3 = %d\n", ip.valeur3);
	printf("valeur4 = %d\n", ip.valeur4);
	printf("masque =  %d\n", ip.masque);
}

const char* octetDecimalEnOctetBinaire(int octetDecimal)
{
	static char motBinaire[8 + 1] = "";
	memset(motBinaire, 0, sizeof(motBinaire));

	int n = octetDecimal;

	int a[10];

	int i;
	for (i = 0;n > 0;i++)
	{
		a[i] = n % 2;
		n = n / 2;
	}
	int j;
	for (j = 0; j < 8 - i; j++)
	{
		char c = '0';
		strncat(motBinaire, &c, 1);
	}
	for (i = i - 1;i >= 0;i--)
	{
		char c = a[i] + '0';
		strncat(motBinaire, &c, 1);
	}

	return motBinaire;

	//strncat(outputTab, motBinaire, 8);
}

int octetBinaireEnOctetDecimal(char* octetBinaire)
{
	int resultat = 0;
	char mot[9] = "";

	strncat(mot, octetBinaire);

	for (int i = 0; i < 8; i++)
	{
		if (mot[i] == '1')
		{
			resultat += pow(2, ((8 - 1) - i));
		}
	}

	return resultat;
}

IPv4 convertBinaryToIPv4(char binaryIP[])
{
	IPv4 newIp;
	char ip[32 + 1] = "";
	strncat(ip, binaryIP);

	char valeur1[9] = "";
	for (int i = 0; i < 8; i++)
	{
		char* c = ip[i];
		strncat(valeur1, &c);
	}
	newIp.valeur1 = octetBinaireEnOctetDecimal(&valeur1);

	char valeur2[9] = "";
	for (int i = 8; i < (8 + 8); i++)
	{
		char* c = ip[i];
		strncat(valeur2, &c);
	}
	newIp.valeur2 = octetBinaireEnOctetDecimal(&valeur2);

	char valeur3[9] = "";
	for (int i = 16; i < (16 + 8); i++)
	{
		char* c = ip[i];
		strncat(valeur3, &c);
	}
	newIp.valeur3 = octetBinaireEnOctetDecimal(&valeur3);

	char valeur4[9] = "";
	for (int i = 24; i < (24 + 8); i++)
	{
		char* c = ip[i];
		strncat(valeur4, &c);
	}
	newIp.valeur4 = octetBinaireEnOctetDecimal(&valeur4);

	newIp.masque = 0;

	return newIp;
}