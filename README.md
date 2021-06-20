# MiniProjet C - RUIZ Nathan & DESCHAUX-BEAUME Léo
 Projet M2201 
 sujet-2 - Analyse adresse IP

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

### **Sauvegarder vers un fichier "ip.txt"**
| sauvegarderVersFichier |  |
| -- | -- |
| description| txt
| paramètre | txt |
| return | txt