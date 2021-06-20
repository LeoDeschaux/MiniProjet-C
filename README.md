# MiniProjet C - RUIZ Nathan & DESCHAUX-BEAUME Léo
 Projet M2201 
 sujet-2 - Analyse adresse IP

 Etudiants : RUIZ Nathan et DESCHAUX-BEAUME Léo
 Groupe : E1
 1ère année, semestre 2 

### **Présentation du projet**

L'objectif de ce programme est d'analyser un adresse IP entrée par l'utilisateur dans la console.

## **Preview**

![Gif fonctionnement](https://media.giphy.com/media/sla2HnCJ75JhkqUW6Q/giphy.gif)

## **Schéma de fonctionnement du programme**
![Schema](https://cdn.discordapp.com/attachments/707298011939733594/856234623223070720/Capture.PNG)

## **Structure de données IPv4**
```c
typedef struct IPv4 {
   int valeur1;
   int valeur2;
   int valeur3;
   int valeur4;
   int masque;
}IPv4;
```

## **Description des fonctions**


### **Vérifier le format**
| isAdressValid |  |
| -- | -- |
| description| isAdressValid permet de savoir si une chaine de caractère est une adresse ip au format CDIR et si les valeurs de cette adresse sont correte.
| paramètre | char* input |
| return | Elle renvoit un int prenant la valeur 0 si l'adresse est valide et 1 si elle ne l'est pas

### **Extraire les champs et convertir en structure IPv4**
| construireIP |  |
| -- | -- |
| description| construireIP permet d'extraire les differentes valeurs ainsi que le masque à l'interieur d'une chaine de caractère. Le format doit être en notation CIDR
| paramètre | char* input, IPv4* ip | 
| return | 

### **Trouver la classe de l'adresse IP**
| trouverClasse |  |
| -- | -- |
| description| trouverClasse permet d'obtenir la classe à laquelle appartient l'adresse IP
| paramètre | IPv4 ip |
| return | char, correspondant à la classe (A,B,C,D, E)

### **Savoir si l'adresse est public ou private**
| isAddressPrivate |  |
| -- | -- |
| description| isAddressPrivate permet de s'avoir si une adresse IPv4 est privée ou publique
| paramètre | IPv4 ip |
| return | bool, renvoi TRUE si l'adresse est privé, sinon FALSE

### **Calculer le masque**
| construireMasque |  |
| -- | -- |
| description| construireMasque permet d'obtenir un masque au format pointé à partir d'une IP au format CIDR
| paramètre | IPv4 ip, IPv4* masque |
| return | 

### **Trouver l'adresse reseau**
| findAdresseReseau |  |
| -- | -- |
| description| findAdresseReseau permet d'obtenir l'adresse du reseau à laquelle appartient une adresse IP à partir de cette dîte adresse IP
| paramètre | IPv4 ip, IPv4* reseau |
| return | 

### **Trouver l'adresse de broadcast**
| findAdresseBroadcast |  |
| -- | -- |
| description| findAdresseReseau permet d'obtenir l'adresse de broadcast à laquelle appartient une adresse IP à partir de cette dîte adresse IP
| paramètre | IPv4 ip, IPv4* broadcast |
| return | 

### **Vérifier s'il s'agit d'un type d'adresse particulier**
| trouverType |  |
| -- | -- |
| description| trouverType permet de savoir si l'adresse IP correspond à un type d'adresse particulier (Localhost / MultiCast / Reseau / Broadcast)
| paramètre | IPv4 ip  |
| return | const char*

### **Affichager dans la console**
| affichage|  |
| -- | -- |
| description| affichage permet d'afficher les informations dans console
| paramètre | IPv4 ip, IPv4 masque, IPv4 reseau, IPv4 broadcast, char classe, char* type, char* caracteristique |
| return | void

### **Sauvegarder vers fichier "ip.txt"** 
| sauvegarderVersFichier(ip, masque, reseau, broadcast, classe, type, caracteristique) |  |
| -- | -- |
| description| La fonction sauvegarderVersFichier sert à sauvegarder les informations dans un fichier nommé ip.txt dans le dossier du programme
| paramètre | IPv4 ip, IPv4 masque, IPv4 reseau, IPv4 broadcast, char classe, char* type, char* caracteristique |
| return | void

## **Description de fonctions facultatives utilisée lors du développement**

### Afficher une Structure IPv4
| printIP(ip) |  |
| -- | -- |
| description| La fonction printIP sert à afficher séparement sur la console les differentes valeurs d'une adresse IP
| paramètre | IPv4 ip |
| return | void

### Convertir un octet decimal en un octet binaire
| octetDecimalEnOctetBinaire(octetDecimal, string) |  |
| -- | -- |
| description| La fonction octetDecimalEnOctetBinaire sert à convertir un octet decimal donné en entrée en un octet binaire sous la forme d'une chaine de caractères donnée en entrée 
| paramètre | int octetDecimal, char* string |
| return | void

### Convertir un octet binaire en un octet decimal
| octetBinaireEnOctetDecimal(octetBinaire) |  |
| -- | -- |
| description| La fonction octetBinaireEnOctetDecimal sert à convertir l'octet en binaire donné en entré en une valeur décimale
| paramètre | char* octetBinaire |
| return | int

### Convertir une adresse IP binaire en adresse IP en Decimal
| convertBinaryToIPv4(binaryIP[]) |  |
| -- | -- |
| description| La fonction convertBinaryToIPv4 sert à convertir une adresse IP sous forme binaire en un Type IPv4
| paramètre | char binaryIP[] |
| return | IPv4

### Convertir une adresse IP en une chaine de caractères
| convertIPv4ToString(ip, string) |  |
| -- | -- |
| description| La fonction convertIPv4ToString sert à convertir une adresse IP en type IPv4 en une chaine de caractères
| paramètre | IPv4 ip, char* string |
| return | void

### Convertir une adresse IP en decimal en une adresse IP en binaire
| convertIPv4ToBinary(ip, string) |  |
| -- | -- |
| description| La fontion convertIPv4ToBinary sert à passer une adresse IP de type IPv4 en une adresse IP sous forme binaire dans une chaine de caractères
| paramètre | IPv4 ip, char* string |
| return | void

### Construire une structure IPv4
| construireIP(input[],  ip) |  |
| -- | -- |
| description| La fonction construireIP sert à construire la structure IPv4 en y entrant les valeurs entrées par l'utilisateurs, elle separe les valeurs et les converti en int
| paramètre | char input[], IPv4* ip |
| return | void