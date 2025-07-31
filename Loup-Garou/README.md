# Les LoupsGarous de Thiercelieux 


Ce programme permet de jouer à plusieur sur un même écran au célèbre jeu Loup Garou édité par Asmodee.
vous pouvez jouer de 8 à 12 joueurs.

-----------------------
## Information importante
-----------------------

Le programme fonctionne uniquement sur Linux. 
Liens GitHub du projet : https://github.com/adamou02/Loup-Garou


---------------------------------------------
## Pour lancer Les Loups-Garous de Thiercelieux
---------------------------------------------

### Executable

Il suffit de doubler cliquer sur le LoupGarou.exe

### Compilation

Accéder à votre terminale Linux avec la commande
ctrl+alt+t.
Une fois dans le terminale diriger vous avec la commande "cd" pour
atteindre le dossier "LoupGarou" vous devriez avoir dans le dossier:

- main.c
- debutdepartie.h
- role.h
- blabla.h
- jour.h
- nuit.h
- README.txt

Si il manque un des fichier veuillez réinstaller le fichier manquant à l'aide du liens :
https://github.com/adamou02/Loup-Garou

Si tout les fichier sont présent faire la commande : 

	  gcc main.c -o LoupGarou  

Puis pour lancer le programme :

	  ./LoupGarou  

------------------------------------------
## Regles du jeu et déroulement d'une partie
------------------------------------------

### INITIALISATION

Le programme va, vous demandez le nombre de joueurs participant entre 8 et 12.
Puis après avoir rentré votre nom votre rôle sera donner.
Ne pas oublier d'appuyer sur 1 à chaque fois que c'est votre tour pour ne pas
dévoiler votre identité au joueur suivant. Appelez le joueur concerné quand il est affiché sur l'écran.



### But du jeu

- Pour les Villageois : éliminer les Loups-garous.
- Pour les Loups-garous : éliminer les Villageois.



### Les cartes :


**Les LOUPS-GAROUS**
Chaque nuit, ils égorgent un Villageois.
Le jour ils se font passer pour des Villageois
afin de ne pas être démasqués.



**Les VILLAGEOIS**
Chaque nuit, l’un d’entre eux est égorgé par le ou les Loups-Garous.
Ce joueur est éliminé du jeu, et ne peut plus participer aux débats. Les Villageois survivants doivent chaque jour lyncher un des joueur, dans l’espoir qu’il soit Loup-Garou. Comme dans le jeu traditionnelle un villageois peut importe son rôle peut entrendre des bruit. Il aura alors le nom de 3 joueurs suspect mais seulement 1 des 3 est loup garou.


• Simple Villageois •
Il n’a aucune compétence particulière, il faut juste que le joueur soit très intuitif.


• Voyante •
Chaque nuit, elle connaît la vrai personnalité d’un joueur de son choix, elle doit aider les Villageois, sans être démasquée par les Loups-Garous.


• Chasseur •
Le chasseur, s’il se fait égorger par les Loups-Garous ou lyncher par les joueurs, a le pouvoir de répliquer en tuant immédiatement n’importe quel autre joueur.


• Cupidon •
La première nuit, il choisit 2 joueurs qui seront follement Amoureux l’un de l’autre. Si l’un d’eux meurt, l’autre meurt de chagrin immédiatement. Un Loup-Garou et un villageois peuvent être Amoureux l'un de l'autre. Ils jouent alors contre tous les autres, Loups-Garous et Villageois.Si les amoureux survivent, alors ce sont eux qui gagnentLe cupidon peut se désigner lui-même comme un des 2 Amoureux.


• Sorcière •
Elle sait concocter 2 potions extrêmement puissantes :
une potion de guérison, pour ressusciter le joueur tué par les Loups-Garous,
une potion d’empoisonnement, utilisée la nuit pour éliminer un joueur. La Sorcière doit utiliser chaque potion 1 seule fois dans la partie. Elle peut se servir des ses 2 potions la même nuit. Le matin suivant l’usage de ce pouvoir, il pourra donc y avoir soit 0 mort, 1 mort ou 2 morts. La sorcière peut utiliser les potions à son profit, et donc se guérir elle-même.


• Voleur •
Le Voleur a le droit durant la première nuit d’échanger sa carte contre une des 2 cartes supplémentaires qu’il reste après distribution du jeu.Il jouera désormais ce personnage. Si une des 2 cartes est un Loups-Garous, le Voleur doit la prendre.


