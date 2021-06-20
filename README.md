# **MiniProjet C - RUIZ Nathan & DESCHAUX-BEAUME Léo**

#### **Projet M2201**

#### **sujet-2 - Analyse adresse IP**

**Etudiants :** **RUIZ Nathan** et **DESCHAUX-BEAUME Léo**

**Groupe :** E1


### **Présentation du projet**

L'objectif de ce programme est d'analyser un adresse IP entrée dans la console par l'utilisateur.

Le programme est alors capable de données les informations suivantes : 
- L'adresse IP est-elle valide ? 
- Quelle est la valeur du masque ?
- A quelle adresse réseau appartient cette IP ?
- Quelle est l'adresse de diffusion correspondant à ce réseau ?

- A quelle classe appartient cette adresse ?
- L'adresse est elle priver ou bien publique ?
- L'adresse IP correspond-elle à un type d'adresse particulier ? (localhost, réseau, broadcast, multicast)

#

Le programme dispose également d'une fonction enregistrement qui lui permet d'enregistrer les adresses IP ainsi que les informations les concernant, au seins d'un fichier .txt.

Le fichier est présent dans le répertoire où se trouve le programme et se nomme "ip.txt".
Seules les adresses validées par le programme se retrouvent enregistrées dans ce fichier.

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
| description| construireIP permet d'extraire les differentes valeurs présentes à l'interieur d'une chaine de caractère, de convertir les valeurs en int, puis de les stocker dans une structure IPv4. Le format doit être en notation CIDR
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
| sauvegarderVersFichier |  |
| -- | -- |
| description| sauvegarderVersFichier permet de sauvegarder les informations dans un fichier nommé ip.txt à l'interieur du répertoire du programme
| paramètre | IPv4 ip, IPv4 masque, IPv4 reseau, IPv4 broadcast, char classe, char* type, char* caracteristique |
| return | void

#

## **Description de fonctions facultatives utilisée lors du développement**

### Afficher une Structure IPv4
| printIP(ip) |  |
| -- | -- |
| description| printIP permet d'afficher séparement dans la console les differentes valeurs d'une adresse IP
| paramètre | IPv4 ip |
| return | void

### Convertir un octet decimal en un octet binaire
| octetDecimalEnOctetBinaire |  |
| -- | -- |
| description| octetDecimalEnOctetBinaire permet de convertir un octet decimal donné en entrée en un octet binaire sous la forme d'une chaine de caractères 
| paramètre | int octetDecimal, char* string |
| return | void

### Convertir un octet binaire en un octet decimal
| octetBinaireEnOctetDecimal |  |
| -- | -- |
| description| octetBinaireEnOctetDecimal permet de convertir un octet binaire donné en entrée en une valeur décimale
| paramètre | char* octetBinaire |
| return | int

### Convertir une adresse IP binaire en adresse IP Decimal
| convertBinaryToIPv4 |  |
| -- | -- |
| description| convertBinaryToIPv4 permet de convertir une adresse IP sous forme binaire en une structure de données IPv4
| paramètre | char binaryIP[] |
| return | IPv4

### Convertir une adresse IP en une chaine de caractères
| convertIPv4ToString |  |
| -- | -- |
| description| convertIPv4ToString permet de convertir une adresse IP IPv4 en une chaine de caractères
| paramètre | IPv4 ip, char* string |
| return | void

### Convertir une adresse IP decimal en une adresse IP binaire
| convertIPv4ToBinary |  |
| -- | -- |
| description| convertIPv4ToBinary permet de convertir une adresse IP de type IPv4 en une adresse IP au format binaire dans une chaine de caractères
| paramètre | IPv4 ip, char* string |
| return | void