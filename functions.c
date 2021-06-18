#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#include "functions.h"

int isAddressValid(char* input)
{
	enum state { record_valeur, record_mask };
	enum state state = record_valeur;

	char valeurs[4][3 + 1] = { "", "xxx", "xxx", "xxx" };
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

	return isValid;
}

void construireIP(char input[], IPv4* ip) {
	char adresse[18+1] = "";
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

void construireMasque(int masque, IPv4* ip)
{
	//CONVERT TO BINARY
	char binaryMask[32 + 1] = "";

	int i;
	for (i = 0; i < masque; i++)
	{
		strncat(binaryMask, "1", 1);
	}
	for (int j = i; j < 32; j++)
	{
		strncat(binaryMask, "0", 1);
	}

	IPv4 maskIP;
	maskIP = convertBinaryToIPv4(binaryMask);

	*ip = maskIP;
}

void findAdresseReseau(IPv4 ip, IPv4* reseau)
{
	//convert ip to binary
	char binaryIP[32 + 1] = "";
	strncat(binaryIP, convertIPv4ToBinary(ip));

	//convert mask to binary
	IPv4 masque;
	construireMasque(ip.masque, &masque);

	char binaryMask[32 + 1] = "";
	strncat(binaryMask, convertIPv4ToBinary(masque));

	//ET logique (ip ET masque)
	char binaryNetwork[32 + 1] = "";
	for (int i = 0; i < 32; i++)
	{
		char cIP = binaryIP[i];
		char cMask = binaryMask[i];

		if (atoi(&cIP) == 0 || atoi(&cMask) == 0)
			strncat(binaryNetwork, "0", 1);
		else
			strncat(binaryNetwork, "1", 1);
	}

	//Convert binary ip to IPv4
	IPv4 networkIP;
	networkIP = convertBinaryToIPv4(binaryNetwork);

	*reseau = networkIP;
}

void findAdresseBroadcast(IPv4 ip, IPv4* broadcast)
{
	//convert ip to binary
	char binaryIP[32 + 1] = "";
	strncat(binaryIP, convertIPv4ToBinary(ip));

	//convert mask to binary
	IPv4 masque;
	construireMasque(ip.masque, &masque);

	char binaryMask[32 + 1] = "";
	strncat(binaryMask, convertIPv4ToBinary(masque));

	//inverser le masque
	char binaryReverseMask[32 + 1] = "";
	for (int i = 0; i < 32; i++)
	{
		char cMask = binaryMask[i];

		if (atoi(&cMask) == 0)
			strncat(binaryReverseMask, "1", 1);
		else
			strncat(binaryReverseMask, "0", 1);
	}

	//OU logique (ip OU (inverse du masque))
	char binaryBroadcast[32 + 1] = "";
	for (int i = 0; i < 32; i++)
	{
		char cIP = binaryIP[i];
		char cMask = binaryReverseMask[i];

		if (atoi(&cIP) == 0 && atoi(&cMask) == 0)
			strncat(binaryBroadcast, "0", 1);
		else
			strncat(binaryBroadcast, "1", 1);
	}

	//Convert binary ip to IPv4
	IPv4 broadcastIP;
	broadcastIP = convertBinaryToIPv4(binaryBroadcast);

	*broadcast = broadcastIP;
}

char trouverClasse(IPv4 ip) {
	signed char classe;
	if (ip.valeur1 >= 0 && ip.valeur1 < 128)
		classe = 'A';
	if (ip.valeur1 >= 128 && ip.valeur1 < 192)
		classe = 'B';
	if (ip.valeur1 >= 192 && ip.valeur1 < 224)
		classe = 'C';
	if (ip.valeur1 >= 224 && ip.valeur1 < 240)
		classe = 'D';
	if (ip.valeur1 >= 240 && ip.valeur1 < 256)
		classe = 'E';

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

const char* trouverType(IPv4 ip)
{
	static char string[50] = "";
	memset(string, 0, sizeof(string));

	//FIND MASQUE
	IPv4 masque;
	construireMasque(ip.masque, &masque);

	//FIND RESEAU
	IPv4 reseau;
	findAdresseReseau(ip, &reseau);

	//FIND BROADCAST
	IPv4 broadcast;
	findAdresseBroadcast(ip, &broadcast);

	//FIND IP CLASS (A,B,C)
	char classe = trouverClasse(ip);

	//------ ANALYSE ---------//

	//CHECK LOCALHOST
	if (ip.valeur1 == 127 && ip.masque == 8 && ip.valeur4 != 0)
	{
		strncat(string, "localhost ");
		return string;
	}

	//CHECK MULTICAST
	char c3[2] = "";
	char c4[2] = "";

	strncat(c3, &classe, 1);
	strncat(c4, "D", 1);

	if (strcmp(c3, c4) == 0)
		strncat(string, "multicast ");
	
	//CHECK RESEAU
	char c1[30] = "";
	char c2[30] = "";
	memset(c1, 0, sizeof(c1));
	memset(c2, 0, sizeof(c2));

	strncat(c1, convertIPv4ToString(ip));
	strncat(c2, convertIPv4ToString(reseau));

	if (strcmp(c1, c2) == 0)
	{
		strncat(string, "reseau ");
		return string;
	}

	//CHECK BROADCAST
	memset(c1, 0, sizeof(c1));
	memset(c2, 0, sizeof(c2));

	strncat(c1, convertIPv4ToString(ip));
	strncat(c2, convertIPv4ToString(broadcast));

	if (strcmp(c1, c2) == 0)
	{
		strncat(string, "broadcast ");
		return string;
	}

	//NONE
	if (strcmp(string, "") == 0)
		strncat(string, "-");
	
	return string;
}

void printIP(IPv4 ip)
{
	printf("valeur1 = %d\n", ip.valeur1);
	printf("valeur2 = %d\n", ip.valeur2);
	printf("valeur3 = %d\n", ip.valeur3);
	printf("valeur4 = %d\n", ip.valeur4);
	printf("masque  = %d\n", ip.masque);
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

const char* convertIPv4ToString(IPv4 ip)
{
	static char string[20] = "";
	memset(string, 0, sizeof(string));

	char valeur[5] = "";
	memset(valeur, 0, sizeof(valeur));
	sprintf(valeur, "%d.", ip.valeur1);
	strncat(string, valeur);

	memset(valeur, 0, sizeof(valeur));
	sprintf(valeur, "%d.", ip.valeur2);
	strncat(string, valeur);

	memset(valeur, 0, sizeof(valeur));
	sprintf(valeur, "%d.", ip.valeur3);
	strncat(string, valeur);

	memset(valeur, 0, sizeof(valeur));
	sprintf(valeur, "%d", ip.valeur4);
	strncat(string, valeur);

	return string;
}

const char* convertIPv4ToBinary(IPv4 ip)
{
	static char binaryIP[32 + 1] = "";
	memset(binaryIP, 0, sizeof(binaryIP));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur1));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur2));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur3));
	strncat(binaryIP, octetDecimalEnOctetBinaire(ip.valeur4));

	return binaryIP;
}