• Petite fille •
Elle sait durant la nuit qui sont les Loups-Garous. Elle peut se faire surprendre par un des Loups-Garous (aléatoirement), elle meurt immédiatement, à la place de la victime désignée.


• Capitaine•
Cette carte est confiée à un des joueurs, en plus de sa carte personnage. Le Capitaine est élu par vote durant la 1ere journée, à la majorité relative. On ne peut refuser l’honneur d’être capitaine.Dorénavant, les votes de ce joueur comptent pour 2 voix. Si ce joueur se fait éliminer, on doit désigne son successeur.



### • TOURS DE JEU •


1 - C'EST LA NUIT, l'ordinateur demande à tous les joueurs de s'assoir, le village s'endort.

- Selon le choix des personnages en jeu -

2 - (Premier tour seulement) L'orinateur appelle le Voleur.
Il se réveille et regarde les 2 cartes restant du paquet, puis il change de personnage.
Le Voleur termine son tour.

3 - (Premier tour seulement) L'ordinateur appelle le Cupidon. Il se presente et choisit 2 joueurs (dont éventuellement lui-même). L'ordinateur appelle aux prochain tour les 2 Amoureux.
Cupidon se rendort.

4 - (Premier tour seulement) Le maître appelle les Amoureux. Ils se réveillent, se reconnaissent, et se rendorment.

5 - (Tous les tours) Le maître appelle la Voyante.
Elle se réveille, et choisit un joueur à sonder. L'ordinateur lui montre la carte du joueur.
La Voyante se rendort.

6 - (Tous les tours) L'ordinateur appelle les Loups-Garous. Ils doivent désigner une victime chacun leur tour en cas d'égalité l'aléatoire départagera les victime pour en choisir qu'un.
si la petite fille se fait prendre elle meurt, à la place de la victime éventellement choisie.
Les Loups Garous se rendorment.

7 - (Tous les tours) L'ordinateur appelle la Sorcière.
L'ordinateur montre la victime des Loups-Garous. elle peut user de sa potion de guérison, ou d’empoisonnement. La Sorcière n’est pas obligée d’user de son pouvoir à un tour spécifique. Si elle utilise une potion, elle doit désigner a l'ordinateur sa cible.

8 - C’EST LE JOUR, le village se réveille, tout le monde lève la tête et ouvre les yeux. Le maître désigne le joueur qui a été victime des Loups-Garous durant la nuit. Ce joueur révèle sa carte, et est éliminé du jeu. Quel que soit son personnage, il ne pourra plus communiquer avec les autres joueurs sous quelque forme que se soit.
• Si ce joueur est le Chasseur, il a le droit de répliquer et tue immédiatement un autre joueur de son choix.
• Si ce joueur est un des 2 Amoureux, l’autre Amoureux se suicide immédiatement.

9 - Les joueurs à force de débats doivent désigner l’un d’entre eux, qui sera éliminé d’après le vote.
• Les Villageois tentent de démasquer un loup-garou et de faire voter pour son élimination.
• Les Loups-Garous doivent à force de bluff et mensonges, se faire passer pour des Villageois.
• La Voyante ainsi que la Petite fille doivent aider les Villageois, mais sans mettre trop tôt leur vie en danger en exposant leur identité.
• Les Amoureux doivent se protéger l’un l’autre.
En cas d’égalité, s’il est présent, le vote du Capitaine désigne la victime. Sinon, les joueurs votent à nouveau (y compris les joueurs en cause) pour départager les ex-aequo.

10 - Le joueur désigné par la majorité des voix est éliminé, il révèle son role et ne pourra plus communiquer avec les autres joueurs sous quelque forme que se soit. En cas d’égalité, les joueurs revotent pour départager les ex-æquo.

11 - C’EST LA NUIT, tous les joueurs vivants se rendorment.
Le jeu reprend au tour N° 5




### CONDITIONS DE VICTOIRE

Les Villageois gagnent, dès le dernier Loup-Garou est éliminé.

Les Loups-Garous gagnent, dès que l'avant dernier villageois est éliminé..


---------------------------
## Groupe du Projet et contact
----------------------------

Amaury PROVENT amauryprovent@gmail.com

Adam BOUHRARA bouhrara.adam@gmail.com

Jeanne TAVERNIER jeanne.tavernier0@gmail.com
