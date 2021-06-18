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

#include "functions.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

int main(int argc, const char** argv)
{
	while (true)
	{
		//SALUER L'UTILISATEUR
		printf("Veuillez entrer une adresse ip avec masque : ");

		//LIRE INPUT, ex: "192.168.1.13/24"
		char input[50];
		scanf("%s", input);
		printf("\n");
		printf("L'adresse que vous venez de rentrer : %s\n", input);
		
		//VERIFIER LE FORMAT
		if (isAddressValid(&input))
			printf("L'adresse est valide\n");
		else
		{
			printf("L'adresse n'est pas valide..\n");
			printf("-------------------------------------------\n");
			continue;
		}

		//EXTRAIRE ET CONVERTIR L'INPUT EN IP STRUCT
		IPv4 ip;
		construireIP(input, &ip);

		//TROUVER LA CLASSE DE L'IP (A,B,C,D,E)
		char classe = trouverClasse(ip);

		//SAVOIR SI L'IP EST public/private
		char type[10] = "";
		if (isAddressPrivate(ip))
			strncat(type, "private");
		else
			strncat(type, "public");

		//TROUVER LE MASQUE
		IPv4 masque;
		construireMasque(ip.masque, &masque);

		//TROUVER L'ADRESSE RESEAU
		IPv4 reseau;
		findAdresseReseau(ip, &reseau);

		//TROUVER L'ADRESSE DE BROADCAST
		IPv4 broadcast;
		findAdresseBroadcast(ip, &broadcast);

		//VERIFIER SI IL S'AGIT D'UN TYPE D'ADRESSE PARTICULIER (localhost, multicast, etc)
		char caracteristique[30] = "";
		strncat(caracteristique, trouverType(ip));

		//AFFICHAGE
		printf("\n");
		printf("IP        : %s\n", convertIPv4ToString(ip));
		printf("Masque    : %s\n", convertIPv4ToString(masque));
		printf("Reseau    : %s\n", convertIPv4ToString(reseau));
		printf("Broadcast : %s\n", convertIPv4ToString(broadcast));

		printf("\n");
		printf("Classe : %c\n", classe);

		printf("Type : %s\n", type);

		printf("Caracteristique : %s\n", caracteristique);

		//SAUVEGARDER VERS FICHIER
		sauvegarderVersFichier(input);
		
		printf("-------------------------------------------\n");
	}

	printf("\n");

	return 0;
}