# MiniProjet C - RUIZ Nathan & DESCHAUX-BEAUME Léo
 Projet M2201 
 sujet-2 - Analyse adresse IP

## **Preview**

![Alt Text](https://media.giphy.com/media/sla2HnCJ75JhkqUW6Q/giphy.gif)

## **Schéma de fonctionnement du programme**
## **Description des fonctions**
### **Vérifier le format**
#### **isAdressValid**
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

### **Extraire les champs**
### **Convertir en valeurs numériques**

### **Décoder l'adresse IP**
### **Calculer le masque, l'adresse reseau, l'adresse de broadcast**
### **Vérifier s'il s'agit d'un type d'adresse particulier**
### **Afficher le résultat dans la console**
### **Enregistrer le résultat dans un fichier "ip.txt" 