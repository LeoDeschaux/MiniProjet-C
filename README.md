# MiniProjet C - RUIZ Nathan & DESCHAUX-BEAUME Léo
 Projet M2201 
 sujet-2 - Analyse adresse IP

## **Preview**

![Gif fonctionnement](https://media.giphy.com/media/sla2HnCJ75JhkqUW6Q/giphy.gif)

## **Schéma de fonctionnement du programme**
![Schema](https://cdn.discordapp.com/attachments/707298011939733594/856234623223070720/Capture.PNG)

## **Description des fonctions**

### **isAdressValid**
```c 
int isAdressValid(char* input);
```

**`isAdressValid`** est une fonction permettant de savoir si une chaine de charactère est une adresse ip au format CDIR et si les valeurs de cette adresse sont correte.

Elle renvoit **0** si l'adresse est valide et **1** si elle ne l'est pas

**Paramètre :**
```c
char* input //correspond à la chaine de charactère à analyser
```

**Return**
```
renvoie un integer pouvant prendre la valeur 0 ou 1
```

**Exemple d'utilisation :**
```c
   if (isAdresseValid("192.168.1.10/24")
    //TRUE
   if (isAdresseValid("192.168.1.999/24")
    //FALSE
```

#

### **Vérifier le format**
| isAdressValid |  |
| -- | -- |
| description| isAdressValid permet de savoir si une chaine de caractère est une adresse ip au format CDIR et si les valeurs de cette adresse sont correte.
| paramètre | char* input |
| return | Elle renvoit un int, 0 si l'adresse est valide et 1 si elle ne l'est pas

### **Extraire les champs et convertir en structure IPv4**
| construireIP |  |
| -- | -- |
| description| construireIP permet d'extraire les differentes valeurs ainsi que le masque à l'interieur d'une chaine de caractère. Le format doit être en notation CIDR
| paramètre | char* input, IPv4* ip | 
| return | -

### **Convertir en valeurs numériques**

### **Décoder l'adresse IP**
### **Calculer le masque, l'adresse reseau, l'adresse de broadcast**


### **Vérifier s'il s'agit d'un type d'adresse particulier**
| nomFonction |  |
| -- | -- |
| description| txt
| paramètre | txt |
| return | txt


### **Afficher le résultat dans la console**
| nomFonction |  |
| -- | -- |
| description| txt
| paramètre | txt |
| return | txt


### **Enregistrer le résultat dans un fichier "ip.txt"** 
| nomFonction |  |
| -- | -- |
| description| txt
| paramètre | txt |
| return | txt