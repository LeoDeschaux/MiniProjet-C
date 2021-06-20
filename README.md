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
#


| Fonction | Description | Paramètre | Return | 
| ------ | ------ | | ------ | | ------ |
| int isAdressValid(char* input); | isAdressValid est une fonction permettant de savoir si une chaine de charactère est une adresse ip au format CDIR et si les valeurs de cette adresse sont correte. | Elle envoit 0 si l'adresse est valide et 1 si elle ne l'est pas
| GitHub | [plugins/github/README.md][PlGh] |