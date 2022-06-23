

# **Projet balance réseaux**


>**Introduction :** Le projet consiste à mettre en place des balances, chacune d’entre elles enverra ses données :
> * Soit sur un **google sheets** (nous n'aborderons pas cette partie)
> * Soit sur une **BDD**. 
> * Par **Wi-Fi** donc sans fil 
>> * **BDD :** Base de données (fr) / **DB :** Database (en) 

>Pour mettre en place la base de données, on va avoir besoin de :
> * **Héberger** un serveur et un nom de domaine
> * **Un script php** pour insérer des données dans MySQL et l’afficher sur une page web
> * **Une BDD**pour stocker les données

# 
## **Prérequis :**
>**Matériel :** 
> * **esp8266** : Carte de développement étant doté du wifi.
> * **HX711** : Cellule de charge qui nous permettra d’avoir les mesures de la balance
> * **Une balance** : Capteur qui renvoie une masse (en grammes)

>**Logiciels :**
> * **IDE Arduino :**
Cela nous permet de téléverser le code sur l’esp8266
(Pas utile pour la base de données pour transmettre 
les mesures par la suite).
> * **Serveur Apache :**
Cela nous permet d’héberger notre page web localement
afin d’y écrire nos script php pour stocker les données 
dans une base de données
> * **MySQL :**
Nous permet de créer des bases de données
> * **PHP et phpmyadmin :**
Nous permet d’envoyer les données de la page web vers phpmyadmin en utilisant des requêtes PHP.

>Pour me simplifier la tâche, j’ai décidé d’utiliser **XAMPP** qui comprend l’ensemble des logiciels cités au dessus (et plus) afin de mettre en place un serveur web local 

#
## **Vue globale du projet :** 
![Texte alternatif](overview_project.png "Titre, facultatif")

#
## **Mise en pratique**
<br>

> Le projet va se diviser en **deux parties** principales :
> * 1 - Brancher la balance au Hx711 puis connecter le Hx711 vers l'esp8266 (ou l'esp32)
> * 2 - Mettre en place le serveur web local
> * 3 - Téléverser le code arduino sur l'esp 32

> **Etape 1 :** Brancher la balance au HX711 puis connecter le HX711 vers l'esp8266
<br>

| Balance ->    | HX711          | - | HX711  ->| ESP8266    |
| :--------     |:--------------:|-:| :--------  |:-----------:|
| excitation +  |   RED/E+       |  | GND        |   GND       |      
| excitation -  | BLACK/E-       |  | 2.7V - 5V  | 3.3V ou 5V  | 
| signal -      | WHITE/A-       |  |  DAT       | D2          |
| signal +      | GREEN/A+       |  | CLK        | D3          |  
<br>

>**Etape 2 :** Mettre en place le serveur web local
<brW>

>Pour cette partie, nous allons tout simplement héberger un serveur web local grâce a **Xampp**, un logiciel qui hébergera notre serveur **MySQL** (contenant notre BDD) et notre serveur **Apache**.

>Lien téléchargement Xampp : https://www.apachefriends.org/download.html

>Une fois Xampp téléchargé et installé, lancez **"Xampp Control Pannel"** en mode administrateur. Lancez Apache et MySQL en appuyant sur le bouton **Start** puis cliquer sur le bouton **Admin** de MySQL (Faites la même opération pour Apache). 

>En cliquant sur admin de **Apache** vous tombez sur une page du type : **"localhost/dashboard".**   
>En cliquant sur admin de **MySQL** vous tombez sur une page du type : **"localhost/phpmyadmin".**
>>Attention : Si le serveur Apache ne se lance pas, il faut modifier le port de ce dernier( par défaut à 80) et le mettre sur 8080.
>>>Pour modifier, cliquez sur : config(bouton en haut à droite) -> Service and Port Settings | Vous pouvez maintenant saisir "8080". <br>   



