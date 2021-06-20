#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#define TAILLE_ADRESSE 18

typedef struct IPv4 {
	int valeur1;
	int valeur2;
	int valeur3;
	int valeur4;
	int masque;
}IPv4;

int isAddressValid(char* input);

void construireIP(char adresse[], IPv4* ip);
void construireMasque(int masque, IPv4* ip);

void findAdresseReseau(IPv4 ip, IPv4* reseau);
void findAdresseBroadcast(IPv4 ip, IPv4* broadcast);

char trouverClasse(IPv4 ip);
bool isAddressPrivate(IPv4 ip);

void affichage(IPv4 ip, IPv4 masque, IPv4 reseau, IPv4 broadcast,
	char classe, char* type, char* caracteristique);

void sauvegarderVersFichier(IPv4 ip, IPv4 masque, IPv4 reseau, IPv4 broadcast,
	char classe, char* type, char* caracteristique);

void trouverType(IPv4 ip, char* string);

void printIP(IPv4 ip);

void octetDecimalEnOctetBinaire(int octetDecimal, char* string);

int octetBinaireEnOctetDecimal(char* octetBinaire);

IPv4 convertBinaryToIPv4(char binaryIP[]);

void convertIPv4ToString(IPv4 ip, char* string);
void convertIPv4ToBinary(IPv4 ip, char* string);